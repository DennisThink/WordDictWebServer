#ifndef _C_HTTP_SERVER_INTERFACE_H_
#define _C_HTTP_SERVER_INTERFACE_H_
#include "CDictDatabaseInterface.hpp"
class CHttpServerInterface
{
public:
	CHttpServerInterface() {};
	virtual ~CHttpServerInterface() {};
	void SetDictAndUserWord(const CDictDataBase_PTR pDict, const CUserWordDataBase_PTR pWord) {
	}
	virtual void Start() = 0;
protected:
	CDictDataBase_PTR m_dict;
	CUserWordDataBase_PTR m_userWord;
};
#endif