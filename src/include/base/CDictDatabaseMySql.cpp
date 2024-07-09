#include "CDictDatabaseMySql.hpp"
#include <iostream>
CDictDatabaseMysql::CDictDatabaseMysql()
{
	InitLibrary();
}

CDictDatabaseMysql::~CDictDatabaseMysql()
{
	UninitLibrary();
}

CUserWordDatabaseMysql::CUserWordDatabaseMysql()
{
	InitLibrary();
}

CUserWordDatabaseMysql::~CUserWordDatabaseMysql()
{
	UninitLibrary();
}
bool CUserWordDatabaseMysql::InsertKnownWord(const std::string strWord, const std::string strToken)
{
	std::string strCreateSql = R"(INSERT INTO T_KNOWN_WORDS(
			F_ENGLISH,
			F_TOKEN) VALUES('%s','%s');)";
	char buff[512] = { 0 };
	sprintf(buff, strCreateSql.c_str(),strWord.c_str(), strToken.c_str());
	std::cout << buff << std::endl;
	int nResult = mysql_query(m_mysql, buff);
	mysql_commit(m_mysql);
	if (nResult == 0) {
		return true;
	}
	else {
		return false;
	}
	return false;
}
void CUserWordDatabaseMysql::InitTables()
{

}
void CUserWordDatabaseMysql::InitLibrary()
{
	m_mysql = NULL;
	int argc = 0;
	char** argv = NULL;
	if (mysql_library_init(argc, argv, NULL)) {
		fprintf(stderr, "could not initialize MySQL client library\n");
		exit(1);
	}

	m_mysql = mysql_init(m_mysql);
}
void CUserWordDatabaseMysql::UninitLibrary()
{
	mysql_close(m_mysql);
	m_mysql = NULL;
	mysql_library_end();
}
bool CUserWordDatabaseMysql::DeleteKnownWord(const std::string strWord, const std::string strToken)
{
	bool bResult = false;
	std::string strSelect = R"(DELETE FROM T_KNOWN_WORDS WHERE F_ENGLISH="%s" AND F_TOKEN="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str(),strToken.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					bResult = true;
					putchar('\n');
					break;
				}

				mysql_free_result(result);
			}
		}
	}
	return bResult;
}

bool CUserWordDatabaseMysql::IsKnownWord(const std::string strWord, const std::string strToken)
{
	bool bResult = false;
	std::string strSelect = R"(SELECT F_ENGLISH,F_TOKEN FROM T_KNOWN_WORDS WHERE F_ENGLISH="%s" AND F_TOKEN="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str(),strToken.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					bResult = true;
					putchar('\n');
					break;
				}

				mysql_free_result(result);
			}
		}
	}
	return bResult;
}

bool CUserWordDatabaseMysql::InsertUnKnownWord(const std::string strWord, const std::string strToken)
{
	std::string strCreateSql = R"(INSERT INTO T_UNKNOWN_WORDS(
			F_ENGLISH,
			F_TOKEN) VALUES('%s','%s');)";
	char buff[512] = { 0 };
	sprintf(buff, strCreateSql.c_str(), strWord.c_str(), strToken.c_str());
	std::cout << buff << std::endl;
	int nResult = mysql_query(m_mysql, buff);
	mysql_commit(m_mysql);
	if (nResult == 0) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

bool CUserWordDatabaseMysql::DeleteUnKnownWord(const std::string strWord, const std::string strToken)
{
	bool bResult = false;
	std::string strSelect = R"(DELETE FROM T_UNKNOWN_WORDS WHERE F_ENGLISH="%s" AND F_TOKEN="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str(),strToken.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					bResult = true;
					putchar('\n');
					break;
				}

				mysql_free_result(result);
			}
		}
	}
	return bResult;
}

