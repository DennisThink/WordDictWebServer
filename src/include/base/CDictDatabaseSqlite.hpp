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
private:
	void DatabaseInit(const std::string strFileName);
	SqliteDatabaseConfig m_config;
};
#endif