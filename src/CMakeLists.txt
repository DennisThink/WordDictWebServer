cmake_minimum_required(VERSION 3.5)
project(WordDictWebServer)
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DASIO_STANDALONE)
include_directories(./include/base/)
include_directories(./include/thirdparty/asio/)
include_directories(./include/thirdparty/json11/)
include_directories(./include/thirdparty/sqlite/)
include_directories(./include/thirdparty/mysql_connector_cpp/)
include_directories(./include/thirdparty/)
include_directories(./include/thirdparty/mysqlwin/include/)
include_directories(./include/thirdparty/doctest/)
link_directories(./libs/mysql_connector_cpp/)

add_executable(DictWebServer ./server/http_server.cpp 
                             ./server/EnglishChineseWordDict.cpp 
							 ./include/thirdparty/json11/json11.cpp
							 ./include/base/dict_tool.cpp 
						     ./include/base/word_dict_struct.cpp
							./include/base/CDictDatabaseJson.cpp)

SET(INC_BASE ./include/)
SET(SQLITE_CPP_FILE ${INC_BASE}/thirdparty/SQLiteCpp/src/Backup.cpp  
					${INC_BASE}/thirdparty/SQLiteCpp/src/Column.cpp 
					${INC_BASE}/thirdparty/SQLiteCpp/src/Database.cpp 
					${INC_BASE}/thirdparty/SQLiteCpp/src/Exception.cpp 
					${INC_BASE}/thirdparty/SQLiteCpp/src/Savepoint.cpp 
					${INC_BASE}/thirdparty/SQLiteCpp/src/Statement.cpp 
					${INC_BASE}/thirdparty/SQLiteCpp/src/Transaction.cpp)
SET(SQLITE_FILE ${INC_BASE}/thirdparty/sqlite/sqlite3.c)
link_directories(./libs/mysqllib/lib/)

add_executable(DictWebClient ./client/http_client.cpp)


add_executable(Dict_Test ./dict_test/dict_test_main.cpp
						./include/base/word_dict_struct.cpp
						./include/base/CDictDatabaseSqlite.cpp
						./include/base/CDictDatabaseJson.cpp
						./include/thirdparty/json11/json11.cpp
						${SQLITE_CPP_FILE}
						${SQLITE_FILE})

add_executable(DictTool ./dict_tool/dict_tool_main.cpp 
						./include/base/dict_tool.cpp 
						./include/base/word_dict_struct.cpp
						./include/base/CDictDatabaseSqlite.cpp
						./include/base/CDictDatabaseMySql.cpp
						./include/base/CDictDatabaseJson.cpp
						./include/thirdparty/json11/json11.cpp
						${SQLITE_CPP_FILE}
						${SQLITE_FILE})
if(CMAKE_HOST_WIN32)
target_link_libraries(DictTool mysqlclient.lib)
else()
target_link_libraries(DictTool mysqlclient)
endif()

if(CMAKE_HOST_WIN32)
target_link_libraries(Dict_Test mysqlclient.lib)
else()
target_link_libraries(Dict_Test mysqlclient)
endif()