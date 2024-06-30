#ifndef _C_DICT_DATA_BASE_JSON_H_
#define _C_DICT_DATA_BASE_JSON_H_
#include "CDictDatabaseInterface.hpp"
#include <map>
#include <vector>
class CDictDatabaseJson :public CDictDatabaseInterface
{
public:
	CDictDatabaseJson();
	virtual ~CDictDatabaseJson() {};
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem);
	virtual bool IsWordInDict(const std::string strWord);
	virtual bool UpdateWordFrequency(const std::string strWord);
	virtual bool SetDatabaseConfig(const DataBaseConfigInterface* cfg);
	std::vector<T_ENGLISH_CHINSE_TRANS> GetAllWords();
protected:
	void InitDatabase(const std::string jsonFile);
	std::string ToLower(const std::string& strOld);
	std::map<std::string, std::string> m_mapWords[26];
};
#endif
