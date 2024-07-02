#include "CDictDatabaseInterface.hpp"
#include "mysql.h"
class CDictDatabaseMysql:public CDictDatabaseInterface
{
public:
	CDictDatabaseMysql();
	virtual ~CDictDatabaseMysql();
	virtual bool SetDatabaseConfig(const DataBaseConfigInterface* cfg);
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem);
	virtual bool UpdateWordFrequency(const std::string strWord);
	virtual bool IsWordInDict(const std::string strWord);

	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken);
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken);
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken);

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken);
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken);
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken);

	bool IsWordInFrequencyTable(const std::string strWord);
private:
	void InitTables();
	void InitLibrary();
	void UninitLibrary();
	MYSQL* m_mysql;
	MysqlDatabaseConfig m_config;
};