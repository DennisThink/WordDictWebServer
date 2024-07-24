#include "version_base.hpp"
#include "error_code.hpp"
#include <iostream>
int main(int argc, char* argv[])
{
	{
		E_Error_Code code = E_Error_Code::Success;
		std::cout << "Code: " << static_cast<int>(code) << " Msg: " << ErrorMsg(code) << std::endl;
	}
	{
		E_Error_Code code = E_Error_Code::Error_Req_Format;
		std::cout << "Code: " << static_cast<int>(code) << " Msg: " << ErrorMsg(code) << std::endl;
	}
	{
		{
			E_Error_Code code = E_Error_Code::Error_Token;
			std::cout << "Code: " << static_cast<int>(code) << " Msg: " << ErrorMsg(code) << std::endl;
		}
	}
	std::cout << GetSoftVersion() << std::endl;
	std::cout << GetCompileInfo() << std::endl;
	return 0;
}