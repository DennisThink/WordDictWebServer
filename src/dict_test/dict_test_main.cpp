#include "word_dict_struct.hpp"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseSqlite.hpp"
#include "CDictDatabaseMySql.hpp"

#include <string>
TEST_CASE("DictJson") {
    CHECK(1 == 1);
    DictDataBaseCfgJson cfg;
    cfg.m_jsonFileName = "middle_school.json";

    CDictDatabaseJson databaseUtil;
    CHECK(databaseUtil.SetDictDatabaseConfig(&cfg));
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");

    CHECK(databaseUtil.IsWordInDict(strEnglish));
    std::string strNewWord = "dennisthink";
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
    T_ENGLISH_CHINSE_TRANS newWord;
    newWord.F_ENGLISH = strNewWord;
    newWord.F_CHINESE = strNewWord;
    newWord.F_LEVEL = 1000;
    CHECK(databaseUtil.InsertWordElem(newWord));
    CHECK(databaseUtil.IsWordInDict(strNewWord));
    CHECK(databaseUtil.DeleteWordElem(newWord));
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
}

TEST_CASE("UserWordJson") {
    CUserWordDatabaseJson dataUtil;

    UserWordDataBaseCfgJson cfg;
    CHECK(dataUtil.SetUserWordDatabaseConfig(&cfg));

    std::string strWord = "apple";
    std::string strToken = "dennisthink";

    if (dataUtil.IsKnownWord(strWord, strToken))
    {
        CHECK(dataUtil.DeleteKnownWord(strWord, strToken));
        CHECK_FALSE(dataUtil.IsKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(dataUtil.InsertKnownWord(strWord, strToken));
        CHECK(dataUtil.IsKnownWord(strWord, strToken));

    }

    if (dataUtil.IsUnKnownWord(strWord, strToken))
    {
        CHECK(dataUtil.DeleteUnKnownWord(strWord, strToken));
        CHECK_FALSE(dataUtil.IsUnKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(dataUtil.InsertUnKnownWord(strWord, strToken));
        CHECK(dataUtil.IsUnKnownWord(strWord, strToken));

    }
}



TEST_CASE("DictSqlite") {
    CHECK(1 == 1);
    DictDataBaseCfgSqlite cfg;
    cfg.m_sqliteFileName = "ecdict_test.db";

    CDictDatabaseSqlite databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");

    CHECK(databaseUtil.IsWordInDict(strEnglish));
    std::string strNewWord = "dennisthink";
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
    T_ENGLISH_CHINSE_TRANS newWord;
    newWord.F_ENGLISH = strNewWord;
    newWord.F_CHINESE = strNewWord;
    newWord.F_LEVEL = 1000;
    CHECK(databaseUtil.InsertWordElem(newWord));
    CHECK(databaseUtil.IsWordInDict(strNewWord));
    CHECK(databaseUtil.DeleteWordElem(newWord));
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
    //CHECK(databaseUtil.UpdateWordFrequency(strEnglish));
}

TEST_CASE("ServerConfigMysql") {
    std::string strConfig = R"({
    "ServerIp":"127.0.0.1",
    "ServerPort":8080,
    "DataBaseType":"MYSQL",
    "DictDataBase":{
        "DataBaseIp":"localhost",
        "DataBasePort":3306,
        "UserName":"test",
        "PassWord":"test@1990",
        "DataBase":"json_dict"
    },
    "UserWordDataBase":{
        "DataBaseIp":"localhost",
        "DataBasePort":3306,
        "UserName":"test",
        "PassWord":"test@1990",
        "DataBase":"json_dict"
    }
   })";
    DictWebServerConfig cfg = FromJsonContent(strConfig);
    CHECK_EQ(cfg.m_strServerIp, "127.0.0.1");
    CHECK_EQ(cfg.m_nServerPort, 8080);
    CHECK_EQ(cfg.m_eDataBaseType, DataBaseType::MY_SQL);
    CHECK_FALSE(cfg.m_dictCfg == nullptr);
    if (nullptr != cfg.m_dictCfg)
    {
        DictDataBaseCfgMysql* pCfg = dynamic_cast<DictDataBaseCfgMysql*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == nullptr);
        if (nullptr != pCfg)
        {
            CHECK_EQ(pCfg->m_strMysqlServerIp, "localhost");
            CHECK_EQ(pCfg->m_nMysqlServerPort, 3306);
            CHECK_EQ(pCfg->m_strMysqlUserName, "test");
            CHECK_EQ(pCfg->m_strMysqlPassoword, "test@1990");
            CHECK_EQ(pCfg->m_strDataBase, "json_dict");
        }
    }
    else
    {
        CHECK_FALSE(true);
    }

    if (NULL != cfg.m_userWordCfg)
    {
        UserWordDataBaseCfgMysql* pCfg = dynamic_cast<UserWordDataBaseCfgMysql*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == NULL);
        if (NULL != pCfg)
        {
            CHECK_EQ(pCfg->m_strMysqlServerIp, "localhost");
            CHECK_EQ(pCfg->m_nMysqlServerPort, 3306);
            CHECK_EQ(pCfg->m_strMysqlUserName, "test");
            CHECK_EQ(pCfg->m_strMysqlPassoword, "test@1990");
            CHECK_EQ(pCfg->m_strDataBase, "json_dict");
        }
    }
    else
    {
        CHECK_FALSE(true);
    }
}


