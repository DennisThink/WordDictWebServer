#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseSqlite.hpp"

//#include "CDictDatabaseMySql.hpp"



TEST_CASE("DictJson") {
	CHECK(1==1);
    JsonDatabaseConfig cfg;
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

    UserWordDatabaseConfigJson cfg;
    CHECK(dataUtil.SetUserWordDatabaseConfig(&cfg));

    std::string strWord = "apple";
    std::string strToken = "dennisthink";
    
    if(dataUtil.IsKnownWord(strWord, strToken))
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
    SqliteDatabaseConfig cfg;
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

TEST_CASE("UserWordSqlite") {
    CUserWordDatabaseSqlite dataUtil;

    UserWordDatabaseConfigSqlite cfg;
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

/*
TEST_CASE("DictMySql") {
    CHECK(1 == 1);
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
}*/
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

    printf("%s\n", "Hello, World!");
    return 0;
}