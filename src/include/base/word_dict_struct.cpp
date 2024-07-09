#include <ostream>
#include "word_dict_struct.hpp"
#include "json11.hpp"
std::ostream& operator<<(std::ostream& os, DictLineElem_t p)
{
    os << "1. " << p.m_strWord <<
        "2. " << p.m_strPhonetic <<
        "3. " << p.m_strDefinition <<
        "4. " << p.m_strTranslation <<
        "5. " << p.m_strPos <<
        "6. " << p.m_strCollins <<
        "7. " << p.m_strOxford <<
        "8. " << p.m_strTag <<
        "9. " << p.m_strBnc <<
        "10. " << p.m_strFrq <<
        "11. " << p.m_strExchange <<
        "12. " << p.m_strDetail <<
        "13. " << p.m_strAudio << std::endl;
    return os;
}

DictLineElem_t::DictLineElem_t()
{
    m_strWord.clear();
    m_strPhonetic.clear();
    m_strDefinition.clear();
    m_strTranslation.clear();
    m_strPos.clear();
    m_strCollins.clear();
    m_strOxford.clear();
    m_strTag.clear();
    m_strBnc.clear();
    m_strFrq.clear();
    m_strExchange.clear();
    m_strDetail.clear();
    m_strAudio.clear();
}

std::string DictLineElem_t::GetTrans() {
    std::string result =  " EN: " + this->m_strWord + " CN: " + this->m_strTranslation;
    return result;
}

std::ostream& operator<<(std::ostream& os,const T_ENGLISH_CHINSE_TRANS& p)
{
    os << "EN: " << p.F_ENGLISH <<
        "  CN: " << p.F_CHINESE <<
        " LEVEL: " << p.F_LEVEL << std::endl;
    return os;
}

std::string WordRspToString(const EnglishToChineseRsp_t& rsp)
{
    json11::Json dataJson = json11::Json::object{
        {"english",rsp.m_data.m_strEnglish},
        {"chinese",rsp.m_data.m_strChinese}
    };
    json11::Json rspJson = json11::Json::object{
        {"code",rsp.m_code},
        {"message",rsp.m_strMsg},
        {"data",dataJson}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}

std::string SentenceRspToString(const SentenceToWordsRsp_t& rsp)
{
    json11::Json::array dataArray;
    for (auto item : rsp.m_data) {
        json11::Json dataJson = json11::Json::object{
            {"english",item.m_strEnglish},
            {"chinese",item.m_strChinese}
        };
        dataArray.push_back(dataJson);
    }
    json11::Json rspJson = json11::Json::object{
       {"code",rsp.m_code},
       {"message",rsp.m_strMsg},
       {"data",dataArray}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}


AddWordToKnowReq_t AddRemoveWordReq(const std::string& strReq)
{
    AddWordToKnowReq_t result;
    {
        {
            std::string strErr;
            auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
            if (strErr.empty())
            {
                result.m_strToken = resultJson["token"].string_value();
                result.m_strWord = resultJson["word"].string_value();
                return result;
            }
        }
    }
    return result;
}

std::string AddRemoveRspToString(const AddWordToKnownRsp_t& rsp)
{

    json11::Json rspJson = json11::Json::object{
       {"code",rsp.m_code},
       {"message",rsp.m_strMsg}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}