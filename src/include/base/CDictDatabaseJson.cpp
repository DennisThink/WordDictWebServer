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
	{
		std::string strLow = ToLower(elem.F_ENGLISH);
		std::size_t index = strLow[0] - 'a';
		if ((0 <= index) &&
			(index < 26)) {
			m_mapWords[index].insert({ elem.F_ENGLISH,elem.F_CHINESE });
			return true;
		}
	}
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


bool CDictDatabaseJson::DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem)
{
	{
		std::string strLow = ToLower(elem.F_ENGLISH);
		std::size_t index = strLow[0] - 'a';
		if ((0 <= index) &&
			(index < 26)) {
			m_mapWords[index].erase(strLow);
			return true;
		}
	}
	return false;
}
bool CDictDatabaseJson::SetDictDatabaseConfig(const DictDataBaseCfg* cfg)
{
	if ((nullptr != cfg) && 
		(NULL != cfg))
	{
		m_cfg = *(DictDataBaseCfgJson*)(cfg);
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

CUserWordDatabaseJson::CUserWordDatabaseJson()
{

}

CUserWordDatabaseJson::~CUserWordDatabaseJson()
{

}


bool CUserWordDatabaseJson::SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg)
{
	if ((nullptr != cfg) &&
		(NULL != cfg))
	{
		m_config = *(UserWordDataBaseCfgJson*)(cfg);
	}
	return true;
}
bool CUserWordDatabaseJson::InsertKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item : m_knownWords)
	{
		if (item.m_strWord == strWord && item.m_strToken == strToken) 
		{
			bHasExist = true;
			break;
		}
	}

	if (!bHasExist)
	{
		WordTokenElem elem;
		elem.m_strWord = strWord;
		elem.m_strToken = strToken;
		m_knownWords.push_back(elem);
	}
	return true;
}

bool CUserWordDatabaseJson::DeleteKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item = m_knownWords.begin(); item != m_knownWords.end(); item++)
	{
		if (item->m_strWord == strWord && item->m_strToken == strToken)
		{
			m_knownWords.erase(item);
			break;
		}
	}
	return false;
}


bool CUserWordDatabaseJson::IsKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item : m_knownWords)
	{
		if (item.m_strWord == strWord && item.m_strToken == strToken)
		{
			bHasExist = true;
			break;
		}
	}
	return bHasExist;
}

bool CUserWordDatabaseJson::InsertUnKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item : m_unKnownWords)
	{
		if (item.m_strWord == strWord && item.m_strToken == strToken)
		{
			bHasExist = true;
			break;
		}
	}

	if (!bHasExist)
	{
		WordTokenElem elem;
		elem.m_strWord = strWord;
		elem.m_strToken = strToken;
		m_unKnownWords.push_back(elem);
	}
	return true;
}

bool CUserWordDatabaseJson::DeleteUnKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item = m_unKnownWords.begin(); item != m_unKnownWords.end(); item++)
	{
		if (item->m_strWord == strWord && item->m_strToken == strToken)
		{
			m_unKnownWords.erase(item);
			break;
		}
	}
	return true;
}

bool CUserWordDatabaseJson::UpdateWordFrequency(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CUserWordDatabaseJson::InsertWordFrequency(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CUserWordDatabaseJson::IsWordFrequencyExist(const std::string strWord, const std::string strToken)
{
	return false;
}

bool CUserWordDatabaseJson::InsertUserLanguageLevel(const std::string strToken, const int nLevel)
{
	return false;
}

bool CUserWordDatabaseJson::UpdateUserLanguageLevel(const std::string strToken, const int nLevel)
{
	return false;
}
bool CUserWordDatabaseJson::GetUserLanguageLevel(const std::string strToken, int& nLevel)
{
	return false;
}

bool CUserWordDatabaseJson::IsUnKnownWord(const std::string strWord, const std::string strToken)
{
	bool bHasExist = false;
	for (auto item : m_unKnownWords)
	{
		if (item.m_strWord == strWord && item.m_strToken == strToken)
		{
			bHasExist = true;
			break;
		}
	}

	return bHasExist;
}


void CUserWordDatabaseJson::InitArrayFromFile()
{

	{
		std::ifstream file(m_config.m_strKnownWordsFileName);
		if (file.is_open()) {
			std::stringstream buff;
			buff << file.rdbuf();
			std::string data(buff.str());
			std::string strErr;
			json11::Json dictJson = json11::Json::parse(data.c_str(), strErr);
			if (strErr.empty()) {
				if (dictJson.is_array()) {
					auto jsonArray = dictJson.array_items();
					for (auto item : jsonArray) {
						WordTokenElem elem;
						if (item["english"].is_string())
						{
							elem.m_strWord = item["english"].string_value();
						}
						if (item["token"].is_string()) 
						{
							elem.m_strToken = item["token"].string_value();
						}
						m_knownWords.push_back(elem);
					}
				}
			}
		}
		else {
		}
	}

	{
		std::ifstream file(m_config.m_strUnKnownWordsFileName);
		if (file.is_open()) {
			std::stringstream buff;
			buff << file.rdbuf();
			std::string data(buff.str());
			std::string strErr;
			json11::Json dictJson = json11::Json::parse(data.c_str(), strErr);
			if (strErr.empty()) {
				if (dictJson.is_array()) {
					auto jsonArray = dictJson.array_items();
					for (auto item : jsonArray) {
						WordTokenElem elem;
						if (item["english"].is_string())
						{
							elem.m_strWord = item["english"].string_value();
						}
						if (item["token"].is_string())
						{
							elem.m_strToken = item["token"].string_value();
						}
						m_unKnownWords.push_back(elem);
					}
				}
			}
		}
		else {
		}
	}
}

void CUserWordDatabaseJson::SaveArrayToFile()
{
	{

		json11::Json::array knownArray;
		for (auto& item : m_knownWords) {
			auto elemJson = json11::Json::object{
				{"english",item.m_strWord},
				{"token",item.m_strToken}
			};
			knownArray.push_back(elemJson);
		}
		std::string strDump = json11::Json(knownArray).dump();
		std::cout << "KnownWords: " << strDump << std::endl;
	}

	{
		{

			json11::Json::array knownArray;
			for (auto& item : m_unKnownWords) {
				auto elemJson = json11::Json::object{
					{"english",item.m_strWord},
					{"token",item.m_strToken}
				};
				knownArray.push_back(elemJson);
			}
			std::string strDump = json11::Json(knownArray).dump();
			std::cout << "UnKnownWords: " << strDump << std::endl;
		}
	}
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