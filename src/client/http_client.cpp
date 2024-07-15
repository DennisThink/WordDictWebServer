#include <string>
#include <client_http.hpp>
#include <future>
#include <server_http.hpp>

// Added for the default_resource example
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>
#ifdef HAVE_OPENSSL
#include "crypto.hpp"
#endif

#include "word_dict_struct.hpp"
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using Response_SHARED_PTR = std::shared_ptr<HttpServer::Response>;
using Request_SHARED_PTR = std::shared_ptr<HttpServer::Request>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

class CWordTranslateClient
{
public:
    std::string GetVersion();
    std::string EnglishToChinese(std::string strEnglish);
    void SentenceToWords();
    void AddWordToKnown();
    void AddWordToUnKnown();
    void SetUserLanguageLevel();
    std::string GetRequestDefault();
    std::string PostRequestDefault();
};

std::string CWordTranslateClient::GetVersion()
{
    HttpClient client("localhost:8080");
    std::cout << "Example POST request to http://localhost:8080/json"
        << std::endl;
    auto rsp = client.request("GET", "/version");
    if (rsp)
    {
        std::cout << rsp->content.string() << std::endl;
    }
    //client.io_service->run();
    return "";
}

std::string CWordTranslateClient::EnglishToChinese(std::string strEnglish)
{

    HttpClient client("localhost:8080");
    std::cout << "Example POST request to http://localhost:8080/json"
        << std::endl;
    {
        EnglishToChineseReq_t req;
        req.m_strEnglish = "apple";
        req.m_strToken = "test@test.com";
        //std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"apple"})";
        auto rsp = client.request("POST", "/v1/english_to_chinese", req.ToString().c_str());
        if (rsp)
        {
            std::cout <<"RSP: "<< rsp->content.string() << std::endl;
            std::string s = rsp->content.string();
            EnglishToChineseRsp_t rsp;
            if (rsp.FromString(s))
            {
                std::cout << "english_to_chinese Success" << std::endl;
            }
            else
            {
                std::cerr << "english_to_chinese Failed" << std::endl;
            }
        }
    }
    //client.io_service->run();
    return "";
}

void CWordTranslateClient::SentenceToWords()
{
    HttpClient client("localhost:8080");
    {
        EnglishToChineseReq_t req;
        req.m_strToken = "test@test.com";
        req.m_strEnglish = "The color of flower is red";
    
        auto rsp = client.request("POST", "/v1/sentence_to_words", req.ToString().c_str());
        if (rsp)
        {
            std::string strRsp = rsp->content.string();
            std::cout << "RSP : " << strRsp << std::endl;
            SentenceToWordsRsp_t rsp;
            if (rsp.FromString(strRsp))
            {
                std::cout << "SentenceToWords Success" << std::endl;
            }
            else
            {
                std::cout << "SentenceToWords Failed" << std::endl;
            }
        }
    }
}

void CWordTranslateClient::AddWordToKnown()
{
    HttpClient client("localhost:8080");
    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"apple"})";
        auto rsp = client.request("POST", "/v1/add_word_to_known", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }
}

void CWordTranslateClient::AddWordToUnKnown()
{
    HttpClient client("localhost:8080");
    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","word":"orange"})";
        auto rsp = client.request("POST", "/v1/add_word_to_unknown", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }
}

void CWordTranslateClient::SetUserLanguageLevel()
{
    HttpClient client("localhost:8080");
    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","level":10})";
        auto rsp = client.request("POST", "/v1/set_user_language_level$", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }
}

std::string CWordTranslateClient::GetRequestDefault()
{
    return "";
}

std::string CWordTranslateClient::PostRequestDefault()
{
    return "";
}


int main(int argc, char* argv[])
{
    try {
        CWordTranslateClient client;
        client.GetVersion();
        client.EnglishToChinese("apple");
        client.SentenceToWords();
        client.AddWordToKnown();
        client.AddWordToUnKnown();
        client.SetUserLanguageLevel();
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}