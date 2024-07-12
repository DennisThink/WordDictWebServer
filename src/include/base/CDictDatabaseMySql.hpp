#ifndef _C_DICT_DATABASE_MYSQL_H_
#define _C_DICT_DATABASE_MYSQL_H_
#include "CDictDatabaseInterface.hpp"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include "mysql.h"
class CDictDatabaseMysql:public CDictDatabaseInterface
{
public:
	CDictDatabaseMysql();
	virtual ~CDictDatabaseMysql();
	virtual bool SetDictDatabaseConfig(const DictDataBaseCfg* cfg) override;
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord) override;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
	virtual bool IsWordInDict(const std::string strWord) override;
	virtual bool DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
private:
	void InitTables();
	void InitLibrary();
	void UninitLibrary();
	MYSQL* m_mysql;
	DictDataBaseCfgMysql m_config;
};

class CUserWordDatabaseMysql :public CUserWordDatabaseInterface
{
public:
	CUserWordDatabaseMysql();
	virtual ~CUserWordDatabaseMysql();
	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken) override;

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken) override;

	virtual bool SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg) override;

	virtual bool UpdateWordFrequency(const std::string strWord, const std::string strToken) override;
	virtual bool InsertWordFrequency(const std::string strWord, const std::string strToken) override;
	virtual bool IsWordFrequencyExist(const std::string strWord, const std::string strToken) override;

	virtual bool InsertUserLanguageLevel(const std::string strToken, const int nLevel) override;
	virtual bool UpdateUserLanguageLevel(const std::string strToken, const int nLevel) override;
	virtual bool GetUserLanguageLevel(const std::string strToken, int& nLevel) override;
private:
	void InitTables();
	void InitLibrary();
	void UninitLibrary();
	MYSQL* m_mysql;
	UserWordDataBaseCfgMysql m_config;
};
#endif