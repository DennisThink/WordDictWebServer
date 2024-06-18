#include "EnglishChineseWordDict.h"
#include "SQLiteCpp/SQLiteCpp.h"
#include <share.h>
#include <memory>
#include "word_dict_struct.hpp"
static std::shared_ptr<SQLite::Database> g_db = nullptr;
EnglishChineseWordDict::EnglishChineseWordDict()
{

}

bool EnglishChineseWordDict::InitDictFromFile(const std::string strFileName)
{
	return false;
}

std::string EnglishChineseWordDict::GetTranslation(const std::string strEnglish)
{
	/* {
        std::string strQueryEmailReceive = "SELECT SENDER_NAME,SENDER_EMAIL,RECEIVER_NAME,RECEIVER_EMAIL,SUBJECT,CONTENT FROM T_EMAIL_SEND WHERE RECEIVER_EMAIL == ?";
        SQLite::Statement query(*g_db, strQueryEmailReceive);
        query.bind(1, userName);
        while (query.executeStep())
        {
            email_info_t email;
            email.emailSender_.name_ = query.getColumn(0).getString();
            email.emailSender_.emailAddr_ = query.getColumn(1).getString();
            email.emailReceiver_.name_ = query.getColumn(2).getString();
            email.emailReceiver_.emailAddr_ = query.getColumn(3).getString();
            email.subject_ = query.getColumn(4).getString();
            email.context_ = query.getColumn(5).getString();
            emailArray.push_back(email);
        }
        return true;
	}*/
	if (strEnglish == "apple")
	{
		return "Æ»¹û";
	}
	else
	{
		return "Ïã½¶";
	}
}

EnglishChineseWordDict::~EnglishChineseWordDict()
{

}
