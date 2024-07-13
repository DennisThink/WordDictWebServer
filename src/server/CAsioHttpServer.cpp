#include "CAsioHttpServer.hpp"
CAsioHttpServer::CAsioHttpServer()
{
    m_server.config.port = 8080;
    /* {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "toefl_dict.json";
        cfg.m_nLevel = 10;
        m_dict.SetDictDatabaseConfig(&cfg);
    }*/

    /* {
        MysqlDatabaseConfig cfg;
        cfg.m_strMysqlServerIp = "localhost";
        cfg.m_nMysqlServerPort = 3306;
        cfg.m_strMysqlUserName = "test";
        cfg.m_strMysqlPassoword = "test@1990";
        cfg.m_strDataBase = "json_dict";
        m_dict.SetDictDatabaseConfig(&cfg);
    }*/
}


CAsioHttpServer::~CAsioHttpServer()
{

}


void CAsioHttpServer::ShowRemotePeer(Request_SHARED_PTR request)
{
    if (request)
    {
        std::cout << "Remote: " << std::endl;
    }

}

void CAsioHttpServer::Start()
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
    return ;
}

/*EnglishToChineseReq_t CAsioHttpServer::GetReqFromRequest(const std::string& strReq)
{
    EnglishToChineseReq_t result;
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
    return result;
}*/


/*std::string CAsioHttpServer::ToLower(const std::string strOrg)
{
    std::string strCopy = strOrg;
    std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return strCopy;
}*/


/* 
std::string CAsioHttpServer::WordTrim(const std::string strOrg)
{
    std::string strResult;
    for (auto iter = strOrg.begin(); iter != strOrg.end(); iter++) {
        if (('a' <= *iter) &&
            (*iter <= 'z')) {
            strResult += *iter;
        }
    }
    return strResult;
}
*/

/*AddWordToKnowReq_t CAsioHttpServer::AddRemoveWordReq(const std::string& strReq)
{
    AddWordToKnowReq_t result;
    {
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
}*/

/*EnglishToChineseRsp_t CAsioHttpServer::CreateRspFromReq(const EnglishToChineseReq_t& req)
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
}*/

/*
* (1) 收到整个英语句子。
(2) 拆分为多个单词。
(3) 确定改单词是否需要翻译
(3.1) 需要翻译，则翻译为汉语
(3.2) 不需要翻译，跳过
(4) 返回所有的翻译结果

*/
/*SentenceToWordsRsp_t CAsioHttpServer::TranslateSentence(const EnglishToChineseReq_t& req)
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
}*/

/*AddWordToKnownRsp_t  CAsioHttpServer::AddWordToKnow(const AddWordToKnowReq_t& req)
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
}*/

/*AddWordToUnKnownRsp_t CAsioHttpServer::AddWordToUnKnown(const AddWordToUnKnownReq_t& req)
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
}*/






/*std::string SentenceRspToString(const SentenceToWordsRsp_t& rsp)
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
}*/

bool CAsioHttpServer::MatchUrlMethodAndFunction()
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

    m_server.resource["^/v1/set_user_language_level$"]["POST"] = [this](Response_SHARED_PTR response,
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
void CAsioHttpServer::OnVersion(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    ShowRemotePeer(request);
    std::string strVersion = "VERSION 0.0.1";
    WriteRspString(response, strVersion);
}


void CAsioHttpServer::OnEnglishToChinese(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    ShowRemotePeer(request);

    std::string strReq = GetReqString(request);
    std::string strRsp = HandleEnglishToChinese(strReq);
    WriteRspString(response, strRsp);

}

void CAsioHttpServer::OnDefaultGet(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnDefaultGet" << std::endl;
    ShowRemotePeer(request);
    std::string strVersion = "Default Get";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

void CAsioHttpServer::OnDefaultPost(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnDefaultPost" << std::endl;
    ShowRemotePeer(request);
    std::string strVersion = "Default Post";
    *response << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << strVersion.length() << "\r\n\r\n"
        << strVersion;
}

void CAsioHttpServer::OnEnglishToWordTranslate(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnEnglishToWordTranslate" << std::endl;
    ShowRemotePeer(request);
    std::string strReq = GetReqString(request);
    std::string strRsp = HandleEnglishToWordTranslate(strReq);
    WriteRspString(response, strRsp);
}

void CAsioHttpServer::OnAddWordToKnow(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnAddWordToKnow" << std::endl;
    ShowRemotePeer(request);
    std::string strReq = GetReqString(request);
    std::string strRsp = HandleAddWordToKnow(strReq);
    WriteRspString(response, strRsp);
    return;
}

std::string CAsioHttpServer::GetReqString(Request_SHARED_PTR request)
{
    std::string strReq = request->content.string();
    return strReq;
}

void CAsioHttpServer::WriteRspString(Response_SHARED_PTR rsp, const std::string str)
{
    *rsp << "HTTP/1.1 200 OK\r\n"
        << "Content-Length: " << str.length() << "\r\n\r\n"
        << str;
}

void CAsioHttpServer::OnAddWordToUnKnow(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnAddWordToUnKnow" << std::endl;
    ShowRemotePeer(request);
    std::string strReq = GetReqString(request);
    std::string strRsp = HandleAddWordToUnKnow(strReq);
    WriteRspString(response, strRsp);
    
    return;
}

void CAsioHttpServer::OnSetUserLanguageLevel(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    std::cout << "OnSetUserLanguageLevel" << std::endl;
    ShowRemotePeer(request);
    std::string strReq = GetReqString(request);

}