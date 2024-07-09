#include "CDictDatabaseInterface.hpp"
#include "mysql.h"
class CDictDatabaseMysql:public CDictDatabaseInterface
{
public:
	CDictDatabaseMysql();
	virtual ~CDictDatabaseMysql();
	virtual bool SetDictDatabaseConfig(const DataBaseConfigInterface* cfg) override;
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord) override;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
	virtual bool IsWordInDict(const std::string strWord) override;
	virtual bool DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
private:
	void InitTables();
	void InitLibrary();
	void UninitLibrary();
	MYSQL* m_mysql;
	MysqlDatabaseConfig m_config;
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
	virtual bool UpdateWordFrequency(const std::string strWord) override;
	virtual bool SetUserWordDatabaseConfig(const UserWordDatabaseConfig* cfg) override;
private:
	void InitTables();
	void InitLibrary();
	void UninitLibrary();
	MYSQL* m_mysql;
	UserWordDatabaseConfigMysql m_config;
};