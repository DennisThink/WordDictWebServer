#include "CDictDatabaseJson.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
	if (argc > 0)
	{
		std::cout << argc << " " << argv[0] << "    " << argv[1] << std::endl;
		CDictDatabaseJson dictJson;
		std::string strArray[] = { "apple","orange","father" };
		for(auto item:strArray)
		{
			DictLineElem_t appleTrans = dictJson.GetTranslation(item);
			std::cout << item << "    " << appleTrans.m_strTranslation << std::endl;
		}
	}
	return 0;
}