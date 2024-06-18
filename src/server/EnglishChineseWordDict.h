#ifndef _ENGLISH_CHINESE_WORD_DICT_H_
#define _ENGLISH_CHINESE_WORD_DICT_H_
#include <string>
class EnglishChineseWordDict
{
public:
	EnglishChineseWordDict();
	virtual ~EnglishChineseWordDict();
	bool InitDictFromFile(const std::string strFileName);
	std::string GetTranslation(const std::string strEnglish);
private:

};
#endif