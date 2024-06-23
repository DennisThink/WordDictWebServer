#include "CDictDatabaseInterface.hpp"
class CDictDatabaseMysql:public CDictDatabaseInterface
{
public:
	CDictDatabaseMysql(const std::string strFileName);
	virtual ~CDictDatabaseMysql();
	virtual DictLineElem_t GetTranslation(const std::string strWord);
	virtual bool InsertWordElem(const DictLineElem_t& elem);
};