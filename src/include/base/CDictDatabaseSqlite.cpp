#include "CDictDatabaseSqlite.hpp"
#include <memory>
#include <iostream>
#include "SQLiteCpp/SQLiteCpp.h"
static std::shared_ptr<SQLite::Database> g_db = nullptr;
CDictDatabaseSqlite::CDictDatabaseSqlite()
{
    DatabaseInit();
}

CDictDatabaseSqlite::~CDictDatabaseSqlite()
{

}

T_ENGLISH_CHINSE_TRANS CDictDatabaseSqlite::GetTranslation(const std::string strWord)
{
    T_ENGLISH_CHINSE_TRANS result;
    std::string strSelectWordTrans = R"(SELECT 
            WORD,
            PHONETIC,
            DEFINITION,
            TRANSLATION,
            POS,
            COLLINS,
            OXFORD,
            TAG,
            BNC,
            FRQ,
            EXCHANGE,
            DETAIL,
            AUDIO) FROM T_ENGLISH_CHINESE WHERE WORD=?;)";
    try {
        SQLite::Statement query(*g_db, strSelectWordTrans);
        query.bind(1, strWord);
        std::vector<DictLineElem_t> wordsArray;
        while (query.executeStep())
        {
            DictLineElem_t elem;
            elem.m_strWord = query.getColumn(0).getString();
            elem.m_strPhonetic = query.getColumn(1).getString();
            elem.m_strDefinition = query.getColumn(2).getString();
            elem.m_strTranslation = query.getColumn(3).getString();
            elem.m_strPos = query.getColumn(4).getString();
            elem.m_strCollins = query.getColumn(5).getString();
            elem.m_strOxford = query.getColumn(6).getString();
            elem.m_strTag = query.getColumn(7).getString();
            elem.m_strBnc = query.getColumn(8).getString();
            elem.m_strFrq = query.getColumn(9).getString();
            elem.m_strExchange = query.getColumn(10).getString();
            elem.m_strDetail = query.getColumn(11).getString();
            elem.m_strAudio = query.getColumn(12).getString();
            //email.emailSender_.name_ = query.getColumn(0).getString();
            wordsArray.push_back(elem);
        }
        if (!wordsArray.empty()) {
            //result = wordsArray[0];
        }
    }
    catch(std::exception & ec)
    {
        std::cout << "Exception:  " << ec.what() << std::endl;
    }
   
	return result;
}

bool CDictDatabaseSqlite::UpdateWordFrequency(const std::string strWord)
{
    return false;
}

bool CDictDatabaseSqlite::IsWordInDict(const std::string strWord)
{
    return false;
}

bool CDictDatabaseSqlite::InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
    bool bResult = false;
    /*try {

        std::string strInsertEmailSend = R"(INSERT INTO T_ENGLISH_CHINESE(
            WORD,
            PHONETIC,
            DEFINITION,
            TRANSLATION,
            POS,
            COLLINS,
            OXFORD,
            TAG,
            BNC,
            FRQ,
            EXCHANGE,
            DETAIL,
            AUDIO) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?);)";
        SQLite::Statement query(*g_db, strInsertEmailSend);
        query.bind(1, elem.m_strWord);
        query.bind(2, elem.m_strPhonetic);
        query.bind(3, elem.m_strDefinition);
        query.bind(4, elem.m_strTranslation);
        query.bind(5, elem.m_strPos);
        query.bind(6, elem.m_strCollins);
        query.bind(7, elem.m_strOxford);
        query.bind(8, elem.m_strTag);
        query.bind(9, elem.m_strBnc);
        query.bind(10, elem.m_strFrq);
        query.bind(11, elem.m_strExchange);
        query.bind(12, elem.m_strDetail);
        query.bind(13, elem.m_strAudio);
        query.exec();
        bResult = true;
    }
    catch (std::exception& ec)
    {
        std::cout << "Exception:  " << ec.what() << std::endl;
        bResult = false;
    }*/
	return bResult;
}

void CDictDatabaseSqlite::DatabaseInit()
{
    try
    {
        //g_db = std::make_shared<SQLite::Database>(m_strDbFileName, SQLite::OPEN_READWRITE);
    }
    catch (std::exception& ec)
    {
        std::cout << "Exception:  " << ec.what() << std::endl;
        if (!g_db)
        {
            try
            {
                /*
                *   std::string m_strWord;
                    std::string m_strPhonetic;
                    std::string m_strDefinition;
                    std::string m_strTranslation;
                    std::string m_strPos;
                    std::string m_strCollins;
                    std::string m_strOxford;
                    std::string m_strTag;
                    std::string m_strBnc;
                    std::string m_strFrq;
                    std::string m_strExchange;
                    std::string m_strDetail;
                    std::string m_strAudio;
                */
                //g_db = std::make_shared<SQLite::Database>(m_strDbFileName, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
                std::string strCreateUserTable(R"(CREATE TABLE T_ENGLISH_CHINESE(ID INTEGER PRIMARY KEY AUTOINCREMENT,
                    WORD TEXT,
                    PHONETIC TEXT,
                    DEFINITION TEXT,
                    TRANSLATION TEXT,
                    POS TEXT,
                    COLLINS TEXT,
                    OXFORD TEXT,
                    TAG TEXT,
                    BNC TEXT,
                    FRQ TEXT,
                    EXCHANGE TEXT,
                    DETAIL TEXT,
                    AUDIO TEXT);)");
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