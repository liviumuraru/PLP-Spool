#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <sstream>

int main(int argc, char** argv)
{
    bool pretty_print = false;

    if(argc < 2)
        throw std::logic_error("No file was given as input. Usage: parse filename");

    if(argc >= 3 && strcmp(argv[2], "pretty_print") == 0)
        pretty_print = true;

    std::ifstream inputFile(argv[1]);

    assert(!inputFile.fail());

    std::string str;
    std::stringstream temp;
    temp << inputFile.rdbuf();
    str = temp.str();

    std::vector<std::pair<std::string, std::string>> RegexMap
    {
        {"fn[ \t\n]+[_a-zA-Z]+[0-9]*[_a-zA-Z]*[ \t\n]*\\([_a-zA-Z]+[0-9]*[_a-zA-Z]*(?:,[ \t\n]*[_a-zA-Z]+[0-9]*[_a-zA-Z]*)*\\)[ \t\n]*;", "FN_DECL"},
        {"var[ \t\n]+[_a-zA-Z]+[0-9]*[_a-zA-Z]*(?:,[ \t\n]*[_a-zA-Z]+[0-9]*[_a-zA-Z]*)*[ \t\n]*;", "VAR_DECL"},
        {"class [_a-zA-Z][0-9]*[_a-zA-Z]*", "CLASS_NAME"},
        {"entry", "ENTRY"},
        {"exit", "EXIT"},
        {"while", "WHILE"},
        {"if", "IF"},
        {"then", "THEN"},
        {"else", "ELSE"},
        {"endif", "ENDIF"},
        {"endloop", "ENDLOOP"},
        {"[1-9][0-9]+", "NUMBER"},
        {"[0-9]", "DIGIT"},
        {"[_a-zA-Z][0-9]*[_a-zA-Z]*" , "IDENTIFIER"},
        {">=|<=|==|!=", "MULTI_CHAR_OPS"},
        {"[\\*\\+=\\-/<>]", "SINGLE_CHAR_OPS"},
        {"[\\{\\}]", "BLOCK_BRACKET"},
        {";", "STMT_SEP"}
    };

    std::string reg;

    for(auto const& x : RegexMap)
        reg += "(" + x.first + ")|"; // parenthesize the submatches

    reg.pop_back();
    std::cout << "Tokenizing input using regex: " << reg << std::endl;

    std::regex re(reg);
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), re);
    auto words_end = std::sregex_iterator();

    for(auto it = words_begin; it != words_end; ++it)
    {
        size_t index = 0;

        for( ; index < it->size(); ++index)
            if(!it->str(index + 1).empty()) // determine which submatch was matched
                break;

        if(!pretty_print)
            std::cout << it->str() << "\t" << RegexMap[index].second << std::endl;
        else
            std::cout << "<" << it->str() << "> ";
    }
    std::cout << std::endl;

    return 0;
}
