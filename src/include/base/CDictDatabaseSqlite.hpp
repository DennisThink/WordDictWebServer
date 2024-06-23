#ifndef _C_DICT_DATA_BASE_SQLITE_H_
#define _C_DICT_DATA_BASE_SQLITE_H_
#include "CDictDatabaseInterface.hpp"
class CDictDatabaseSqlite:public CDictDatabaseInterface
{
public:
	CDictDatabaseSqlite(const std::string strFileName);
	virtual ~CDictDatabaseSqlite();
	virtual DictLineElem_t GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const DictLineElem_t& elem);
private:
	void DatabaseInit();
};
#endif