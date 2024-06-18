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