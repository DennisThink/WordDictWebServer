#include <iostream>
#include <fstream> 
#include <string> 
#include <ostream>
#include <vector>
#include "word_dict_struct.hpp"
#include "dict_tool.hpp"
int main(int argc, char* argv[])
{
    CdictTool tool;
    auto allWords = tool.GetAllWords(argv[1]);
    std::cout << allWords.size() << std::endl;
	return 0;
}