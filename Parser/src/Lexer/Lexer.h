#pragma once

#include <regex>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <tuple>
#include <utility>

// Lexer class; Given a SPOOL program file program.sp, output the sequence of tokens that make up the program.
class Lexer
{
private:

private:

public:
    struct Pass
    {
        enum class Type
        {
            Tokenize,
            Match,
            Replace
        };

        explicit Pass(Pass::Type t, std::regex rgx, std::regex_constants::match_flag_type regex_flags = std::regex_constants::format_default | std::regex_constants::match_default, std::string&& str = std::string())
            : type(t)
            , passRegex(rgx)
            , flag(regex_flags)
            , helperStr(std::move(str))
        {

        }

        virtual ~Pass(){}



        Type type;
        std::regex passRegex;
        std::regex_constants::match_flag_type flag;
        std::string helperStr;
    };

public:
    explicit Lexer(std::ifstream&& file, Pass initialPass);
    explicit Lexer(const Lexer&) = delete;
    explicit Lexer(Lexer&&) = delete;
    virtual ~Lexer();

    Lexer& AddRegexPass(const Pass& pass);
    void PrintTokens(std::ostream& os);
    uint32_t ExecPasses();

protected:

protected:
    std::vector<std::string>    Tokens;
    std::vector<Pass>    RegexPasses;

    std::ifstream Input;
};
