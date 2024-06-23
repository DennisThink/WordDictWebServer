#include "dict_tool.hpp"
#include <iostream>
#include <fstream>
std::vector<DictLineElem_t> CdictTool::GetAllWords(const std::string strFileName)
{
    ReadFileLineByLine(strFileName);
    return m_allWords;
}
DictLineElem_t CdictTool::SplitLine(const std::string strLine)
{
    DictLineElem_t elem;
    std::size_t nFirstIndex = 0;
    std::size_t nSecondIndex = 0;
    {
        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strWord = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strPhonetic = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strDefinition = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strTranslation = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }


        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strPos = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strCollins = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strOxford = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strTag = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strBnc = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strFrq = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strExchange = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strDetail = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }

        {
            nSecondIndex = strLine.find_first_of(',', nFirstIndex);
            if (nSecondIndex != std::string::npos)
            {
                elem.m_strAudio = strLine.substr(nFirstIndex, nSecondIndex - nFirstIndex);
                nFirstIndex = nSecondIndex + 1;
            }
        }
    }
    return elem;

}
void CdictTool::ReadFileLineByLine(const std::string strFileName)
{
    // Create an input file stream object named 'file' and 
    // open the file "GFG.txt". 
    std::ifstream file(strFileName);

    // String to store each line of the file. 
    std::string line;

    if (file.is_open()) {
        // Read each line from the file and store it in the 
        // 'line' variable. 
        while (getline(file, line)) {
            std::cout << line << std::endl;
            std::cout << SplitLine(line) << std::endl;
            m_allWords.push_back(SplitLine(line));
        }

        // Close the file stream once all lines have been 
        // read. 
        file.close();
    }
    else {
        // Print an error message to the standard error 
        // stream if the file cannot be opened. 
        std::cerr << "Unable to open file!" << std::endl;
    }

}
