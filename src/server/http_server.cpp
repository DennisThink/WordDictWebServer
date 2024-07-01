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
private:
    EnglishToChineseReq_t GetReqFromRequest(Request_SHARED_PTR request);
    EnglishToChineseRsp_t CreateRspFromReq(const EnglishToChineseReq_t& req);
    SentenceToWordsRsp_t TranslateSentence(const EnglishToChineseReq_t& req);
    bool MatchUrlMethodAndFunction();
    void ShowRemotePeer(Request_SHARED_PTR request);

private:
    HttpServer m_server;
    CDictDatabaseJson m_LowDict;
    CDictDatabaseJson m_highDict;
};

CWordTranslateServer::CWordTranslateServer()
{
    m_server.config.port = 8080;
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "middle_school.json";
        cfg.m_nLevel = 4;
        m_LowDict.SetDatabaseConfig(&cfg);
    }
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "toefl_dict.json";
        cfg.m_nLevel = 10;
        m_highDict.SetDatabaseConfig(&cfg);
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


EnglishToChineseRsp_t CWordTranslateServer::CreateRspFromReq(const EnglishToChineseReq_t& req)
{
    EnglishToChineseRsp_t result;
    std::string strChinese = m_highDict.GetTranslation(req.m_strEnglish).F_CHINESE;
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

SentenceToWordsRsp_t CWordTranslateServer::TranslateSentence(const EnglishToChineseReq_t& req)
{
    SentenceToWordsRsp_t result;
    std::vector<EnglishToChineseData_t> transResultArray;
    std::map<std::string, int> words;
    std::string strSentence = req.m_strEnglish;
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;
    startIndex = endIndex;
    std::cout << "Sentence:  " << strSentence << std::endl;
    while(endIndex != std::string::npos) {
        endIndex = strSentence.find_first_of(" ", startIndex);
        std::string word = strSentence.substr(startIndex, endIndex - startIndex);
        std::cout << "Word:  "<<word << std::endl;
        words.insert({ word,1 });
        startIndex = endIndex+1;
    }
    for (auto item : words) {
        if (m_LowDict.IsWordInDict(item.first)) {
            std::cout << "Word Already Know: " << item.first << std::endl;
        }
        else {
            if (m_highDict.IsWordInDict(item.first)) 
            {
                EnglishToChineseData_t elem;
                elem.m_strEnglish = item.first;
                elem.m_strChinese = m_highDict.GetTranslation(item.first).F_CHINESE;
                std::cout << "Engish: " << item.first << "   Chinese: " << elem.m_strChinese << std::endl;
                transResultArray.push_back(elem);
            }
            else
            {
                std::cout << "CAN NOT TRANS EN: " << item.first <<std::endl;
            }

        }
    }
    result.m_code = 0;
    result.m_strMsg = "success";
    result.m_data = transResultArray;
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
    ShowRemotePeer(request);
    std::string strVersion = "Default Get";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

void CWordTranslateServer::OnDefaultPost(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
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
    ShowRemotePeer(request);
    EnglishToChineseReq_t reqData = GetReqFromRequest(request);
    auto result = TranslateSentence(reqData);
    std::string strVersion = SentenceRspToString(result);
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

int main() {
    CWordTranslateServer server;
    server.Start();
}
