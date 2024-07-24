#include "version_base.hpp"
#include "error_code.hpp"
#define MAIN_VERSION "1"
#define SUB_VERSION "0"
#define BUG_FIX_VERSION "0"
std::string GetSoftVersion()
{
	std::string strResult = MAIN_VERSION;
	strResult +=".";
	strResult += SUB_VERSION;
	strResult += ".";
	strResult +=BUG_FIX_VERSION;
	return strResult;
}

std::string GetCompileInfo()
{
	std::string strResult = " TIME: ";
	strResult += __TIMESTAMP__;
#ifdef _WIN32
	strResult += " Compiler: ";
	strResult += " MSVC_LANG ";
	strResult += std::to_string(_MSVC_LANG);

	strResult += " MSC_VER: ";
	strResult += std::to_string(_MSC_VER);
#endif

	return strResult;
}