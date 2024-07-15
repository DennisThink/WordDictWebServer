#ifndef _C_HTTP_SERVER_INTERFACE_H_
#define _C_HTTP_SERVER_INTERFACE_H_
#include "CDictDatabaseInterface.hpp"
class CHttpServerInterface
{
public:
	CHttpServerInterface();
	virtual ~CHttpServerInterface() {};
	void SetServerCfg(const DictWebServerConfig& cfg);
	void InitDataBaseFromCfg();
	void SetDictAndUserWord(const CDictDataBase_PTR pDict, const CUserWordDataBase_PTR pWord);
	virtual void Start() = 0;
public:
	std::string HandleEnglishToChinese(const std::string& strReq);
	std::string HandleEnglishToWordTranslate(const std::string& strReq);
	std::string HandleAddWordToKnow(const std::string& strReq);
	std::string HandleAddWordToUnKnow(const std::string& strReq);
	std::string HandleSetUserLanguageLevel(const std::string& strReq);


	//SetUserLanguageLevelReq_t GetUserLanguageLevelReq(const std::string& strReq);
	SetUserLanguageLevelRsp_t SetUserLanguageLevel(const SetUserLanguageLevelReq_t& req);
	//EnglishToChineseReq_t GetReqFromRequest(const std::string& strReq);
	EnglishToChineseRsp_t CreateRspFromReq(const EnglishToChineseReq_t& req);
	SentenceToWordsRsp_t TranslateSentence(const EnglishToChineseReq_t& req);
	AddWordToKnownRsp_t  AddWordToKnow(const AddWordToKnowReq_t& req);
	AddWordToUnKnownRsp_t AddWordToUnKnown(const AddWordToUnKnownReq_t& req);
protected:
	std::string ToLower(const std::string strOrg);
	std::string WordTrim(const std::string strOrg);
protected:
	CDictDataBase_PTR m_dict;
	CUserWordDataBase_PTR m_userWord;
	DictWebServerConfig m_cfg;
};
#endif