#include "EnglishChineseWordDict.h"

EnglishChineseWordDict::EnglishChineseWordDict()
{

}

bool EnglishChineseWordDict::InitDictFromFile(const std::string strFileName)
{
	return false;
}

std::string EnglishChineseWordDict::GetTranslation(const std::string strEnglish)
{
	if (strEnglish == "apple")
	{
		return "ƻ��";
	}
	else
	{
		return "�㽶";
	}
}

EnglishChineseWordDict::~EnglishChineseWordDict()
{

}
