#ifndef _WORD_DICT_STRUCT_H_
#define _WORD_DICT_STRUCT_H_
#include <string>
#include <vector>
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
};
std::ostream& operator<<(std::ostream& os, DictLineElem_t p);


struct DataBaseConfigInterface {

};

struct SqliteDatabaseConfig :public DataBaseConfigInterface {

};


struct T_ENGLISH_CHINSE_TRANS
{
    std::string F_ID;
    std::string F_ENGLISH;
    std::string F_CHINESE;
    int         F_LEVEL;
};

struct T_WORD_REQUENCY {
    std::string F_ENGLISH;
    std::string F_TOKEN;
    int         F_TIMES;
};


#endif