#include "Lexer.h"

#include <stdexcept>
#include <cassert>


Lexer::Lexer(std::ifstream&& file, Pass initialPass)
    : Input(std::move(file))
{
    if(Input.fail())
        throw std::logic_error("Lexer: Input is in a fail state.\n");

    if(initialPass.type == Pass::Type::Tokenize)
    {
        std::stringstream program;
        program << Input.rdbuf();
        std::string code = program.str();

        std::copy(std::sregex_token_iterator(code.begin(), code.end(), initialPass.passRegex, initialPass.flag), std::sregex_token_iterator(), std::back_inserter(Tokens));
    }
    else
        throw std::logic_error("The first pass in the lexer must always tokenize the input.\n");
}

Lexer::~Lexer()
{

}

Lexer& Lexer::AddRegexPass(const Pass& pass)
{
    RegexPasses.push_back(pass);
    return *this;
}

uint32_t Lexer::ExecPasses()
{
    for(auto pass = RegexPasses.begin(); pass != RegexPasses.end(); pass++)
    {

        switch(pass->type)
        {
            case Pass::Type::Match:
                break;

            case Pass::Type::Replace:
                //TODO: find a faster, simpler, more elegant way to do this
                for(auto& str : Tokens)
                {
                    str = std::regex_replace(str, pass->passRegex, pass->helperStr, pass->flag);
                }
                break;

            case Pass::Type::Tokenize:
                throw std::logic_error("Only the first pass must tokenize the input.\n");
                break;

            default:
                throw std::logic_error("default in switch was hit in Lexer::ExecPass().\n");
                break;
        }

        RegexPasses.erase(pass);
    }
}

void Lexer::PrintTokens(std::ostream& os)
{
    for (auto& token : Tokens)
        os << "<" << token << "> ";
    os << "\n";
}