TEST_CASE("ServerConfigJson") {
    std::string strConfig = R"({
    "ServerIp":"127.0.0.1",
    "ServerPort":8080,
    "DataBaseType":"JSON",
    "DictDataBase":{
        "FileName":"middle_school.json",
        "Level":10
    },
    "UserWordDataBase":{
        "KnownWordFile":"KnownWordFile.json",
        "UnKnownWordFile":"UnKnowWordFile.json"
    }
   })";
    DictWebServerConfig cfg = FromJsonContent(strConfig);
    CHECK_EQ(cfg.m_strServerIp, "127.0.0.1");
    CHECK_EQ(cfg.m_nServerPort, 8080);
    CHECK_EQ(cfg.m_eDataBaseType, DataBaseType::JSON);
    CHECK_FALSE(cfg.m_dictCfg == nullptr);
    if (nullptr != cfg.m_dictCfg)
    {
        DictDataBaseCfgJson* pCfg = dynamic_cast<DictDataBaseCfgJson*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == nullptr);
        if (nullptr != pCfg)
        {
            CHECK_EQ(pCfg->m_jsonFileName, "middle_school.json");
            CHECK_EQ(pCfg->m_nLevel, 10);
        }
    }
    else
    {
        CHECK_FALSE(true);
    }

    if (NULL != cfg.m_userWordCfg)
    {
        UserWordDataBaseCfgJson* pCfg = dynamic_cast<UserWordDataBaseCfgJson*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == NULL);
        if (NULL != pCfg)
        {

            CHECK_EQ(pCfg->m_strKnownWordsFileName, "KnownWordFile.json");
            CHECK_EQ(pCfg->m_strKnownWordsFileName, "UnKnowWordFile.json");
        }
    }
    else
    {
        CHECK_FALSE(true);
    }
}

TEST_CASE("ServerConfigSqlite") {
    std::string strConfig = R"({
    "ServerIp":"127.0.0.1",
    "ServerPort":8080,
    "DataBaseType":"SQLITE",
    "DictDataBase":{
        "FileName":"ecdict_test.db"
    },
    "UserWordDataBase":{
        "FileName":"user_word.db"
    }
   })";
    DictWebServerConfig cfg = FromJsonContent(strConfig);
    CHECK_EQ(cfg.m_strServerIp, "127.0.0.1");
    CHECK_EQ(cfg.m_nServerPort, 8080);
    CHECK_EQ(cfg.m_eDataBaseType, DataBaseType::SQLITE);
    CHECK_FALSE(cfg.m_dictCfg == nullptr);
    if (nullptr != cfg.m_dictCfg)
    {
        DictDataBaseCfgSqlite* pCfg = dynamic_cast<DictDataBaseCfgSqlite*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == nullptr);
        if (nullptr != pCfg)
        {
            CHECK_EQ(pCfg->m_sqliteFileName, "ecdict_test.db");
        }
    }
    else
    {
        CHECK_FALSE(true);
    }

    if (NULL != cfg.m_userWordCfg)
    {
        UserWordDataBaseCfgSqlite* pCfg = dynamic_cast<UserWordDataBaseCfgSqlite*>(cfg.m_dictCfg.get());
        CHECK_FALSE(pCfg == NULL);
        if (NULL != pCfg)
        {

            CHECK_EQ(pCfg->m_strUserWordFileName, "user_word.db");
        }
    }
    else
    {
        CHECK_FALSE(true);
    }
}

