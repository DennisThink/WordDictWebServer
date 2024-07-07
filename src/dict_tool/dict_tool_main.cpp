#include <iostream>
#include <fstream> 
#include <string> 
#include <ostream>
#include <vector>
#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseSqlite.hpp"
#include "CDictDatabaseMySql.hpp"
#include "dict_tool.hpp"

int JsonDemo(int argc, char* argv[])
{
    JsonDatabaseConfig cfg;
    cfg.m_jsonFileName = "middle_school.json";

    CDictDatabaseJson databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;

    if (databaseUtil.IsWordInDict(strEnglish)) {
    }

    /*
    //add new word to unknown
    {
        std::string strToken = "dennisthink@hotmail.com";
        if (databaseUtil.IsKnownWord(strEnglish,strToken)) {
            databaseUtil.InsertUnKnownWord(strEnglish, strToken);
            databaseUtil.DeleteKnownWord(strEnglish, strToken);
        }
        else{
            databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
            databaseUtil.InsertKnownWord(strEnglish, strToken);
        }
    }

    //add new word to know
    {
        std::string strToken = "dennisthink@hotmail.com";
        if (databaseUtil.IsUnKnownWord(strEnglish, strToken)) {
            databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
            databaseUtil.InsertKnownWord(strEnglish, strToken);
        }
        else
        {
            databaseUtil.InsertUnKnownWord(strEnglish, strToken);
            databaseUtil.DeleteKnownWord(strEnglish, strToken);
        }
    }*/
    return 0;
}

int SqliteDemo(int argc, char* argv[])
{
    SqliteDatabaseConfig cfg;
    cfg.m_sqliteFileName = "ecdict_test.db";

    CDictDatabaseSqlite databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;
    /*
    if (databaseUtil.IsWordInDict(strEnglish)) {
        databaseUtil.UpdateWordFrequency(strEnglish);
    }
    {
        //add new word to unknown
        {
            std::string strToken = "dennisthink@hotmail.com";
            if (databaseUtil.IsKnownWord(strEnglish, strToken)) {
                databaseUtil.InsertUnKnownWord(strEnglish, strToken);
                databaseUtil.DeleteKnownWord(strEnglish, strToken);
            }
            else {
                databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
                databaseUtil.InsertKnownWord(strEnglish, strToken);
            }
        }

        //add new word to know
        {
            std::string strToken = "dennisthink@hotmail.com";
            if (databaseUtil.IsUnKnownWord(strEnglish, strToken)) {
                databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
                databaseUtil.InsertKnownWord(strEnglish, strToken);
            }
            else
            {
                databaseUtil.InsertUnKnownWord(strEnglish, strToken);
                databaseUtil.DeleteKnownWord(strEnglish, strToken);
            }
        }
    }*/
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
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    std::cout << "EN: " << trans.F_ENGLISH << "   CN:  " << trans.F_CHINESE << "  LEVEL: " << trans.F_LEVEL << std::endl;
    
    /*
    if (databaseUtil.IsWordInDict(strEnglish)) {
        databaseUtil.UpdateWordFrequency(strEnglish);
    }
    {
        //add new word to unknown
        {
            std::string strToken = "dennisthink@hotmail.com";
            if (databaseUtil.IsKnownWord(strEnglish, strToken)) {
                databaseUtil.InsertUnKnownWord(strEnglish, strToken);
                databaseUtil.DeleteKnownWord(strEnglish, strToken);
            }
            else {
                databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
                databaseUtil.InsertKnownWord(strEnglish, strToken);
            }
        }

        //add new word to know
        {
            std::string strToken = "dennisthink@hotmail.com";
            if (databaseUtil.IsUnKnownWord(strEnglish, strToken)) {
                databaseUtil.DeleteUnKnownWord(strEnglish, strToken);
                databaseUtil.InsertKnownWord(strEnglish, strToken);
            }
            else
            {
                databaseUtil.InsertUnKnownWord(strEnglish, strToken);
                databaseUtil.DeleteKnownWord(strEnglish, strToken);
            }
        }
    }*/
    return 0;
}

