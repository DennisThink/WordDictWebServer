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

    void OnEnglishToChineseMock(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultGet(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultPost(Response_SHARED_PTR response,
        Request_SHARED_PTR request);
private:
    EnglishToChineseReq_t GetReqFromRequest(Request_SHARED_PTR request);
    EnglishToChineseRsp_t CreateRspFromReq(const EnglishToChineseReq_t& req);
    bool MatchUrlMethodAndFunction();
    void ShowRemotePeer(Request_SHARED_PTR request);

private:
    HttpServer m_server;
    EnglishChineseWordDict m_dict;
};

CWordTranslateServer::CWordTranslateServer()
{
    m_server.config.port = 8080;
}

CWordTranslateServer::~CWordTranslateServer()
{

}

void CWordTranslateServer::ShowRemotePeer(Request_SHARED_PTR request)
{
    std::cout<< request->remote_endpoint().address().to_string() << ":"
        << request->remote_endpoint().port();
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
    std::string strChinese = m_dict.GetTranslation(req.m_strEnglish);
    if (strChinese.empty())
    {
        result.m_code = -1;
        result.m_strMsg = "New words";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = strChinese;
    }
    else
    {
        result.m_code = 0;
        result.m_strMsg = "success";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = strChinese;
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
}

void CWordTranslateServer::OnDefaultPost(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{
    ShowRemotePeer(request);
}


void CWordTranslateServer::OnEnglishToChineseMock(Response_SHARED_PTR response,
    Request_SHARED_PTR request)
{

}

int main() {
    CWordTranslateServer server;
    server.Start();
}