TEST_CASE("UserWordSqlite") {
    CUserWordDatabaseSqlite dataUtil;

    UserWordDataBaseCfgSqlite cfg;
    CHECK(dataUtil.SetUserWordDatabaseConfig(&cfg));

    std::string strWord = "apple";
    std::string strToken = "dennisthink";

    if (dataUtil.IsKnownWord(strWord, strToken))
    {
        CHECK(dataUtil.DeleteKnownWord(strWord, strToken));
        CHECK_FALSE(dataUtil.IsKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(dataUtil.InsertKnownWord(strWord, strToken));
        CHECK(dataUtil.IsKnownWord(strWord, strToken));
    }

    if (dataUtil.IsUnKnownWord(strWord, strToken))
    {
        CHECK(dataUtil.DeleteUnKnownWord(strWord, strToken));
        CHECK_FALSE(dataUtil.IsUnKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(dataUtil.InsertUnKnownWord(strWord, strToken));
        CHECK(dataUtil.IsUnKnownWord(strWord, strToken));
    }
}

TEST_CASE("DictMySql") {
    CHECK(1 == 1);
    DictDataBaseCfgMysql cfg;
    cfg.m_strMysqlServerIp = "localhost";
    cfg.m_nMysqlServerPort = 3306;
    cfg.m_strMysqlUserName = "test";
    cfg.m_strMysqlPassoword = "test@1990";
    cfg.m_strDataBase = "json_dict";

    CDictDatabaseMysql databaseUtil;
    databaseUtil.SetDictDatabaseConfig(&cfg);
    std::string strEnglish = "apple";
    T_ENGLISH_CHINSE_TRANS trans = databaseUtil.GetTranslation("apple");

    CHECK(databaseUtil.IsWordInDict(strEnglish));
    std::string strNewWord = "dennisthink";
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
    T_ENGLISH_CHINSE_TRANS newWord;
    newWord.F_ENGLISH = strNewWord;
    newWord.F_CHINESE = strNewWord;
    newWord.F_LEVEL = 1000;
    CHECK(databaseUtil.InsertWordElem(newWord));
    CHECK(databaseUtil.IsWordInDict(strNewWord));
    CHECK(databaseUtil.DeleteWordElem(newWord));
    CHECK_FALSE(databaseUtil.IsWordInDict(strNewWord));
    //CHECK(databaseUtil.UpdateWordFrequency(strEnglish));
}

TEST_CASE("UserWordMysql") {
    CHECK(1 == 1);
    UserWordDataBaseCfgMysql cfg;
    cfg.m_strMysqlServerIp = "localhost";
    cfg.m_nMysqlServerPort = 3306;
    cfg.m_strMysqlUserName = "test";
    cfg.m_strMysqlPassoword = "test@1990";
    cfg.m_strDataBase = "json_dict";

    CUserWordDatabaseMysql databaseUtil;
    CHECK(databaseUtil.SetUserWordDatabaseConfig(&cfg));
    std::string strWord = "apple";
    std::string strToken = "dennisthink@hotmail.com";
    if (databaseUtil.IsKnownWord(strWord, strToken))
    {
        CHECK(databaseUtil.DeleteKnownWord(strWord, strToken));
        CHECK_FALSE(databaseUtil.IsKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(databaseUtil.InsertKnownWord(strWord, strToken));
        CHECK(databaseUtil.IsKnownWord(strWord, strToken));
    }

    if (databaseUtil.IsUnKnownWord(strWord, strToken)) 
    {
        CHECK(databaseUtil.DeleteUnKnownWord(strWord, strToken));
        CHECK_FALSE(databaseUtil.IsUnKnownWord(strWord, strToken));
    }
    else
    {
        CHECK(databaseUtil.InsertUnKnownWord(strWord, strToken));
        CHECK(databaseUtil.IsUnKnownWord(strWord, strToken));
    }
    if (databaseUtil.IsWordFrequencyExist(strWord, strToken))
    {
        CHECK(databaseUtil.UpdateWordFrequency(strWord, strToken));
    }
    else
    {
        CHECK(databaseUtil.InsertWordFrequency(strWord, strToken));
        CHECK(databaseUtil.UpdateWordFrequency(strWord, strToken));
    }
    CHECK(databaseUtil.UpdateUserLanguageLevel(strToken, 10));
    int nLevel = -1;
    CHECK(databaseUtil.GetUserLanguageLevel(strToken, nLevel));
    CHECK(databaseUtil.InsertUserLanguageLevel(strToken, nLevel));
}


int main(int argc, char* argv[])
{
    doctest::Context context;
    context.applyCommandLine(argc, argv);

    int res = context.run(); // run doctest

    // important - query flags (and --exit) rely on the user doing this
    if (context.shouldExit()) {
        // propagate the result of the tests
        return res;
    }
    return 0;
}