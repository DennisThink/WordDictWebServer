#include "CDictDatabaseMySql.hpp"
#include <mysqlx/xdevapi.h>
#include <iostream>
CDictDatabaseMysql::CDictDatabaseMysql(const std::string strFileName):CDictDatabaseInterface(strFileName)
{
	std::string host = "localhost";
	std::string strUser = "test";
	std::string strPassword = "test@1990";
	std::string strDb = "en_cn_dict";
	mysqlx::SessionSettings mysqlSet(host,strUser.c_str(), strPassword, strDb.c_str());
	mysqlx::Session mysqlDbUtil(mysqlSet);
	mysqlx::RowResult res = mysqlDbUtil.sql("show variables like 'version'").execute();
	std::stringstream version;

	std::cout << res.fetchOne().get(1).get<std::string>()<<std::endl;
}

CDictDatabaseMysql::~CDictDatabaseMysql()
{

}
DictLineElem_t CDictDatabaseMysql::GetTranslation(const std::string strWord)
{
	DictLineElem_t result;
	return result;
}

bool CDictDatabaseMysql::InsertWordElem(const DictLineElem_t& elem)
{
	return false;
}