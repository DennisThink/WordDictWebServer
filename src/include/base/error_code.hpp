#ifndef _ERROR_CODE_H_
#define _ERROR_CODE_H_
#include <string>
enum class E_Error_Code:int {

	Error_Token=-2,
	Error_Req_Format=-1,
	Success=0,
};

std::string ErrorMsg(const E_Error_Code& code);
#endif