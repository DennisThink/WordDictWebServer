#ifndef _DICT_TOOL_H_
#define _DICT_TOOL_H_
#include "word_dict_struct.hpp"
#include <vector>
class CdictTool
{
public:
    std::vector<DictLineElem_t> GetAllWords(const std::string strFileName);
private:
    void ReadFileLineByLine(const std::string strFileName);
    DictLineElem_t SplitLine(const std::string strLine);
    std::vector<DictLineElem_t> m_allWords;
};
#endif