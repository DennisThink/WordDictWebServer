#ifndef _C_DICT_DATA_BASE_SQLITE_H_
#define _C_DICT_DATA_BASE_SQLITE_H_
#include "CDictDatabaseInterface.hpp"
class CDictDatabaseSqlite:public CDictDatabaseInterface
{
public:
	CDictDatabaseSqlite();
	virtual ~CDictDatabaseSqlite();
	virtual bool SetDatabaseConfig(const DataBaseConfigInterface* cfg);
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem);
	virtual bool IsWordInDict(const std::string strWord);
	virtual bool UpdateWordFrequency(const std::string strWord);

	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken);
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken);
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken);

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken);
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken);
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken);
private:
	void DatabaseInit(const std::string strFileName);
	SqliteDatabaseConfig m_config;
};
#endif