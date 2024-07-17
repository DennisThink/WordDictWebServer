#include <ostream>
#include <fstream>
#include <sstream>
#include <memory>
#include "word_dict_struct.hpp"
#include "json11.hpp"
std::ostream& operator<<(std::ostream& os, DictLineElem_t p)
{
    os << "1. " << p.m_strWord <<
        "2. " << p.m_strPhonetic <<
        "3. " << p.m_strDefinition <<
        "4. " << p.m_strTranslation <<
        "5. " << p.m_strPos <<
        "6. " << p.m_strCollins <<
        "7. " << p.m_strOxford <<
        "8. " << p.m_strTag <<
        "9. " << p.m_strBnc <<
        "10. " << p.m_strFrq <<
        "11. " << p.m_strExchange <<
        "12. " << p.m_strDetail <<
        "13. " << p.m_strAudio << std::endl;
    return os;
}

DictLineElem_t::DictLineElem_t()
{
    m_strWord.clear();
    m_strPhonetic.clear();
    m_strDefinition.clear();
    m_strTranslation.clear();
    m_strPos.clear();
    m_strCollins.clear();
    m_strOxford.clear();
    m_strTag.clear();
    m_strBnc.clear();
    m_strFrq.clear();
    m_strExchange.clear();
    m_strDetail.clear();
    m_strAudio.clear();
}

std::string DictLineElem_t::GetTrans() {
    std::string result =  " EN: " + this->m_strWord + " CN: " + this->m_strTranslation;
    return result;
}

std::ostream& operator<<(std::ostream& os,const T_ENGLISH_CHINSE_TRANS& p)
{
    os << "EN: " << p.F_ENGLISH <<
        "  CN: " << p.F_CHINESE <<
        " LEVEL: " << p.F_LEVEL << std::endl;
    return os;
}


// EnglishToChineseReq_t begin
std::string EnglishToChineseReq_t::ToString()
{
    json11::Json dataJson = json11::Json::object{
      {"english",this->m_strEnglish},
      {"token",this->m_strToken}
    };
    std::string strReq = dataJson.dump();
    return strReq;
}

bool EnglishToChineseReq_t::FromString(const std::string& strReq)
{
    std::string strErr;
    auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
    if (strErr.empty())
    {
        this->m_strToken = resultJson["token"].string_value();
        this->m_strEnglish = resultJson["english"].string_value();
        return true;
    }
    return false;
}

//EnglishToChineseReq_t end