bool  CUserWordDatabaseMysql::SetUserWordDatabaseConfig(const UserWordDatabaseConfig* cfg)
{
	if (nullptr != cfg)
	{
		
		if (nullptr != cfg && NULL != cfg)
		{
			m_config = *((UserWordDatabaseConfigMysql*)(cfg));
			if (NULL != m_mysql)
			{
				if (!mysql_real_connect(m_mysql,       /* MYSQL structure to use */
					m_config.m_strMysqlServerIp.c_str(),         /* server hostname or IP address */
					m_config.m_strMysqlUserName.c_str(),         /* mysql user */
					m_config.m_strMysqlPassoword.c_str(),          /* password */
					m_config.m_strDataBase.c_str(),               /* default database to use, NULL for none */
					m_config.m_nMysqlServerPort,           /* port number, 0 for default */
					NULL,        /* socket file or named pipe name */
					CLIENT_FOUND_ROWS /* connection flags */)) {
					fprintf(stderr, "mysql_real_connect() failed: '%s'\n", mysql_error(m_mysql));
					puts("Connect failed\n");
				}
				else {
					puts("Connect OK\n");
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
bool CUserWordDatabaseMysql::UpdateWordFrequency(const std::string strWord)
{
	return false;
}
bool CUserWordDatabaseMysql::IsUnKnownWord(const std::string strWord, const std::string strToken)
{
	bool bResult = false;
	std::string strSelect = R"(SELECT F_ENGLISH,F_TOKEN FROM T_UNKNOWN_WORDS WHERE F_ENGLISH="%s" AND F_TOKEN="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str(),strToken.c_str());
	std::cout << "SQL: " << buff << std::endl;
	try
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					bResult = true;
					putchar('\n');
					break;
				}

				mysql_free_result(result);
			}
		}
	}
	catch (std::exception& ec) {

	}
	return bResult;
}


bool CDictDatabaseMysql::SetDictDatabaseConfig(const DataBaseConfigInterface* cfg)
{
	if (nullptr != cfg && NULL != cfg)
	{
		m_config = *(MysqlDatabaseConfig*)(cfg);
		if(NULL != m_mysql)
		{
			if (!mysql_real_connect(m_mysql,       /* MYSQL structure to use */
				m_config.m_strMysqlServerIp.c_str(),         /* server hostname or IP address */
				m_config.m_strMysqlUserName.c_str(),         /* mysql user */
				m_config.m_strMysqlPassoword.c_str(),          /* password */
				m_config.m_strDataBase.c_str(),               /* default database to use, NULL for none */
				m_config.m_nMysqlServerPort,           /* port number, 0 for default */
				NULL,        /* socket file or named pipe name */
				CLIENT_FOUND_ROWS /* connection flags */)) {
				fprintf(stderr, "mysql_real_connect() failed: '%s'\n", mysql_error(m_mysql));
				puts("Connect failed\n");
			}
			else {
				puts("Connect OK\n");
			}
		}
		return true;
	}
	else {
		return false;
	}
}


T_ENGLISH_CHINSE_TRANS CDictDatabaseMysql::GetTranslation(const std::string strWord)
{
	T_ENGLISH_CHINSE_TRANS transResult;
	std::string strSelect = R"(SELECT F_ENGLISH,F_CHINESE,F_LEVEL FROM T_ENGLISH_CHINESE WHERE F_ENGLISH="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					transResult.F_ENGLISH = row[0];
					transResult.F_CHINESE = row[1];
					transResult.F_LEVEL = std::atoi(row[2]);
					putchar('\n');

					break;
				}

				mysql_free_result(result);
			}
		}
	}
	return transResult;
}

bool CDictDatabaseMysql::InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
	std::string strCreateSql = R"(INSERT INTO T_ENGLISH_CHINESE(
			F_ENGLISH,
			F_CHINESE,
			F_LEVEL) VALUES('%s','%s',%d);)";
	char buff[1024] = { 0 };
	sprintf(buff, strCreateSql.c_str(), elem.F_ENGLISH.c_str(), elem.F_CHINESE.c_str(), elem.F_LEVEL);
	std::cout << buff << std::endl;
	int nResult = mysql_query(m_mysql, buff);
	mysql_commit(m_mysql);
	if (nResult == 0) {
		return true;
	}
	else {
		return false;
	}
	return false;
}

