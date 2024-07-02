#include "CDictDatabaseJson.hpp"
#include <algorithm>
#include "json11/json11.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
CDictDatabaseJson::CDictDatabaseJson()
{
}
T_ENGLISH_CHINSE_TRANS CDictDatabaseJson::GetTranslation(const std::string strWord)
{
	T_ENGLISH_CHINSE_TRANS result;
	result.F_ENGLISH = strWord;
	std::string strOld = ToLower(strWord);
	std::size_t index = strOld[0] - 'a';
	if ( (0 <= index) && 
		 (index < 26) )
	{
		auto iter = m_mapWords[index].find(strWord);
		if (iter != m_mapWords[index].end()) {
			result.F_CHINESE = strWord;
			result.F_CHINESE = iter->second;
			result.F_LEVEL = 0;
		}
	}
	return result;
}
bool CDictDatabaseJson::InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
	return false;
}

bool CDictDatabaseJson::IsWordInDict(const std::string strWord)
{
	std::string strOld = ToLower(strWord);
	std::size_t index = strOld[0] - 'a';
	if ((0 <= index) &&
		(index < 26))
	{
		auto iter = m_mapWords[index].find(strWord);
		if (iter != m_mapWords[index].end()) {
			return true;
		}
	}
	return false;
}

std::string CDictDatabaseJson::ToLower(const std::string& strOld)
{
	std::string strIn = strOld;
	std::transform(strIn.begin(), strIn.end(), strIn.begin(),
		[](unsigned char c) { return std::tolower(c); });
	return strIn;
}

bool CDictDatabaseJson::UpdateWordFrequency(const std::string strWord)
{
	return false;
}

bool CDictDatabaseJson::SetDatabaseConfig(const DataBaseConfigInterface* cfg)
{
	if ((nullptr != cfg) && 
		(NULL != cfg))
	{
		m_cfg = *(JsonDatabaseConfig*)(cfg);
		InitDatabase(m_cfg.m_jsonFileName);
		return true;
	}
	return false;
}

std::vector<T_ENGLISH_CHINSE_TRANS> CDictDatabaseJson::GetAllWords()
{
	std::vector<T_ENGLISH_CHINSE_TRANS> retResult;
	for (auto mapItem : m_mapWords)
	{
		for (auto wordItem : mapItem) {
			T_ENGLISH_CHINSE_TRANS elem;
			elem.F_ENGLISH = wordItem.first;
			elem.F_CHINESE = wordItem.second;
			elem.F_LEVEL = m_cfg.m_nLevel;
			retResult.push_back(elem);
		}
	}
	return retResult;
}

bool CDictDatabaseJson::InsertKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CDictDatabaseJson::DeleteKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}


bool CDictDatabaseJson::IsKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CDictDatabaseJson::InsertUnKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CDictDatabaseJson::DeleteUnKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CDictDatabaseJson::IsUnKnownWord(const std::string strWord, const std::string strToken)
{
	return false;
}

void CDictDatabaseJson::InitDatabase(const std::string strJsonFile)
{
	std::ifstream file(strJsonFile);
	if (file.is_open()) {
		std::stringstream buff;
		buff << file.rdbuf();
		std::string data(buff.str());
		//std::cout << "data:" << data << std::endl;

		std::string strErr;
		json11::Json dictJson = json11::Json::parse(data.c_str(), strErr);
		if (strErr.empty()) {
			if (dictJson.is_array()) {
				auto jsonArray = dictJson.array_items();
				std::string strEnglish;
				std::string strChinese;
				for (auto item : jsonArray) {
					strEnglish.clear();
					strChinese.clear();
					if (item["word"].is_string())
					{
						//std::cout << "English: " << item["word"].string_value() << "  ";
						strEnglish = item["word"].string_value();
					}
					if (item["translations"].is_array()) {
						auto trans = item["translations"].array_items();
						//std::cout << "Chinese: ";
						for (auto it : trans) {
							if (it["translation"].is_string()) {
								strChinese +=" ";
								strChinese += it["translation"].string_value();
								//std::cout << it["translation"].string_value() << " ";
							}
						}
						//std::cout << std::endl;
					}
					{
						std::string strLow = ToLower(strEnglish);
						std::size_t index = strLow[0] - 'a';
						if ( (0 <= index) && 
							 (index < 26)  ) {
							m_mapWords[index].insert({ strEnglish,strChinese });
						}
					}
				}
			}
		}
	}
	else {
	}
}