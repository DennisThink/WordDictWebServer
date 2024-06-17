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
#endif