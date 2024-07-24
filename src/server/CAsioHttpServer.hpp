#ifndef _C_ASIO_HTTP_SERVER_H_
#define _C_ASIO_HTTP_SERVER_H_

#include "CHttpServerInterface.hpp"
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
class CAsioHttpServer:public CHttpServerInterface
{
public:
	CAsioHttpServer();
	virtual ~CAsioHttpServer();
	virtual void Start() override;
protected:
    void OnVersion(Response_SHARED_PTR response,
        Request_SHARED_PTR request);
    void OnEnglishToChinese(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnEnglishToWordTranslate(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultGet(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnDefaultPost(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnAddWordToKnow(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnAddWordToUnKnow(Response_SHARED_PTR response,
        Request_SHARED_PTR request);

    void OnSetUserLanguageLevel(Response_SHARED_PTR response,
        Request_SHARED_PTR request);
public:
protected:
private:
    std::string GetReqString(Request_SHARED_PTR request);
    void WriteRspString(Response_SHARED_PTR rsp, const std::string str);
    bool MatchUrlMethodAndFunction();
    void ShowRemotePeer(Request_SHARED_PTR request);
private:
    HttpServer m_server;
};
#endif