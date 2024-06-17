cmake_minimum_required(VERSION 3.5)
project(WordDictWebServer)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DASIO_STANDALONE)
include_directories(./include/base/)
include_directories(./include/thirdparty/asio/)
include_directories(./include/thirdparty/json11/)


add_executable(DictWebServer ./server/http_server.cpp ./server/EnglishChineseWordDict.cpp ./include/thirdparty/json11/json11.cpp)
add_executable(DictWebClient ./client/http_client.cpp)