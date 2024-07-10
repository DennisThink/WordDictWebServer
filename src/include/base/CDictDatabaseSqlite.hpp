#ifndef _C_DICT_DATA_BASE_SQLITE_H_
#define _C_DICT_DATA_BASE_SQLITE_H_
#include "CDictDatabaseInterface.hpp"
class CDictDatabaseSqlite:public CDictDatabaseInterface
{
public:
	CDictDatabaseSqlite();
	virtual ~CDictDatabaseSqlite();
	virtual bool SetDictDatabaseConfig(const DictDataBaseCfg* cfg) override;
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord) override;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
	virtual bool IsWordInDict(const std::string strWord) override;
	virtual bool DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;

private:
	void DatabaseInit(const std::string strFileName);
	DictDataBaseCfgSqlite m_config;
};

class CUserWordDatabaseSqlite :public CUserWordDatabaseInterface
{
public:
	virtual bool SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg)  override { return true; };
	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken) override;

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken) override;
	
	virtual bool UpdateWordFrequency(const std::string strWord) override;
};
#endif