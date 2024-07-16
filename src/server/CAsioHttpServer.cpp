#include "CAsioHttpServer.hpp"
CAsioHttpServer::CAsioHttpServer()
{
    m_server.config.port = 8080;
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
            OnSetUserLanguageLevel(response, request);
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
    std::cout << "REQ: " << strReq << std::endl;
    return strReq;
}

void CAsioHttpServer::WriteRspString(Response_SHARED_PTR rsp, const std::string str)
{
    std::cout << "RSP: " << str << std::endl;
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
    std::string strRsp = HandleSetUserLanguageLevel(strReq);
    WriteRspString(response, strRsp);
    return;
}