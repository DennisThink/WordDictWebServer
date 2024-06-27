#ifndef _C_DICT_DATA_BASE_INTERFACE_H_
#define _C_DICT_DATA_BASE_INTERFACE_H_
#include "word_dict_struct.hpp"
class CDictDatabaseInterface
{
public:
	CDictDatabaseInterface() {};
	virtual bool SetDatabaseConfig(const DataBaseConfigInterface* cfg)=0;
	virtual ~CDictDatabaseInterface() {};
	virtual T_ENGLISH_CHINSE_TRANS GetTranslation(const std::string strWord)=0;
	virtual bool InsertWordElem(const T_ENGLISH_CHINSE_TRANS& elem)=0;
	virtual bool IsWordInDict(const std::string strWord) = 0;
	virtual bool UpdateWordFrequency(const std::string strWord)=0;
};
#endif