#include "CCppHttpLibServer.hpp"
#include <iostream>
CCppHttpLibServer::CCppHttpLibServer()
{

}
CCppHttpLibServer::~CCppHttpLibServer()
{

}
void CCppHttpLibServer::Start()
{
	InitUrlRoute();
	m_server.listen("0.0.0.0", 8080);
}

void CCppHttpLibServer::OnGetDefault(const httplib::Request&, httplib::Response& res)
{
	std::cout << "OnGetDefault" << std::endl;
	res.set_content("OnGetDefault", "text/plain");
}

void CCppHttpLibServer::OnPostDefault(const httplib::Request&, httplib::Response& res)
{
	std::cout << "OnPostDefault" << std::endl;
	res.set_content("OnPostDefault", "text/plain");
}

void CCppHttpLibServer::OnVersion(const httplib::Request&, httplib::Response& res)
{

}
void CCppHttpLibServer::OnEnglishToChinese(const httplib::Request& req, httplib::Response& res)
{
	std::string strReq = GetReqString(req);
	std::string strRsp = HandleEnglishToChinese(strReq);
	WriteRspString(res, strRsp);
}

void CCppHttpLibServer::OnEnglishToWordTranslate(const httplib::Request& req, httplib::Response& res)
{
	std::string strReq = GetReqString(req);
	std::string strRsp = HandleEnglishToWordTranslate(strReq);
	WriteRspString(res, strRsp);
}

void CCppHttpLibServer::OnDefaultGet(const httplib::Request&, httplib::Response& res)
{

}

void CCppHttpLibServer::OnDefaultPost(const httplib::Request&, httplib::Response& res)
{

}

void CCppHttpLibServer::OnAddWordToKnow(const httplib::Request&, httplib::Response& res)
{

}

void CCppHttpLibServer::OnAddWordToUnKnow(const httplib::Request&, httplib::Response& res)
{

}

std::string CCppHttpLibServer::GetReqString(const httplib::Request& req)
{
	std::string strRsp = req.body;
	return strRsp;
}
void CCppHttpLibServer::WriteRspString(httplib::Response& res, const std::string strRsp)
{
	res.set_content(strRsp, "text/json");
}

void CCppHttpLibServer::InitUrlRoute()
{
	m_server.Get("/version", [this](const httplib::Request& req, httplib::Response& rsp) {
		std::cout << "GET version" << std::endl;
		this->OnGetDefault(req, rsp);
	});

	m_server.Post("/version", [this](const httplib::Request& req, httplib::Response& rsp) {
		std::cout << "POST version" << std::endl;
		this->OnPostDefault(req, rsp);
	});



    m_server.Post("^/v1/english_to_chinese$",[this](const httplib::Request& req, httplib::Response& rsp) {
            OnEnglishToChinese(req, rsp);
    });
    
    m_server.Post("^/v1/sentence_to_words$",[this](const httplib::Request& req, httplib::Response& rsp) {
            OnEnglishToWordTranslate(req, rsp);
    });

    m_server.Post("^/v1/add_word_to_known$",[this](const httplib::Request& req, httplib::Response& rsp) {
            OnAddWordToKnow(req, rsp);
    });

    m_server.Post("^/v1/add_word_to_unknown$",[this](const httplib::Request& req, httplib::Response& rsp) {
            OnAddWordToUnKnow(req, rsp);
    });
}