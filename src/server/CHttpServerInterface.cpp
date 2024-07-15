#include "CHttpServerInterface.hpp"
#include "CDictDatabaseMySql.hpp"
#include "json11.hpp"
#include <iostream>
#include <algorithm>
CHttpServerInterface::CHttpServerInterface()
{
    m_dict = nullptr;
    m_userWord = nullptr;
}
void CHttpServerInterface::SetDictAndUserWord(const CDictDataBase_PTR pDict, const CUserWordDataBase_PTR pWord)
{
    m_dict = pDict;
    m_userWord = pWord;
}
void CHttpServerInterface::InitDataBaseFromCfg()
{
    if (m_cfg.m_eDataBaseType == DataBaseType::MY_SQL)
    {
        m_dict = std::make_shared<CDictDatabaseMysql>();
        m_dict->SetDictDatabaseConfig(m_cfg.m_dictCfg.get());
        m_userWord = std::make_shared<CUserWordDatabaseMysql>();
        m_userWord->SetUserWordDatabaseConfig(m_cfg.m_userWordCfg.get());
    }
}
void CHttpServerInterface::SetServerCfg(const DictWebServerConfig& cfg)
{
    m_cfg = cfg;
    InitDataBaseFromCfg();
}
std::string CHttpServerInterface::HandleEnglishToChinese(const std::string& strReq)
{
    EnglishToChineseReq_t reqData;
    if (reqData.FromString(strReq))
    {
        EnglishToChineseRsp_t rspData = CreateRspFromReq(reqData);
        std::string strRsp = rspData.ToString();
        return strRsp;
    }
    else
    {
        return "";
    }

}

std::string CHttpServerInterface::HandleEnglishToWordTranslate(const std::string& strReq)
{
    EnglishToChineseReq_t reqData;
    if(reqData.FromString(strReq)) //= GetReqFromRequest(strReq);
    {
        auto result = TranslateSentence(reqData);
        std::string strVersion = result.ToString();
        return strVersion;
    }
    else
    {
        return "";
    }
}

std::string CHttpServerInterface::HandleAddWordToKnow(const std::string& strReq)
{
    AddWordToKnowReq_t reqData;
    if(reqData.FromString(strReq))
    {
        auto result = AddWordToKnow(reqData);
        std::string strVersion = result.ToString();// AddRemoveRspToString();
        return strVersion;
    }
    else
    {
        return "";
    }
}

std::string CHttpServerInterface::HandleAddWordToUnKnow(const std::string& strReq)
{
    AddWordToKnowReq_t reqData;
    // = AddRemoveWordReq(strReq);
    if (reqData.FromString(strReq))
    {
        auto result = AddWordToUnKnown(reqData);
        std::string strVersion = result.ToString();// AddRemoveRspToString(result);
        return strVersion;
    }
    else
    {
        return "";
    }
}
std::string CHttpServerInterface::HandleSetUserLanguageLevel(const std::string& strReq)
{
    std::string strResult;
    SetUserLanguageLevelReq_t req;
    if (req.FromString(strReq))
    {
        //auto req = GetUserLanguageLevelReq(strReq);
        auto rsp = SetUserLanguageLevel(req);
        strResult = rsp.ToString();// AddRemoveRspToString(rsp);
        return strResult;
    }
    else
    {
        return "";
    }
}

AddWordToUnKnownRsp_t CHttpServerInterface::AddWordToUnKnown(const AddWordToUnKnownReq_t& req)
{
    AddWordToKnownRsp_t result;
    if (m_userWord && m_userWord->IsUnKnownWord(req.m_strWord, req.m_strToken))
    {
        result.m_code = -1;
        result.m_strMsg = "Already a unknown word";
    }
    else
    {
        if (m_userWord && m_userWord->IsKnownWord(req.m_strWord, req.m_strWord))
        {
            m_userWord->DeleteKnownWord(req.m_strWord, req.m_strToken);
        }
        if (m_userWord)
        {
            m_userWord->InsertUnKnownWord(req.m_strWord, req.m_strToken);
        }
        result.m_code = 0;
        result.m_strMsg = "success";
    }

    return result;
}

