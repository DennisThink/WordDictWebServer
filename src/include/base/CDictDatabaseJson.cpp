#include "CDictDatabaseJson.hpp"
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
	for (auto item : m_allWords) {
		if (item.m_strWord == strWord) {
			return item;
		}
	}
	return result;
}
bool CDictDatabaseJson::InsertWordElem(const DictLineElem_t& elem)
{
	return false;
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

					DictLineElem_t elem;
					elem.m_strWord = strEnglish;
					elem.m_strTranslation = strChinese;
					m_allWords.push_back(elem);
				}
			}
		}
	}
	else {
		std::cout << "Read File failed  File: " << m_strDbFileName <<std::endl;
	}
}