int SaveWordsFromJsonToMysql(int argc, char* argv[])
{
    CDictDatabaseJson JsonDatabaseUtil;
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = "middle_school.json";
        cfg.m_nLevel = 10;
        JsonDatabaseUtil.SetDictDatabaseConfig(&cfg);
    }
    CDictDatabaseMysql mysqlDatabaseUtil;
    {
        MysqlDatabaseConfig cfg;
        cfg.m_strMysqlServerIp = "localhost";
        cfg.m_nMysqlServerPort = 3306;
        cfg.m_strMysqlUserName = "test";
        cfg.m_strMysqlPassoword = "test@1990";
        cfg.m_strDataBase = "en_cn_dict";
        mysqlDatabaseUtil.SetDictDatabaseConfig(&cfg);
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
        JsonDatabaseUtil.SetDictDatabaseConfig(&cfg);
    }
    CDictDatabaseSqlite sqliteDatabaseUtil;
    {
        SqliteDatabaseConfig cfg;
        cfg.m_sqliteFileName = "ecdict_test.db";


        sqliteDatabaseUtil.SetDictDatabaseConfig(&cfg);
      
    }
    auto allWords = JsonDatabaseUtil.GetAllWords();
    for (auto item : allWords) {
        std::cout << item;
        sqliteDatabaseUtil.InsertWordElem(item);
    }

    return 0;
}

void SaveWordsToMysql()
{
    CdictTool tool;
    auto allWords = tool.GetAllWords("ecdict.csv");

    MysqlDatabaseConfig cfg;
    cfg.m_strMysqlServerIp = "localhost";
    cfg.m_nMysqlServerPort = 3306;
    cfg.m_strMysqlUserName = "test";
    cfg.m_strMysqlPassoword = "test@1990";
    cfg.m_strDataBase = "dict_release";

    CDictDatabaseMysql databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    for (auto& item : allWords) {
        std::cout << item.GetTrans() << std::endl;
        if (item.m_strTranslation.length() < 128)
        {
            T_ENGLISH_CHINSE_TRANS elem;
            elem.F_ENGLISH = item.m_strWord;
            elem.F_CHINESE = item.m_strTranslation;
            elem.F_LEVEL = 1;
            databaseUtil.InsertWordElem(elem);
        }
        else
        {
            T_ENGLISH_CHINSE_TRANS elem;
            elem.F_ENGLISH = item.m_strWord;
            elem.F_CHINESE = item.m_strTranslation.substr(0, 127);
            elem.F_LEVEL = 1;
            databaseUtil.InsertWordElem(elem);
        }
    }
}

void SaveJsonToMysql(const std::string strName, const int level)
{
    CDictDatabaseJson JsonDatabaseUtil;
    {
        JsonDatabaseConfig cfg;
        cfg.m_jsonFileName = strName;
        cfg.m_nLevel = level;
        JsonDatabaseUtil.SetDictDatabaseConfig(&cfg);
    }
    MysqlDatabaseConfig cfg;
    cfg.m_strMysqlServerIp = "localhost";
    cfg.m_nMysqlServerPort = 3306;
    cfg.m_strMysqlUserName = "test";
    cfg.m_strMysqlPassoword = "test@1990";
    cfg.m_strDataBase = "json_dict";

    CDictDatabaseMysql databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");
    auto allWords = JsonDatabaseUtil.GetAllWords();
    for (auto item : allWords) {
        std::cout << item << std::endl;
        if (item.F_CHINESE.length() < 128)
        {
            databaseUtil.InsertWordElem(item);
        }
        else
        {
            item.F_CHINESE = item.F_CHINESE.substr(0, 127);
            databaseUtil.InsertWordElem(item);
        }
    }

}
int main(int argc, char* argv[])
{
    //SaveWordsFromJsonToMysql(argc, argv);
    //SaveWordsFromJsonToSqlite(argc, argv);
    //JsonDemo(argc, argv);
    //SqliteDemo(argc, argv);
    //MysqlDemo(argc, argv);
    //SaveWordsToMysql();
    {
        SaveJsonToMysql("10-middle-school.json",10);
        SaveJsonToMysql("15-high-school.json", 15);
        SaveJsonToMysql("20-CET4-university.json", 20);
        SaveJsonToMysql("25-CET6-university.json", 25);
        SaveJsonToMysql("30-Master-Entry.json", 30);
        SaveJsonToMysql("35-SAT-TEST.json", 35);
        SaveJsonToMysql("40-toefl-dict.json", 40);
    }
    return 0;
}