//EnglishToChineseRsp_t begin
std::string EnglishToChineseRsp_t::ToString()
{
    json11::Json dataJson = json11::Json::object{
       {"english",this->m_data.m_strEnglish},
       {"chinese",this->m_data.m_strChinese}
    };
    json11::Json rspJson = json11::Json::object{
        {"code",this->m_code},
        {"message",this->m_strMsg},
        {"data",dataJson}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}

bool EnglishToChineseRsp_t::FromString(const std::string& strReq)
{
    std::string strErr;
    auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
    if (strErr.empty())
    {
        this->m_code = resultJson["code"].int_value();
        this->m_strMsg = resultJson["message"].string_value();
        auto dataJson = resultJson["data"];
        if (!dataJson.is_null())
        {
            this->m_data.m_strChinese = dataJson["chinese"].string_value();
            this->m_data.m_strEnglish = dataJson["english"].string_value();
            return true;
        }
    }
    return false;
}

//EnglishToChineseRsp_t end

//SentenceToWordsRsp_t begin
std::string SentenceToWordsRsp_t::ToString()
{
    json11::Json::array dataArray;
    for (auto item : this->m_data) {
        json11::Json dataJson = json11::Json::object{
            {"english",item.m_strEnglish},
            {"chinese",item.m_strChinese}
        };
        dataArray.push_back(dataJson);
    }
    json11::Json rspJson = json11::Json::object{
       {"code",this->m_code},
       {"message",this->m_strMsg},
       {"data",dataArray}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}

bool SentenceToWordsRsp_t::FromString(const std::string& strReq)
{
    {
        std::string strErr;
        auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
        if (strErr.empty())
        {
            this->m_code = resultJson["code"].int_value();
            this->m_strMsg = resultJson["word"].string_value();
            auto dataArray = resultJson["data"];
            for (auto& item : dataArray.array_items())
            {
                EnglishToChineseData_t elem;
                elem.m_strChinese = item["chinese"].string_value();
                elem.m_strEnglish = item["english"].string_value();
                this->m_data.push_back(elem);
            }
            return true;
        }
    }
    return false;
}
//SentenceToWordsRsp_t end

//AddWordToKnowReq_t begin
bool AddWordToKnowReq_t::FromString(const std::string& strReq)
{
    {
        std::string strErr;
        auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
        if (strErr.empty())
        {
            this->m_strToken = resultJson["token"].string_value();
            this->m_strWord = resultJson["word"].string_value();
            return true;
        }
    }
    return false;
}

std::string AddWordToKnowReq_t::ToString()
{
    json11::Json rspJson = json11::Json::object{
     {"token",this->m_strToken},
     {"english",this->m_strWord}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}
//AddWordToKnowReq_t end

//AddWordToKnownRsp_t begin
bool AddWordToKnownRsp_t::FromString(const std::string& strReq)
{
    std::string strErr;
    auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
    if (strErr.empty())
    {
        this->m_code = resultJson["code"].int_value();
        this->m_strMsg = resultJson["message"].string_value();
        return true;
    }

    return false;
}

std::string AddWordToKnownRsp_t::ToString()
{
    json11::Json rspJson = json11::Json::object{
      {"code",this->m_code},
      {"message",this->m_strMsg}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}
//AddWordToKnownRsp_t end


//SetUserLanguageLevelReq_t begin
std::string SetUserLanguageLevelReq_t::ToString()
{
    json11::Json rspJson = json11::Json::object{
      {"token",this->m_strToken},
      {"level",this->m_nLevel}
    };
    std::string strRsp = rspJson.dump();
    return strRsp;
}

bool SetUserLanguageLevelReq_t::FromString(const std::string& strReq)
{
    std::string strErr;
    auto resultJson = json11::Json::parse(strReq.c_str(), strErr);
    if (strErr.empty())
    {
        this->m_strToken = resultJson["token"].string_value();
        this->m_nLevel = resultJson["level"].int_value();
        return true;
    }
    return false;
}
//SetUserLanguageLevelReq_t end





DictWebServerConfig::DictWebServerConfig()
{
    m_strServerIp.clear();
    m_nServerPort=-1;
    m_eDataBaseType = DataBaseType::NONE;
    m_dictCfg = nullptr;
    m_userWordCfg = nullptr;
}

DictWebServerConfig::~DictWebServerConfig()
{

}
DictWebServerConfig FromJsonContent(const std::string& jsonContent)
{
    DictWebServerConfig result;
    std::string strErr;
    auto resultJson = json11::Json::parse(jsonContent.c_str(), strErr);
    if (strErr.empty())
    {
        if (resultJson["ServerIp"].is_string())
        {
            result.m_strServerIp = resultJson["ServerIp"].string_value();
        }
        if (resultJson["ServerPort"].is_number())
        {
            result.m_nServerPort = resultJson["ServerPort"].int_value();
        }

        if (resultJson["DataBaseType"].is_string()) {
            std::string strType = resultJson["DataBaseType"].string_value();
           
            if (strType == "JSON")
            {
                result.m_eDataBaseType = DataBaseType::JSON;
            }
            if (strType == "MYSQL")
            {
                result.m_eDataBaseType = DataBaseType::MY_SQL;
            }
            if (strType == "SQLITE")
            {
                result.m_eDataBaseType = DataBaseType::SQLITE;
            }
        }
        {
            if (result.m_eDataBaseType == DataBaseType::JSON)
            {
                auto databaseJson = resultJson["DictDataBase"];
                auto pDict = std::make_shared<DictDataBaseCfgJson>();
                if (databaseJson.is_array())
                {
                    auto jsonItemArray = databaseJson.array_items();
                    for (auto& jsonItem : jsonItemArray)
                    {
                        DictJsonFileElem elem;
                        if (jsonItem["FileName"].is_string())
                        {
                            elem.m_jsonFileName = jsonItem["FileName"].string_value();
                        }
                        if (jsonItem["Level"].is_number())
                        {
                            elem.m_nLevel = jsonItem["Level"].int_value();
                        }
                        pDict->m_jsonFiles.push_back(elem);
                    }
                }
                result.m_dictCfg = pDict;
            }

            if (result.m_eDataBaseType == DataBaseType::MY_SQL)
            {
                auto databaseJson = resultJson["DictDataBase"];
                auto pDict = std::make_shared <DictDataBaseCfgMysql>();
                if (databaseJson["DataBaseIp"].is_string())
                {
                    pDict->m_strMysqlServerIp = databaseJson["DataBaseIp"].string_value();
                }
                if (databaseJson["DataBasePort"].is_number())
                {
                    pDict->m_nMysqlServerPort = databaseJson["DataBasePort"].int_value();
                }

                if (databaseJson["UserName"].is_string())
                {
                    pDict->m_strMysqlUserName = databaseJson["UserName"].string_value();
                }

                if (databaseJson["PassWord"].is_string())
                {
                    pDict->m_strMysqlPassoword = databaseJson["PassWord"].string_value();
                }

                if (databaseJson["DataBase"].is_string())
                {
                    pDict->m_strDataBase = databaseJson["DataBase"].string_value();
                }
                result.m_dictCfg = pDict;
            }
            if (result.m_eDataBaseType == DataBaseType::SQLITE)
            {
                auto databaseJson = resultJson["DictDataBase"];
                auto pDict = std::make_shared<DictDataBaseCfgSqlite>();
                if (databaseJson["FileName"].is_string())
                {
                    pDict->m_sqliteFileName = databaseJson["FileName"].string_value();
                }
                result.m_dictCfg = pDict;
            }
        }
        {
            if (result.m_eDataBaseType == DataBaseType::SQLITE)
            {
                auto databaseJson = resultJson["UserWordDataBase"];
                auto pDict = std::make_shared <UserWordDataBaseCfgSqlite>();
                if (databaseJson["FileName"].is_string())
                {
                    pDict->m_strUserWordFileName= databaseJson["FileName"].string_value();
                }
                result.m_userWordCfg = pDict;
            }

            if (result.m_eDataBaseType == DataBaseType::MY_SQL)
            {
                auto databaseJson = resultJson["UserWordDataBase"];
                auto pDict = std::make_shared<UserWordDataBaseCfgMysql>();
                if (databaseJson["DataBaseIp"].is_string())
                {
                    pDict->m_strMysqlServerIp = databaseJson["DataBaseIp"].string_value();
                }
                if (databaseJson["DataBasePort"].is_number())
                {
                    pDict->m_nMysqlServerPort = databaseJson["DataBasePort"].int_value();
                }

                if (databaseJson["UserName"].is_string())
                {
                    pDict->m_strMysqlUserName = databaseJson["UserName"].string_value();
                }

                if (databaseJson["PassWord"].is_string())
                {
                    pDict->m_strMysqlPassoword = databaseJson["PassWord"].string_value();
                }

                if (databaseJson["DataBase"].is_string())
                {
                    pDict->m_strDataBase = databaseJson["DataBase"].string_value();
                }
                result.m_userWordCfg = pDict;
            }

            if (result.m_eDataBaseType == DataBaseType::JSON)
            {
                auto databaseJson = resultJson["UserWordDataBase"];
                auto pDict = std::make_shared<UserWordDataBaseCfgJson>();
                if (databaseJson["KnownWordFileName"].is_string())
                {
                    pDict->m_strKnownWordsFileName = databaseJson["KnownWordFileName"].string_value();
                }
                if (databaseJson["UnKnownWordFileName"].is_string())
                {
                    pDict->m_strUnKnownWordsFileName = databaseJson["UnKnownWordFileName"].int_value();
                }
                result.m_userWordCfg = pDict;
            }
        }
    }
    return result;
}

DictWebServerConfig FromJsonFile(const std::string strJsonFile)
{
    DictWebServerConfig result;
    {
        DataBaseType databaseType = DataBaseType::NONE;
        {
            std::ifstream file(strJsonFile);
            if (file.is_open()) {
                std::stringstream buff;
                buff << file.rdbuf();
                std::string data(buff.str());
                return FromJsonContent(data);
            }
               
        }
    }
    return result;
}