AddWordToKnownRsp_t  CHttpServerInterface::AddWordToKnow(const AddWordToKnowReq_t& req)
{
    AddWordToKnownRsp_t result;
    if (m_userWord && m_userWord->IsKnownWord(req.m_strWord, req.m_strToken))
    {
        result.m_code = -1;
        result.m_strMsg = "Already a known word";
    }
    else
    {
        if (m_userWord && m_userWord->IsUnKnownWord(req.m_strWord, req.m_strWord))
        {
            m_userWord->DeleteUnKnownWord(req.m_strWord, req.m_strToken);
        }
        if (m_userWord)
        {
            m_userWord->InsertKnownWord(req.m_strWord, req.m_strToken);
        }
        result.m_code = 0;
        result.m_strMsg = "success";
    }

    return result;
}

std::string CHttpServerInterface::WordTrim(const std::string strOrg)
{
    std::string strResult;
    for (auto iter = strOrg.begin(); iter != strOrg.end(); iter++) {
        if (('a' <= *iter) &&
            (*iter <= 'z')) {
            strResult += *iter;
        }
    }
    return strResult;
}

/*
* (1) 收到整个英语句子。
(2) 拆分为多个单词。
(3) 确定改单词是否需要翻译
(3.1) 需要翻译，则翻译为汉语
(3.2) 不需要翻译，跳过
(4) 返回所有的翻译结果

*/
SentenceToWordsRsp_t CHttpServerInterface::TranslateSentence(const EnglishToChineseReq_t& req)
{
    SentenceToWordsRsp_t result;
    std::vector<EnglishToChineseData_t> transResultArray;

    std::string strSentence = req.m_strEnglish;
    std::size_t startIndex = 0;
    std::size_t endIndex = 0;
    startIndex = endIndex;
    std::cout << "Sentence:  " << strSentence << std::endl;

    std::map<std::string, int> words;
    {

        while (endIndex != std::string::npos) {
            endIndex = strSentence.find_first_of(" ", startIndex);
            std::string word = strSentence.substr(startIndex, endIndex - startIndex);
            std::cout << "Word:  " << word << std::endl;
            words.insert({ word,1 });
            startIndex = endIndex + 1;
        }
    }

    bool bNeedTranslat = false;
    for (auto item : words) {
        bNeedTranslat = true;
        //Need Translate
        {
            if (nullptr != m_userWord)
            {
                if (m_userWord->IsKnownWord(item.first, req.m_strToken))
                {
                    bNeedTranslat = false;
                }
            }
        }
        //Translate
        {
            if (bNeedTranslat)
            {
                EnglishToChineseData_t elem;
                elem.m_strEnglish = item.first;
                std::string strLow = ToLower(elem.m_strEnglish);
                strLow = WordTrim(strLow);
                if (nullptr != m_dict)
                {
                    elem.m_strChinese = m_dict->GetTranslation(strLow).F_CHINESE;
                }
                std::cout << "Engish: " << item.first << "   Chinese: " << elem.m_strChinese << std::endl;
                transResultArray.push_back(elem);
            }
            else
            {
                std::cout << "CAN NOT TRANS EN: " << item.first << std::endl;
            }
        }
    }
    result.m_code = 0;
    result.m_strMsg = "success";
    result.m_data = transResultArray;
    return result;
}

std::string CHttpServerInterface::ToLower(const std::string strOrg)
{
    std::string strCopy = strOrg;
    std::transform(strCopy.begin(), strCopy.end(), strCopy.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return strCopy;
}


SetUserLanguageLevelRsp_t CHttpServerInterface::SetUserLanguageLevel(const SetUserLanguageLevelReq_t& req)
{
    SetUserLanguageLevelRsp_t result;
    return result;
}


EnglishToChineseRsp_t CHttpServerInterface::CreateRspFromReq(const EnglishToChineseReq_t& req)
{
    EnglishToChineseRsp_t result;
    std::string strChinese;
    if (nullptr != m_dict)
    {
        strChinese = m_dict->GetTranslation(req.m_strEnglish).F_CHINESE;
    }
    if (strChinese.empty())
    {
        result.m_code = 0;
        result.m_strMsg = "New words";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = "NEW_WORDS";
        std::cout << "FAILED  English: " << req.m_strEnglish << std::endl;
    }
    else
    {
        result.m_code = 0;
        result.m_strMsg = "success";
        result.m_data.m_strEnglish = req.m_strEnglish;
        result.m_data.m_strChinese = strChinese;
        std::cout << "SUCCEED  English: " << req.m_strEnglish << "  Chinese: " << strChinese << std::endl;
    }
    return result;
}