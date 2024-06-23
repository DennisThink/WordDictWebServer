#include <iostream>
#include <fstream> 
#include <string> 
#include <ostream>
#include <vector>
#include "word_dict_struct.hpp"
#include "CDictDatabaseSqlite.hpp"
#include "CDictDatabaseMySql.hpp"
#include "dict_tool.hpp"

int SqliteDemo(int argc, char* argv[])
{
    CdictTool tool;
    auto allWords = tool.GetAllWords(argv[1]);
    CDictDatabaseSqlite sqliteDB(argv[2]);
    for (auto item : allWords)
    {
        std::cout << sqliteDB.InsertWordElem(item) << "  " << item << std::endl;
    }
    
    auto searchResult = sqliteDB.GetTranslation("apple");
    std::cout << "Result for: \"apple\"  Result: " << searchResult << std::endl;
    std::cout << allWords.size() << std::endl;
	return 0;
}

int main(int argc, char* argv[])
{
    CDictDatabaseMysql mysqlDb(argv[0]);
    return 0;
}