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
			auto appleTrans = dictJson.GetTranslation(item);
			std::cout << item << "    " << appleTrans.F_CHINESE << std::endl;
		}
	}
	return 0;
}