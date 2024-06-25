#ifndef _C_DICT_DATA_BASE_INTERFACE_H_
#define _C_DICT_DATA_BASE_INTERFACE_H_
#include "word_dict_struct.hpp"
class CDictDatabaseInterface
{
public:
	CDictDatabaseInterface(const std::string strFileName) { m_strDbFileName = strFileName; };
	virtual ~CDictDatabaseInterface() {};
	virtual DictLineElem_t GetTranslation(const std::string strWord)=0;
	virtual bool InsertWordElem(const DictLineElem_t& elem)=0;
	virtual bool IsWordInDict(const std::string strWord) = 0;
protected:
	std::string m_strDbFileName;
};
#endif