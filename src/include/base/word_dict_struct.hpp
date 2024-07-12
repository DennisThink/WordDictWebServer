#ifndef _WORD_DICT_STRUCT_H_
#define _WORD_DICT_STRUCT_H_
#include <string>
#include <vector>
#include <memory>
struct EnglishToChineseReq_t
{
    std::string m_strToken;
    std::string m_strEnglish;
};

struct EnglishToChineseData_t
{
    std::string m_strEnglish;
    std::string m_strChinese;
};

struct EnglishToChineseRsp_t
{
    int m_code;
    std::string m_strMsg;
    EnglishToChineseData_t m_data;
};


struct SentenceToWordsRsp_t 
{
    int m_code;
    std::string m_strMsg;
    std::vector<EnglishToChineseData_t> m_data;
};

struct AddWordToKnowReq_t
{
    std::string m_strWord;
    std::string m_strToken;
};

struct AddWordToKnownRsp_t
{
    int m_code;
    std::string m_strMsg;
};


typedef AddWordToKnowReq_t  AddWordToUnKnownReq_t;
typedef AddWordToKnownRsp_t AddWordToUnKnownRsp_t;
/*
* word,phonetic,definition,translation,pos,collins,oxford,tag,bnc,frq,exchange,detail,audio
*/
struct DictLineElem_t
{
    std::string m_strWord;
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
    DictLineElem_t();
    std::string GetTrans();
};
std::ostream& operator<<(std::ostream& os, DictLineElem_t p);


struct DictDataBaseCfg {
public:
    DictDataBaseCfg() {};
    virtual ~DictDataBaseCfg() {};
};

struct DictDataBaseCfgSqlite :public DictDataBaseCfg {
public:
    DictDataBaseCfgSqlite() {};
    virtual ~DictDataBaseCfgSqlite() {};
    std::string m_sqliteFileName;
};

struct DictDataBaseCfgJson : public DictDataBaseCfg {
public:
    DictDataBaseCfgJson(){};
    virtual ~DictDataBaseCfgJson() {};
    std::string m_jsonFileName;
    int m_nLevel;
};

struct DictDataBaseCfgMysql : public DictDataBaseCfg {
public:
    DictDataBaseCfgMysql() {};
    virtual ~DictDataBaseCfgMysql() {};
    std::string m_strMysqlServerIp;
    int m_nMysqlServerPort;
    std::string m_strMysqlUserName;
    std::string m_strMysqlPassoword;
    std::string m_strDataBase;
};

struct UserWordDataBaseCfg {

};

struct UserWordDataBaseCfgJson :public UserWordDataBaseCfg {
    std::string m_strKnownWordsFileName;
    std::string m_strUnKnownWordsFileName;
};

struct UserWordDataBaseCfgSqlite :public UserWordDataBaseCfg {
    std::string m_strUserWordFileName;
};

struct UserWordDataBaseCfgMysql :public UserWordDataBaseCfg {
    std::string m_strMysqlServerIp;
    int m_nMysqlServerPort;
    std::string m_strMysqlUserName;
    std::string m_strMysqlPassoword;
    std::string m_strDataBase;
};


struct T_ENGLISH_CHINSE_TRANS
{
    std::string F_ID;
    std::string F_ENGLISH;
    std::string F_CHINESE;
    int         F_LEVEL;
};
std::ostream& operator<<(std::ostream& os,const T_ENGLISH_CHINSE_TRANS& p);

struct T_WORD_REQUENCY {
    std::string F_ENGLISH;
    std::string F_TOKEN;
    int         F_TIMES;
};

std::string WordRspToString(const EnglishToChineseRsp_t& rsp);
std::string SentenceRspToString(const SentenceToWordsRsp_t& rsp);
AddWordToKnowReq_t AddRemoveWordReq(const std::string& strReq);
std::string AddRemoveRspToString(const AddWordToKnownRsp_t& rsp);

enum class DataBaseType
{
    NONE,
    JSON,
    MY_SQL,
    SQLITE,
};
class DictWebServerConfig
{
public:
    DictWebServerConfig();
    virtual ~DictWebServerConfig();
    std::string m_strServerIp;
    int         m_nServerPort;
    DataBaseType m_eDataBaseType;//JSON,MYSQL,SQLITE
    std::shared_ptr<DictDataBaseCfg> m_dictCfg;
    std::shared_ptr<UserWordDataBaseCfg> m_userWordCfg;
};

DictWebServerConfig FromJsonFile(const std::string strJsonFile);
DictWebServerConfig FromJsonContent(const std::string& jsonContent);
#endif