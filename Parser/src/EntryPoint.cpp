// Entry Point containing the main() function
#include "Lexer.h"

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <iterator>
#include <tuple>



constexpr const char* splFile = "spool.sp";


int main(int argc, char** argv)
{
    std::regex reSeparators("class [_a-zA-Z]+[0-9]*[_a-zA-Z]*|(var)[ \t\n]+([_a-zA-Z]+[0-9]*[_a-zA-Z]*)(,[ \t\n]*[_a-zA-Z]+[0-9]*[_a-zA-Z]*)*[ \t\n]*;|[{}]|fn[ \t\n]+[_a-zA-Z]+[0-9]*[_a-zA-Z]*[ \t\n]*;|entry|exit|if|endif|then|else|while|[_a-zA-Z]+[0-9]*[_a-zA-Z]*|[0-9]|[1-9][0-9]*|[<>]|>=|<=|==|!=|=|[+-/%]", std::regex::ECMAScript);
    std::ifstream inFile(splFile);


    Lexer lexer(std::move(inFile), Lexer::Pass(Lexer::Pass::Type::Tokenize, reSeparators));

    std::regex reCleanExtraWS("[\t ]+", std::regex::extended);
    std::regex pass2("[{}]", std::regex::extended);

    //std::regex reCleanSpaces("[\t\ ]{2,}", std::regex::extended);

    //lexer.AddRegexPass(Lexer::Pass(Lexer::Pass::Type::Replace, reCleanExtraWS, std::regex_constants::format_first_only | std::regex_constants::match_continuous, ""));
    //.AddRegexPass(Lexer::Pass(Lexer::Pass::Type::Replace, reCleanSpaces));
    lexer.ExecPasses();
    lexer.PrintTokens(std::cout);

    return 0;
}
