#include <ostream>
#include "word_dict_struct.hpp"
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
