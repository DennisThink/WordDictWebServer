#ifndef _C_DICT_DATA_BASE_INTERFACE_H_
#define _C_DICT_DATA_BASE_INTERFACE_H_
#include "word_dict_struct.hpp"
#include <memory>
class CDictDatabaseInterface
{
public:
	CDictDatabaseInterface() {};
	virtual ~CDictDatabaseInterface() {};
	virtual bool SetDictDatabaseConfig(const DictDataBaseCfg* cfg)=0;
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord)=0;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)=0;
	virtual bool DeleteWordElem(const T_ENGLISH_CHINSE_TRANS& elem) = 0;
	virtual bool IsWordInDict(const std::string strWord) = 0;
};

class CUserWordDatabaseInterface
{
public:
	CUserWordDatabaseInterface() {};
	virtual ~CUserWordDatabaseInterface() {};
	virtual bool SetUserWordDatabaseConfig(const UserWordDataBaseCfg* cfg) = 0;

	virtual bool InsertKnownWord(const std::string strWord, const std::string strToken) = 0;
	virtual bool DeleteKnownWord(const std::string strWord, const std::string strToken) = 0;
	virtual bool IsKnownWord(const std::string strWord, const std::string strToken) = 0;

	virtual bool InsertUnKnownWord(const std::string strWord, const std::string strToken) = 0;
	virtual bool DeleteUnKnownWord(const std::string strWord, const std::string strToken) = 0;
	virtual bool IsUnKnownWord(const std::string strWord, const std::string strToken) = 0;

	virtual bool UpdateWordFrequency(const std::string strWord, const std::string strToken) = 0;
	virtual bool InsertWordFrequency(const std::string strWord, const std::string strToken) = 0;
	virtual bool IsWordFrequencyExist(const std::string strWord, const std::string strToken) = 0;

	virtual bool InsertUserLanguageLevel(const std::string strToken, const int nLevel) = 0;
	virtual bool UpdateUserLanguageLevel(const std::string strToken, const int nLevel) = 0;
	virtual bool GetUserLanguageLevel(const std::string strToken, int& nLevel) = 0;
};

using CDictDataBase_PTR = std::shared_ptr<CDictDatabaseInterface>;
using CUserWordDataBase_PTR = std::shared_ptr<CUserWordDatabaseInterface>;
#endif