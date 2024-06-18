cmake_minimum_required(VERSION 3.5)
project(WordDictWebServer)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DASIO_STANDALONE)
include_directories(./include/base/)
include_directories(./include/thirdparty/asio/)
include_directories(./include/thirdparty/json11/)
include_directories(./include/thirdparty/sqlite/)
include_directories(./include/thirdparty/)


add_executable(DictWebServer ./server/http_server.cpp 
                             ./server/EnglishChineseWordDict.cpp 
							 ./include/thirdparty/json11/json11.cpp)

add_executable(DictWebClient ./client/http_client.cpp)

add_executable(DictTool ./dict_tool/dict_tool_main.cpp 
						./include/base/dict_tool.cpp 
						./include/base/word_dict_struct.cpp)