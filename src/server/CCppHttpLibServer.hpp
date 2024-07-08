#ifndef _C_CPP_HTTP_LIB_SERVER_H_
#define _C_CPP_HTTP_LIB_SERVER_H_
#include "httplib.h"
class CCppHttpLibServer
{
public:
	CCppHttpLibServer();
	virtual ~CCppHttpLibServer();
	void Start();
	void InitUrlRoute();
	void OnGetDefault(const httplib::Request&, httplib::Response& res);
	void OnPostDefault(const httplib::Request&, httplib::Response& res);
    void OnVersion(const httplib::Request&, httplib::Response& res);
    void OnEnglishToChinese(const httplib::Request&, httplib::Response& res);

    void OnEnglishToWordTranslate(const httplib::Request&, httplib::Response& res);

    void OnDefaultGet(const httplib::Request&, httplib::Response& res);

    void OnDefaultPost(const httplib::Request&, httplib::Response& res);

    void OnAddWordToKnow(const httplib::Request&, httplib::Response& res);

    void OnAddWordToUnKnow(const httplib::Request&, httplib::Response& res);
private:
	httplib::Server m_server;
};
#endif