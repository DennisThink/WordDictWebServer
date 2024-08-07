#ifndef _C_DICT_DATA_BASE_JSON_H_
#define _C_DICT_DATA_BASE_JSON_H_
#include "CDictDatabaseInterface.hpp"
#include <map>
#include <vector>
struct WordTokenElem
{
	std::string m_strWord;
	std::string m_strToken;
};

struct WordFrequencyElem
{
	std::string m_strWord;
	std::string m_strToken;
	int m_nTimes;
};

struct UserLanguageLevelElem
{
	std::string strToken;
	int m_nLevel;
};

struct WordTransAndLevelElem
{
	std::string m_strChinese;
	int m_nLevel;
};

class CDictDatabaseJson :public CDictDatabaseInterface
{
public:
	CDictDatabaseJson();
	virtual ~CDictDatabaseJson() {};
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord) override;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
	virtual bool DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem) override;
	virtual bool IsWordInDict(const std::string strWord) override;
	virtual bool SetDictDatabaseConfig(const DictDataBaseCfg* cfg) override;
	std::vector<T_ENGLISH_CHINSE_TRANS> GetAllWords();
protected:
	void InitDatabase(const std::string jsonFile,const int nLevel);
	std::string ToLower(const std::string& strOld);
	std::map<std::string,WordTransAndLevelElem> m_mapWords[26];

	DictDataBaseCfgJson m_cfg;
};

class CUserWordDatabaseJson :public CUserWordDatabaseInterface
{
public:
	CUserWordDatabaseJson();
	virtual ~CUserWordDatabaseJson();
	virtual bool SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg) override;
	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken) override;

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken) override;
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken) override;

	virtual bool UpdateWordFrequency(const std::string strWord, const std::string strToken) override;
	virtual bool InsertWordFrequency(const std::string strWord, const std::string strToken) override;
	virtual bool IsWordFrequencyExist(const std::string strWord, const std::string strToken) override;

	virtual bool InsertUserLanguageLevel(const std::string strToken, const int nLevel) override;
	virtual bool UpdateUserLanguageLevel(const std::string strToken, const int nLevel) override;
	virtual bool GetUserLanguageLevel(const std::string strToken, int& nLevel) override;
private:
	void InitArrayFromFile();
	void SaveArrayToFile();
	std::vector<WordTokenElem> m_knownWords;
	std::vector<WordTokenElem> m_unKnownWords;
	std::vector<WordFrequencyElem> m_userWordFrequency;
	std::vector<UserLanguageLevelElem> m_userLanguageLevels;
private:
	UserWordDataBaseCfgJson m_config;
};
#endif
