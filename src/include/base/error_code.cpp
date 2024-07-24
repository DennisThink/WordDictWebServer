#include "error_code.hpp"
std::string ErrorMsg(const E_Error_Code& code)
{
	switch (code)
	{
		case E_Error_Code::Success:
		{
			return "Success";
		}break;
		case E_Error_Code::Error_Req_Format:
		{
			return "the request format is wrong";
		}break;
		case E_Error_Code::Error_Token:
		{
			return "The Token is wrong";
		}break;
		default:
		{
			return "Unknown Error";
		}break;
	}
	return "";
}