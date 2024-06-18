#ifndef _WORD_DICT_STRUCT_H_
#define _WORD_DICT_STRUCT_H_
#include <string>
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
};
std::ostream& operator<<(std::ostream& os, DictLineElem_t p);
#endif