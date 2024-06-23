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

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using Response_SHARED_PTR = std::shared_ptr<HttpServer::Response>;
using Request_SHARED_PTR = std::shared_ptr<HttpServer::Request>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

class CWordTranslateClient
{
public:
    std::string GetVersion();
    std::string EnglishToChinese(std::string strEnglish);
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
        std::cout << rsp->content.rdbuf() << std::endl;
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
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"apple"})";
        auto rsp = client.request("POST", "/v1/english_to_chinese", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }

    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"orange"})";
        auto rsp = client.request("POST", "/v1/english_to_chinese", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }

    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"The color of flower is red"})";
        auto rsp = client.request("POST", "/v1/sentence_to_words", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }

    {
        std::string strReqContent = R"({"token":"dennisthink@hotmail.com","english":"I like eating apples"})";
        auto rsp = client.request("POST", "/v1/sentence_to_words", strReqContent.c_str());
        if (rsp)
        {
            std::cout << rsp->content.rdbuf() << std::endl;
        }
    }
    //client.io_service->run();
    return "";
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
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}