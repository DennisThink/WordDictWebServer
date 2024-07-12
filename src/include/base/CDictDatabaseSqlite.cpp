#include "CDictDatabaseSqlite.hpp"
#include <memory>
#include <iostream>

CDictDatabaseSqlite::CDictDatabaseSqlite()
{
}

CDictDatabaseSqlite::~CDictDatabaseSqlite()
{

}

bool CDictDatabaseSqlite::SetDictDatabaseConfig(const DictDataBaseCfg* cfg)
{
    if ((NULL != cfg) &&
        (nullptr != cfg)) {
        DictDataBaseCfgSqlite* pCfg = (DictDataBaseCfgSqlite*)(cfg);
        DatabaseInit(pCfg->m_sqliteFileName);
        return true;
    }
    return false;
}

CUserWordDatabaseSqlite::CUserWordDatabaseSqlite()
{
}

CUserWordDatabaseSqlite::~CUserWordDatabaseSqlite()
{

}

void CUserWordDatabaseSqlite::DatabaseInit(const std::string strFileName)
{
    m_dbSqlite = nullptr;
    try
    {
        m_dbSqlite = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE);
    }
    catch (std::exception& ec)
    {
        m_dbSqlite = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "Exception:  " << ec.what() << std::endl;
    }
}
bool CUserWordDatabaseSqlite::SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg)
{
    if ((NULL != cfg) &&
        (nullptr != cfg)) {
        UserWordDataBaseCfgSqlite* pCfg = (UserWordDataBaseCfgSqlite*)(cfg);
        m_config = *pCfg;
        DatabaseInit(m_config.m_strUserWordFileName);
        return true;
    }
    return false;
}
T_ENGLISH_CHINSE_TRANS CDictDatabaseSqlite::GetTranslation(const std::string strWord)
{
    T_ENGLISH_CHINSE_TRANS result;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH,F_CHINESE,F_LEVEL FROM T_ENGLISH_CHINESE WHERE F_ENGLISH=?;)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
        if (nullptr != m_dbSqlite) {
            try {
                SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
        std::string strSelectWordTrans = R"(INSERT INTO T_UNKNOWN_WORDS(F_ENGLISH,F_TOKEN)  VALUES('%s','%s');)";
        if (nullptr != m_dbSqlite) {
            try {
                char buff[512] = { 0 };
                sprintf(buff, strSelectWordTrans.c_str(), strWord.c_str(), strToken.c_str());
                std::cout << "SQL: " << buff << std::endl;
                SQLite::Statement query(*m_dbSqlite, buff);
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
    std::string strSelectWordTrans = R"(DELETE FROM T_UNKNOWN_WORDS WHERE F_ENGLISH='%s' AND F_TOKEN='%s';)";
    if (nullptr != m_dbSqlite) {
        try {
            char buff[512] = { 0 };
            sprintf(buff, strSelectWordTrans.c_str(), strWord.c_str(), strToken.c_str());
            std::cout << "SQL: " << buff << std::endl;
            SQLite::Statement query(*m_dbSqlite, buff);
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


bool CUserWordDatabaseSqlite::UpdateWordFrequency(const std::string strWord, const std::string strToken)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(UPDATE T_WORD_FREQUENCY SET F_TIMES=F_TIMES+1 WHERE F_ENGLISH='%s' AND F_TOKEN='%s';)";
    if (nullptr != m_dbSqlite) {
        try {
            char buff[512] = { 0 };
            sprintf(buff, strSelectWordTrans.c_str(), strWord.c_str(), strToken.c_str());
            std::cout << "SQL: " << buff << std::endl;
            SQLite::Statement query(*m_dbSqlite, buff);
            while (query.executeStep())
            {
                bExist = true;
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

bool CUserWordDatabaseSqlite::InsertWordFrequency(const std::string strWord, const std::string strToken)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(INSERT INTO T_WORD_FREQUENCY(F_ENGLISH,F_TOKEN,F_TIMES) VALUES(?,?,?);)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
            query.bind(1, strWord);
            query.bind(2, strToken);
            query.bind(3, 1);
            while (query.executeStep())
            {
                bExist = true;
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

bool CUserWordDatabaseSqlite::IsWordFrequencyExist(const std::string strWord, const std::string strToken)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(SELECT F_TIMES FROM T_WORD_FREQUENCY WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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

bool CUserWordDatabaseSqlite::InsertUserLanguageLevel(const std::string strToken, const int nLevel)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(INSERT INTO T_USER_LANGUAGE_LEVEL(F_TOKEN,F_LEVEL) VALUES(?,?);)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
            query.bind(1, strToken);
            query.bind(2, nLevel);
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

bool CUserWordDatabaseSqlite::UpdateUserLanguageLevel(const std::string strToken, const int nLevel)
{
    bool bExist = true;
    std::string strSelectWordTrans = R"(UPDATE T_USER_LANGUAGE_LEVEL SET F_LEVEL=%d WHERE F_TOKEN='%s';)";
    if (nullptr != m_dbSqlite) {
        try {
            char buff[512] = { 0 };
            sprintf(buff, strSelectWordTrans.c_str(), nLevel, strToken.c_str());
            std::cout << "SQL: " << buff << std::endl;
            SQLite::Statement query(*m_dbSqlite, buff);
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
    else {
        bExist = false;
    }
    return bExist;
}

bool CUserWordDatabaseSqlite::GetUserLanguageLevel(const std::string strToken, int& nLevel)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(SELECT F_LEVEL FROM T_USER_LANGUAGE_LEVEL WHERE F_TOKEN=?;)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
            query.bind(1, strToken);
            while (query.executeStep())
            { 
                nLevel = query.getColumn(0).getInt();
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

bool CUserWordDatabaseSqlite::IsUnKnownWord(const std::string strWord, const std::string strToken)
{
    bool bExist = false;
    std::string strSelectWordTrans = R"(SELECT F_ENGLISH FROM T_UNKNOWN_WORDS WHERE F_ENGLISH=? AND F_TOKEN=?;)";
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
    if (nullptr != m_dbSqlite) {
        try {
            SQLite::Statement query(*m_dbSqlite, strSelectWordTrans);
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
    if (nullptr != m_dbSqlite) {
        try {

            std::string strInsertEmailSend = R"(INSERT INTO T_ENGLISH_CHINESE(
            F_ENGLISH,F_CHINESE,F_LEVEL) VALUES(?,?,?);)";
            SQLite::Statement query(*m_dbSqlite, strInsertEmailSend);
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
    m_dbSqlite = nullptr;
    try
    {
        m_dbSqlite = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE);
    }
    catch (std::exception& ec)
    {
        m_dbSqlite = std::make_shared<SQLite::Database>(strFileName, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        std::cout << "Exception:  " << ec.what() << std::endl;
        if (!m_dbSqlite)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_ENGLISH_CHINESE(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_CHINESE TEXT,
                    F_LEVEL INTEGER);)");
                SQLite::Transaction tr(*m_dbSqlite);
                m_dbSqlite->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }

        //Table T_KNOWN_WORDS
        if (!m_dbSqlite)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_KNOWN_WORDS(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_TOKEN TEXT);)");
                SQLite::Transaction tr(*m_dbSqlite);
                m_dbSqlite->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }


        if (!m_dbSqlite)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_UNKNOWN_WORDS(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_TOKEN TEXT);)");
                SQLite::Transaction tr(*m_dbSqlite);
                m_dbSqlite->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }

        if (!m_dbSqlite)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_USER_LANGUAGE_LEVEL(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_TOKEN TEXT,
                    F_LEVEL INTEGER);)");
                SQLite::Transaction tr(*m_dbSqlite);
                m_dbSqlite->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }

        if (!m_dbSqlite)
        {
            try
            {
                std::string strCreateUserTable(R"(CREATE TABLE T_WORD_FREQUENCY(F_ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    F_ENGLISH TEXT,
                    F_TOKEN TEXT,
                    F_TIMES INTEGER);)");
                SQLite::Transaction tr(*m_dbSqlite);
                m_dbSqlite->exec(strCreateUserTable);
                tr.commit();
            }
            catch (std::exception& ec2)
            {
                std::cout << "Exception:  " << ec2.what() << std::endl;
            }
        }
    }
}