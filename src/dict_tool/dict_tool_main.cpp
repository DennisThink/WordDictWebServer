#include <iostream>
#include <fstream> 
#include <string> 
#include <ostream>
#include <vector>
#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseSqlite.hpp"
#include "CDictDatabaseMySql.hpp"

int JsonDemo(int argc, char* argv[])
{
    JsonDatabaseConfig cfg;
    cfg.m_jsonFileName = "middle_school.json";

    CDictDatabaseJson databaseUtil;
    databaseUtil.SetDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;

    if (databaseUtil.IsWordInDict(strEnglish)) {
        databaseUtil.UpdateWordFrequency(strEnglish);
    }
    return 0;
}

int SqliteDemo(int argc, char* argv[])
{
    SqliteDatabaseConfig cfg;
    cfg.m_sqliteFileName = "ecdict_test.db";

    CDictDatabaseSqlite databaseUtil;
    databaseUtil.SetDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;

    if (databaseUtil.IsWordInDict(strEnglish)) {
        databaseUtil.UpdateWordFrequency(strEnglish);
    }
    return 0;
}

int MysqlDemo(int argc, char* argv[])
{
    MysqlDatabaseConfig cfg;
    cfg.m_strMysqlServerIp = "localhost";
    cfg.m_nMysqlServerPort = 3306;
    cfg.m_strMysqlUserName = "test";
    cfg.m_strMysqlPassoword = "test@1990";
    cfg.m_strDataBase = "en_cn_dict";

    CDictDatabaseMysql databaseUtil;
    databaseUtil.SetDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;

    if (databaseUtil.IsWordInDict(strEnglish)) {
        databaseUtil.UpdateWordFrequency(strEnglish);
    }
    return 0;
}

int SaveWordsFromJsonToMysql(int argc, char* argv[])
{
    CDictDatabaseJson JsonDatabaseUtil;
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "middle_school.json";
        cfg.m_nLevel = 10;
        JsonDatabaseUtil.SetDatabaseConfig(&cfg);
    }
    CDictDatabaseMysql mysqlDatabaseUtil;
    {
        MysqlDatabaseConfig cfg;
        cfg.m_strMysqlServerIp = "localhost";
        cfg.m_nMysqlServerPort = 3306;
        cfg.m_strMysqlUserName = "test";
        cfg.m_strMysqlPassoword = "test@1990";
        cfg.m_strDataBase = "en_cn_dict";
        mysqlDatabaseUtil.SetDatabaseConfig(&cfg);
    }
    auto allWords = JsonDatabaseUtil.GetAllWords();
    for (auto item : allWords) {
        std::cout << item;
        mysqlDatabaseUtil.InsertWordElem(item);
    }

    return 0;
}

int SaveWordsFromJsonToSqlite(int argc, char* argv[])
{
    CDictDatabaseJson JsonDatabaseUtil;
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "middle_school.json";
        cfg.m_nLevel = 10;
        JsonDatabaseUtil.SetDatabaseConfig(&cfg);
    }
    CDictDatabaseSqlite sqliteDatabaseUtil;
    {
        SqliteDatabaseConfig cfg;
        cfg.m_sqliteFileName = "ecdict_test.db";


        sqliteDatabaseUtil.SetDatabaseConfig(&cfg);
      
    }
    auto allWords = JsonDatabaseUtil.GetAllWords();
    for (auto item : allWords) {
        std::cout << item;
        sqliteDatabaseUtil.InsertWordElem(item);
    }

    return 0;
}
int main(int argc, char* argv[])
{
    //SaveWordsFromJsonToMysql(argc, argv);
    SaveWordsFromJsonToSqlite(argc, argv);
    //JsonDemo(argc, argv);
    //SqliteDemo(argc, argv);
    //MysqlDemo(argc, argv);
    return 0;
}