#include <client_http.hpp>
#include <future>
#include <server_http.hpp>

// Added for the default_resource example
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

#include "word_dict_struct.hpp"
#include "EnglishChineseWordDict.h"
#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseMySql.hpp"
#include "json11.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using Response_SHARED_PTR = std::shared_ptr<HttpServer::Response>;
using Request_SHARED_PTR = std::shared_ptr<HttpServer::Request>;
class CWordTranslateServer
{
//Function
public:
    CWordTranslateServer();
    virtual ~CWordTranslateServer();
public:
    bool Start();
    bool Stop();
protected:
    void OnVersion(Response_SHARED_PTR response,
        Request_SHARED_PTR request);
    void OnEnglishToChinese(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnEnglishToWordTranslate(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnEnglishToChineseMock(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultGet(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultPost(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnAddWordToKnow(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnAddWordToUnKnow(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

private:
    AddWordToKnowReq_t  AddRemoveWordReq(Request_SHARED_PTR request);
    EnglishToChineseReq_t GetReqFromRequest(Request_SHARED_PTR request);
    EnglishToChineseRsp_t CreateRspFromReq(const EnglishToChineseReq_t& req);
    SentenceToWordsRsp_t TranslateSentence(const EnglishToChineseReq_t& req);
    AddWordToKnownRsp_t  AddWordToKnow(const AddWordToKnowReq_t& req);
    AddWordToUnKnownRsp_t  AddWordToUnKnown(const AddWordToUnKnownReq_t& req);
    bool MatchUrlMethodAndFunction();
    void ShowRemotePeer(Request_SHARED_PTR request);
    std::string ToLower(const std::string strOrg);
    std::string WordTrim(const std::string strOrg);

private:
    HttpServer m_server;
    //CDictDatabaseJson m_dict;
    CDictDatabaseMysql m_dict;
    CUserWordDatabaseJson m_userWordDatabase;
};

CWordTranslateServer::CWordTranslateServer()
{
    m_server.config.port = 8080;
    /* {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "toefl_dict.json";
        cfg.m_nLevel = 10;
        m_dict.SetDictDatabaseConfig(&cfg);
    }*/

    {
        MysqlDatabaseConfig cfg;
        cfg.m_strMysqlServerIp = "localhost";
        cfg.m_nMysqlServerPort = 3306;
        cfg.m_strMysqlUserName = "test";
        cfg.m_strMysqlPassoword = "test@1990";
        cfg.m_strDataBase = "json_dict";
        m_dict.SetDictDatabaseConfig(&cfg);
    }
}

CWordTranslateServer::~CWordTranslateServer()
{

}

void CWordTranslateServer::ShowRemotePeer(Request_SHARED_PTR request)
{
    std::cout << "Remote: " << std::endl;
}

bool CWordTranslateServer::Start()
{
    MatchUrlMethodAndFunction();
    std::promise<unsigned short> server_port;
    std::thread server_thread([this, &server_port]() {
        // Start server
        m_server.start(
            [&server_port](unsigned short port) { server_port.set_value(port); });
        });
    std::cout << "Server listening on port " << server_port.get_future().get()
        << std::endl
        << std::endl;
    server_thread.join();
    return false;
}

bool CWordTranslateServer::Stop()
{
    return false;
}

EnglishToChineseReq_t CWordTranslateServer::GetReqFromRequest(Request_SHARED_PTR request)
{
   EnglishToChineseReq_t result;
   {
       std::string strReq = request->content.string();
       {
           std::string strErr;
           auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
           if (strErr.empty())
           {
               result.m_strToken = resultJson["token"].string_value();
               result.m_strEnglish = resultJson["english"].string_value();
               return result;
           }
       }
   }
   return result;
}

std::string CWordTranslateServer::ToLower(const std::string strOrg)
{
    std::string strCopy = strOrg;
    std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return strCopy;
}

std::string CWordTranslateServer::WordTrim(const std::string strOrg)
{
    std::string strResult;
    for (auto iter = strOrg.begin(); iter != strOrg.end(); iter++) {
        if ( ('a' <= *iter) && 
             (*iter <= 'z')  ) {
            strResult += *iter;
        }
    }
    return strResult;
}
AddWordToKnowReq_t CWordTranslateServer::AddRemoveWordReq(Request_SHARED_PTR request)
{
    AddWordToKnowReq_t result;
    {
        std::string strReq = request->content.string();
        {
            std::string strErr;
            auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
            if (strErr.empty())
            {
                result.m_strToken = resultJson["token"].string_value();
                result.m_strWord = resultJson["word"].string_value();
                return result;
            }
        }
    }
    return result;
}


EnglishToChineseRsp_t CWordTranslateServer::CreateRspFromReq(const EnglishToChineseReq_t& req)
{
    EnglishToChineseRsp_t result;
    std::string strChinese = m_dict.GetTranslation(req.m_strEnglish).F_CHINESE;
    if (strChinese.empty())
    {
        result.m_code = 0;
        result.m_strMsg = "New words";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = "NEW_WORDS";
        std::cout << "FAILED  English: " << req.m_strEnglish << std::endl;
    }
    else
    {
        result.m_code = 0;
        result.m_strMsg = "success";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = strChinese;
        std::cout << "SUCCEED  English: " << req.m_strEnglish << "  Chinese: " << strChinese << std::endl;
    }
    return result;
}

/*
* (1) 收到整个英语句子。
(2) 拆分为多个单词。
(3) 确定改单词是否需要翻译
(3.1) 需要翻译，则翻译为汉语
(3.2) 不需要翻译，跳过
(4) 返回所有的翻译结果

*/
SentenceToWordsRsp_t CWordTranslateServer::TranslateSentence(const EnglishToChineseReq_t& req)
{
    SentenceToWordsRsp_t result;
    std::vector<EnglishToChineseData_t> transResultArray;
 
    std::string strSentence = req.m_strEnglish;
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;
    startIndex = endIndex;
    std::cout << "Sentence:  " << strSentence << std::endl;
    
    std::map<std::string, int> words;
    {

        while (endIndex != std::string::npos) {
            endIndex = strSentence.find_first_of(" ", startIndex);
            std::string word = strSentence.substr(startIndex, endIndex - startIndex);
            std::cout << "Word:  " << word << std::endl;
            words.insert({ word,1 });
            startIndex = endIndex + 1;
        }
    }

    bool bNeedTranslat = false;
    for (auto item : words) {
        bNeedTranslat = true;
        //Need Translate
        {
            if (m_userWordDatabase.IsKnownWord(item.first, req.m_strToken))
            {
                bNeedTranslat = false;
            }
        }
        //Translate
        {
            if (bNeedTranslat)
            {
                EnglishToChineseData_t elem;
                elem.m_strEnglish = item.first;
                std::string strLow = ToLower(elem.m_strEnglish);
                strLow = WordTrim(strLow);
                elem.m_strChinese = m_dict.GetTranslation(strLow).F_CHINESE;
                std::cout << "Engish: " << item.first << "   Chinese: " << elem.m_strChinese << std::endl;
                transResultArray.push_back(elem);
            }
            else
            {
                std::cout << "CAN NOT TRANS EN: " << item.first << std::endl;
            }
        }
    }
    result.m_code = 0;
    result.m_strMsg = "success";
    result.m_data = transResultArray;
    return result;
}

AddWordToKnownRsp_t  CWordTranslateServer::AddWordToKnow(const AddWordToKnowReq_t& req)
{
    AddWordToKnownRsp_t result;
    if (m_userWordDatabase.IsKnownWord(req.m_strWord, req.m_strToken))
    {
        result.m_code = -1;
        result.m_strMsg = "Already a known word";
    }
    else
    {
        if (m_userWordDatabase.IsUnKnownWord(req.m_strWord, req.m_strWord))
        {
            m_userWordDatabase.DeleteUnKnownWord(req.m_strWord, req.m_strToken);
        }
        m_userWordDatabase.InsertKnownWord(req.m_strWord, req.m_strToken);
        result.m_code = 0;
        result.m_strMsg = "success";
    }

    return result;
}

AddWordToUnKnownRsp_t CWordTranslateServer::AddWordToUnKnown(const AddWordToUnKnownReq_t& req)
{
    AddWordToKnownRsp_t result;
    if (m_userWordDatabase.IsUnKnownWord(req.m_strWord, req.m_strToken))
    {
        result.m_code = -1;
        result.m_strMsg = "Already a unknown word";
    }
    else
    {
        if (m_userWordDatabase.IsKnownWord(req.m_strWord, req.m_strWord))
        {
            m_userWordDatabase.DeleteKnownWord(req.m_strWord, req.m_strToken);
        }
        m_userWordDatabase.InsertUnKnownWord(req.m_strWord, req.m_strToken);
        result.m_code = 0;
        result.m_strMsg = "success";
    }

    return result;
}
std::string WordRspToString(const EnglishToChineseRsp_t& rsp)
{
    json11::Json dataJson = json11::Json::object{
        {"english",rsp.m_data.m_strEnglish},
        {"chinese",rsp.m_data.m_strChinese}
    };
    json11::Json rspJson = json11::Json::object{
        {"code",rsp.m_code},
        {"message",rsp.m_strMsg},
        {"data",dataJson}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}


std::string AddRemoveRspToString(const AddWordToKnownRsp_t& rsp)
{
  
    json11::Json rspJson = json11::Json::object{
       {"code",rsp.m_code},
       {"message",rsp.m_strMsg}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}


std::string SentenceRspToString(const SentenceToWordsRsp_t& rsp)
{
    json11::Json::array dataArray;
    for (auto item : rsp.m_data) {
        json11::Json dataJson = json11::Json::object{
            {"english",item.m_strEnglish},
            {"chinese",item.m_strChinese}
        };
        dataArray.push_back(dataJson);
    }
    json11::Json rspJson = json11::Json::object{
       {"code",rsp.m_code},
       {"message",rsp.m_strMsg},
       {"data",dataArray}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}

bool CWordTranslateServer::MatchUrlMethodAndFunction()
{
    m_server.resource["^/version$"]["GET"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnVersion(response, request);
        };

    m_server.resource["^/v1/english_to_chinese$"]["POST"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnEnglishToChinese(response, request);
        };
    m_server.resource["^/v1/sentence_to_words$"]["POST"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnEnglishToWordTranslate(response, request);
        };
    m_server.resource["^/v1/add_word_to_known$"]["POST"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnAddWordToKnow(response, request);
        };

    m_server.resource["^/v1/add_word_to_unknown$"]["POST"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnAddWordToUnKnow(response, request);
        };

    m_server.default_resource["GET"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
            OnDefaultGet(response, request);
        };
    m_server.default_resource["POST"] = [this](Response_SHARED_PTR response,
        Request_SHARED_PTR request) {
           OnDefaultPost(response, request);
        };
    return false;
}
void CWordTranslateServer::OnVersion(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    ShowRemotePeer(request);
    std::string strVersion = "VERSION 0.0.1";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}
void CWordTranslateServer::OnEnglishToChinese(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnEnglishToChinese" << std::endl;
    ShowRemotePeer(request);
    
    EnglishToChineseReq_t reqData = GetReqFromRequest(request);
    EnglishToChineseRsp_t rspData = CreateRspFromReq(reqData);
    std::string strRsp = WordRspToString(rspData);
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strRsp.length() << "\r\n\r\n"
        << strRsp;
}

void CWordTranslateServer::OnDefaultGet(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnDefaultGet" << std::endl;
    ShowRemotePeer(request);
    std::string strVersion = "Default Get";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

void CWordTranslateServer::OnDefaultPost(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnDefaultPost" << std::endl;
    ShowRemotePeer(request);
    std::string strVersion = "Default Post";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}


void CWordTranslateServer::OnEnglishToChineseMock(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{

}



void CWordTranslateServer::OnEnglishToWordTranslate(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnEnglishToWordTranslate" << std::endl;
    ShowRemotePeer(request);
    EnglishToChineseReq_t reqData = GetReqFromRequest(request);
    auto result = TranslateSentence(reqData);
    std::string strVersion = SentenceRspToString(result);
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

void CWordTranslateServer::OnAddWordToKnow(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnAddWordToKnow" << std::endl;
    ShowRemotePeer(request);
    AddWordToKnowReq_t reqData = AddRemoveWordReq(request);
    auto result = AddWordToKnow(reqData);
    std::string strVersion = AddRemoveRspToString(result);
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
    return ;
}

void CWordTranslateServer::OnAddWordToUnKnow(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnAddWordToUnKnow" << std::endl;
    ShowRemotePeer(request);
    AddWordToKnowReq_t reqData = AddRemoveWordReq(request);
    auto result = AddWordToUnKnown(reqData);
    std::string strVersion = AddRemoveRspToString(result);
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
    return;
}

int main() {
    CWordTranslateServer server;
    server.Start();
}