void CDictDatabaseMysql::InitTables()
{
	{
		if (NULL != m_mysql) {
			std::string strCreateSql = R"(CREATE TABLE T_ENGLISH_CHINESE(
			F_ID int NOT NULL AUTO_INCREMENT,
			F_ENGLISH varchar(64),
			F_CHINESE varchar(512),
			F_LEVEL int,
			PRIMARY KEY(F_ID)
			); )";
			int nResult = mysql_query(m_mysql, strCreateSql.c_str());
			if (nResult == 0) {
			}
			else {
			}
		}
	}
	{
		if (NULL != m_mysql) {
			std::string strCreateSql = R"(CREATE TABLE T_WORD_FREQUENCY(
											F_ID int NOT NULL AUTO_INCREMENT,
											F_ENGISH varchar(64),
											F_TOKEN varchar(128),
											F_TIMES int,
											PRIMARY KEY (F_ID)); )";
			int nResult = mysql_query(m_mysql, strCreateSql.c_str());
			if (nResult == 0) {
			}
			else {
			}
		}
	}
	{
		if (NULL != m_mysql) {
			std::string strCreateSql = R"(CREATE TABLE T_KNOWN_WORDS(
											F_ID int NOT NULL AUTO_INCREMENT,
											F_ENGLISH varchar(64),
											F_TOKEN varchar(128),
											PRIMARY KEY (F_ID)); )";
			int nResult = mysql_query(m_mysql, strCreateSql.c_str());
			if (nResult == 0) {
			}
			else {
			}
		}
	}
	{
		if (NULL != m_mysql) {
			std::string strCreateSql = R"(CREATE TABLE T_UNKNOWN_WORDS(
											F_ID int NOT NULL AUTO_INCREMENT,
											F_ENGLISH varchar(64),
											F_TOKEN varchar(128),
											PRIMARY KEY (F_ID)); )";
			int nResult = mysql_query(m_mysql, strCreateSql.c_str());
			if (nResult == 0) {
			}
			else {
			}
		}
	}
}

void CDictDatabaseMysql::InitLibrary()
{
	m_mysql = NULL;
	int argc = 0;
	char** argv = NULL;
	if (mysql_library_init(argc, argv, NULL)) {
		fprintf(stderr, "could not initialize MySQL client library\n");
		exit(1);
	}

	m_mysql = mysql_init(m_mysql);
	
}

void CDictDatabaseMysql::UninitLibrary()
{
	mysql_close(m_mysql);
	m_mysql = NULL;
	mysql_library_end();
}


bool CDictDatabaseMysql::IsWordInDict(const std::string strWord)
{
	bool bResult = false;
	std::string strSelect = R"(SELECT F_ENGLISH FROM T_ENGLISH_CHINESE WHERE F_ENGLISH="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), strWord.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			MYSQL_RES* result = mysql_store_result(m_mysql);

			if (!result) {
				printf("Couldn't get results set: %s\n", mysql_error(m_mysql));
			}
			else {
				MYSQL_ROW row;
				unsigned int num_fields = mysql_num_fields(result);
				printf("get results set: %s\n", mysql_error(m_mysql));
				while ((row = mysql_fetch_row(result))) {
					printf("ROW loop get results set: %s\n", mysql_error(m_mysql));
					bResult = true;
					putchar('\n');

					break;
				}

				mysql_free_result(result);
			}
		}
	}
	return bResult;
}

bool CDictDatabaseMysql::DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
	bool bResult = false;
	std::string strSelect = R"(DELETE FROM T_ENGLISH_CHINESE WHERE F_ENGLISH="%s";)";
	char buff[256] = { 0 };
	sprintf(buff, strSelect.c_str(), elem.F_ENGLISH.c_str());
	std::cout << "SQL: " << buff << std::endl;
	{
		if (mysql_query(m_mysql, buff)) {
			printf("Query failed: %s\n", mysql_error(m_mysql));
		}
		else {
			bResult = true;
		}
	}
	return bResult;
}