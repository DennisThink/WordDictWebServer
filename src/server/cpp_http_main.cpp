#include <iostream>
#include "CCppHttpLibServer.hpp"
#include "version_base.hpp"
int main(int argc, char* argv[])
{
	std::cout << GetSoftVersion() << "   " << GetCompileInfo() << std::endl;
	CCppHttpLibServer server;
	server.Start();
	std::cout << "cpp_http_main" << std::endl;
	return 0;
}