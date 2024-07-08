#include <iostream>
#include "CCppHttpLibServer.hpp"
int main(int argc, char* argv[])
{
	CCppHttpLibServer server;
	server.Start();
	std::cout << "cpp_http_main" << std::endl;
	return 0;
}