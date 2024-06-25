#include "CDictDatabaseJson.hpp"
#include <algorithm>
#include "json11/json11.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
CDictDatabaseJson::CDictDatabaseJson(const std::string strFileName):CDictDatabaseInterface(strFileName)
{
	InitDatabase();
}
DictLineElem_t CDictDatabaseJson::GetTranslation(const std::string strWord)
{
	DictLineElem_t result;
	result.m_strWord = strWord;
	std::string strOld = ToLower(strWord);
	std::size_t index = strOld[0] - 'a';
	if ( (0 <= index) && 
		 (index < 26) )
	{
		auto iter = m_mapWords[index].find(strWord);
		if (iter != m_mapWords[index].end()) {
			result.m_strWord = strWord;
			result.m_strTranslation = iter->second;
		}
	}
	return result;
}
bool CDictDatabaseJson::InsertWordElem(const DictLineElem_t& elem)
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
void CDictDatabaseJson::InitDatabase()
{
	std::ifstream file(m_strDbFileName);
	if (file.is_open()) {
		std::stringstream buff;
		buff << file.rdbuf();
		std::string data(buff.str());
		std::cout << "data:" << data << std::endl;

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
						std::cout << "English: " << item["word"].string_value() << "  ";
						strEnglish = item["word"].string_value();
					}
					if (item["translations"].is_array()) {
						auto trans = item["translations"].array_items();
						std::cout << "Chinese: ";
						for (auto it : trans) {
							if (it["translation"].is_string()) {
								strChinese +=" ";
								strChinese += it["translation"].string_value();
								std::cout << it["translation"].string_value() << " ";
							}
						}
						std::cout << std::endl;
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
		std::cout << "Read File failed  File: " << m_strDbFileName <<std::endl;
	}
}