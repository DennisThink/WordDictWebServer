#ifndef _C_DICT_DATA_BASE_JSON_H_
#define _C_DICT_DATA_BASE_JSON_H_
#include "CDictDatabaseInterface.hpp"
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
	std::vector<DictLineElem_t> m_allWords;
};
#endif
