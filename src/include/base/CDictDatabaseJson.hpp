#ifndef _C_DICT_DATA_BASE_JSON_H_
#define _C_DICT_DATA_BASE_JSON_H_
#include "CDictDatabaseInterface.hpp"
#include <map>
#include <vector>
class CDictDatabaseJson :public CDictDatabaseInterface
{
public:
	CDictDatabaseJson(const std::string strFileName);
	virtual ~CDictDatabaseJson() {};
	virtual DictLineElem_t GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const DictLineElem_t& elem);
protected:
	void InitDatabase();
	std::string ToLower(const std::string& strOld);
	std::map<std::string, std::string> m_mapWords[26];
};
#endif
