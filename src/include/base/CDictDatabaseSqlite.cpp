#include "CDictDatabaseSqlite.hpp"
#include <memory>
#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
static std::shared_ptr<SQLite::Database> g_db = nullptr;
CDictDatabaseSqlite::CDictDatabaseSqlite()
{
}

CDictDatabaseSqlite::~CDictDatabaseSqlite()
{

}

bool CDictDatabaseSqlite::SetDictDatabaseConfig(const DataBaseConfigInterface* cfg)
{
    if ((NULL != cfg) &&
        (nullptr != cfg)) {
        SqliteDatabaseConfig* pCfg = (SqliteDatabaseConfig*)(cfg);
        DatabaseInit(pCfg->m_sqliteFileName);
        return true;
    }
    return false;
}


T_ENGLISH_CHINSE_TRANS CDictDatabaseSqlite::GetTranslation(const std::string strWord)
{
    T_ENGLISH_CHINSE_TRANS result;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH,F_CHINESE,F_LEVEL FROM T_ENGLISH_CHINESE WHERE F_ENGLISH=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            while (query.executeStep())
            {
                result.F_ENGLISH = query.getColumn(0).getString();
                result.F_CHINESE = query.getColumn(1).getString();
                result.F_LEVEL = query.getColumn(2).getInt();
                break;
            }
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
	return result;
}

bool CUserWordDatabaseSqlite::InsertKnownWord(const std::string strWord, const std::string strToken)
{
    if (!IsKnownWord(strWord, strToken)) {
        std::string strSelectWordTrans = R"(INSERT INTO T_KNOWN_WORDS(F_ENGLISH,F_TOKEN)  VALUES(?,?);)";
        if (nullptr != g_db) {
            try {
                SQLite::Statement query(*g_db, strSelectWordTrans);
                query.bind(1, strWord);
                query.bind(2, strToken);
                while (query.executeStep())
                {
                    break;
                }
            }
            catch (std::exception& ec)
            {
                std::cout << "Exception:  " << ec.what() << std::endl;
            }
        }
    }
    return true;
}

bool CUserWordDatabaseSqlite::DeleteKnownWord(const std::string strWord, const std::string strToken)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(DELETE FROM T_KNOWN_WORDS WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            query.bind(2, strToken);
            while (query.executeStep())
            {
                
                break;
            }
        }
        catch (std::exception& ec)
        {
            bExist = false;
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
    return bExist;
}

bool CUserWordDatabaseSqlite::IsKnownWord(const std::string strWord, const std::string strToken)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH FROM T_KNOWN_WORDS WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            query.bind(2, strToken);
            while (query.executeStep())
            {
                bExist = true;
                break;
            }
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
    return bExist;
}

bool CUserWordDatabaseSqlite::InsertUnKnownWord(const std::string strWord, const std::string strToken)
{
    if (!IsUnKnownWord(strWord, strToken)) {
        std::string strSelectWordTrans = R"(INSERT INTO T_UNKNOWN_WORDS(F_ENGLISH,F_TOKEN)  VALUES(?,?);)";
        if (nullptr != g_db) {
            try {
                SQLite::Statement query(*g_db, strSelectWordTrans);
                query.bind(1, strWord);
                query.bind(2, strToken);
                while (query.executeStep())
                {
                    break;
                }
            }
            catch (std::exception& ec)
            {
                std::cout << "Exception:  " << ec.what() << std::endl;
            }
        }
    }
    return true;
}

bool CUserWordDatabaseSqlite::DeleteUnKnownWord(const std::string strWord, const std::string strToken)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(DELETE FROM T_UNKNOWN_WORDS WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            query.bind(2, strToken);
            while (query.executeStep())
            {
               
                break;
            }
        }
        catch (std::exception& ec)
        {
            bExist = false;
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
    return bExist;
}


bool CUserWordDatabaseSqlite::UpdateWordFrequency(const std::string strWord)
{
    return false;
}
bool CUserWordDatabaseSqlite::IsUnKnownWord(const std::string strWord, const std::string strToken)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH FROM T_UNKNOWN_WORDS WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            query.bind(2, strToken);
            while (query.executeStep())
            {
                bExist = true;
                break;
            }
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
    return bExist;
}

bool CDictDatabaseSqlite::IsWordInDict(const std::string strWord)
{
    bool bResult = false;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH FROM T_ENGLISH_CHINESE WHERE F_ENGLISH=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, strWord);
            while (query.executeStep())
            {
                bResult = true;
                break;
            }
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
        }
    }
    return bResult;
}
bool CDictDatabaseSqlite::DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(DELETE FROM T_ENGLISH_CHINESE WHERE F_ENGLISH=?;)";
    if (nullptr != g_db) {
        try {
            SQLite::Statement query(*g_db, strSelectWordTrans);
            query.bind(1, elem.F_ENGLISH);
            while (query.executeStep())
            {
                bExist = true;
                break;
            }
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
            bExist = false;
        }
    }
    return true;
}

bool CDictDatabaseSqlite::InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
    bool bResult = false;
    if (nullptr != g_db) {
        try {

            std::string strInsertEmailSend = R"(INSERT INTO T_ENGLISH_CHINESE(
            F_ENGLISH,F_CHINESE,F_LEVEL) VALUES(?,?,?);)";
            SQLite::Statement query(*g_db, strInsertEmailSend);
            query.bind(1, elem.F_ENGLISH);
            query.bind(2, elem.F_CHINESE);
            query.bind(3, elem.F_LEVEL);
            query.exec();
            bResult = true;
        }
        catch (std::exception& ec)
        {
            std::cout << "Exception:  " << ec.what() << std::endl;
            bResult = false;
        }
    }
	return bResult;
}

void CDictDatabaseSqlite::DatabaseInit(const std::string strFileName)
{
    g_db = nullptr;
    try
    {
        g_db = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE);
    }
    catch (std::exception& ec)
    {
        g_db = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        std::cout << "Exception:  " << ec.what() << std::endl;
        if (!g_db)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_ENGLISH_CHINESE(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_CHINESE TEXT,
                    F_LEVEL INTEGER);)");
                SQLite::Transaction tr(*g_db);
                g_db->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }

        //Table T_KNOWN_WORDS
        if (!g_db)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_KNOWN_WORDS(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_TOKEN TEXT);)");
                SQLite::Transaction tr(*g_db);
                g_db->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }


        if (!g_db)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_UNKNOWN_WORDS(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_TOKEN TEXT);)");
                SQLite::Transaction tr(*g_db);
                g_db->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }
    }
}