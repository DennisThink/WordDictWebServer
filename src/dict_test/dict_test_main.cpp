#include "CDictDatabaseJson.hpp"
#include "CDictDatabaseSqlite.hpp"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


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