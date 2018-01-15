#include <iterator>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <sstream>
#include <string>
#include <cstring>
#include <regex>
#include <stack>
#include <map>

enum Symbol : uint32_t
{
	Invalid,

	T_hash,
	T_epsilon,
	T_number,
	T_name,
	T_begin,
	T_end,
	T_entry,

	T_self,
	T_as,
	T_inherit,
	T_dot,
	T_return,
	T_subtype,
	T_cast,

	T_if,
	T_then,
	T_else,
	T_endif,

	T_while,
	T_do,
	T_endloop,
	
	T_op_plus,
	T_op_minus,
	T_op_star,
	T_op_div,

	T_op_comp_less,
	T_op_comp_greater,
	T_op_comp_lesseq,
	T_op_comp_greatereq,
	T_op_comp_eq,
	T_op_comp_noteq,

	T_op_equals,
	T_var,
	T_type,
	T_fn,
	T_call,

	T_l_parens,
	T_r_parens,
	T_semicolon,
	T_comma,

	T_logical_and,
	T_logical_or,
	T_logical_not,

	N_numeric_expression,
	N_numeric_expression_helper,
	N_conditional_expression,
	N_conditional_expression_helper,
	N_term,
	N_term_helper,
	N_factor,
	N_expression,
	N_expression_list,
	N_expression_list_helper,
	N_statement,
	N_statement_list,


	N_declaration,
	N_var_declaration,
	N_param_declaration,
	N_param_declaration_list,
	N_param_declaration_list_helper,
	N_fn_declaration,
	N_type_declaration

};

std::string ToString(Symbol sym)
{
	switch (sym)
	{
	case T_hash:
		return "T_hash";

	case T_comma:
		return "T_comma";

	case T_begin:
		return "T_begin";

	case T_end:
		return "T_end";

	case T_name:
		return "T_name";

	case T_var:
		return "T_var";

	case T_type:
		return "T_type";

	case T_fn:
		return "T_fn";
	case T_call:
		return "T_call";

	case T_number:
		return "T_number";



	case T_self:
		return "T_self";
	case T_as:
		return "T_as";
	case T_inherit:
		return "T_inherit";
	case T_dot:
		return "T_dot";
	case T_subtype:
		return "T_subtype";
	case T_cast:
		return "T_cast";


	case T_logical_and:
		return "T_logical_and";
	case T_logical_not:
		return "T_logical_not";
	case T_logical_or:
		return "T_logical_or";


	case T_op_plus:
		return "T_op_plus";
	case T_op_minus:
		return "T_op_minus";
	case T_op_star:
		return "T_op_star";
	case T_op_div:
		return "T_op_div";
	case T_op_equals:
		return "T_op_equals";

	case T_op_comp_less:
		return "T_op_comp_less";
	case T_op_comp_lesseq:
		return "T_op_comp_lesseq";
	case T_op_comp_greater:
		return "T_op_comp_greater";
	case T_op_comp_greatereq:
		return "T_op_comp_greatereq";
	case T_op_comp_eq:
		return "T_op_comp_eq";
	case T_op_comp_noteq:
		return "T_op_comp_noteq";

	case T_l_parens:
		return "T_l_parens";
	case T_r_parens:
		return "T_r_parens";
	case T_semicolon:
		return "T_semicolon";
	case T_epsilon:
		return "T_epsilon";

	

	case T_entry:
		return "T_entry";


	case T_if:
		return "T_if";
	case T_else:
		return "T_else";
	case T_then:
		return "T_then";
	case T_endif:
		return "T_endif";

	
	case T_while:
		return "T_while";
	case T_do:
		return "T_do";
	case T_endloop:
		return "T_endloop";

	
	case T_return:
		return "T_return";

	
	case N_numeric_expression:
		return "N_numeric_expression";
	case N_numeric_expression_helper:
		return "N_numeric_expression_helper";

	case N_conditional_expression:
		return "N_conditional_expression";
	case N_conditional_expression_helper:
		return "N_conditional_expression_helper";

	case N_term_helper:
		return "N_term_helper";

	case N_term:
		return "N_term";

	case N_factor:
		return "N_factor";

	case N_statement:
		return "N_statement";

	case N_expression:
		return "N_expression";
	case N_expression_list:
		return "N_expression_list";
	case N_expression_list_helper:
		return "N_expression_list_helper";

	case N_statement_list:
		return "N_statement_list";



	case N_declaration:
		return "N_declaration";
	case N_var_declaration:
		return "N_var_declaration";
	case N_param_declaration:
		return "N_param_declaration";
	case N_param_declaration_list:
		return "N_param_declaration_list";
	case N_param_declaration_list_helper:
		return "N_param_declaration_list_helper";
	case N_fn_declaration:
		return "N_fn_declaration";
	case N_type_declaration:
		return "N_type_declaration";

	}
#ifndef NDEBUG
	exit(1);
#endif
	return "ToString(): UNIDENTIFIED SYMBOL";
}

Symbol ToSymbol(std::pair<std::string, std::string> match)
{
	if (match.second == "T_number")
		return Symbol::T_number;
	if (match.second == "T_name")
		return Symbol::T_name;
	if (match.second == "T_var")
		return Symbol::T_var;
	if (match.second == "T_fn")
		return Symbol::T_fn;
	if (match.second == "T_call")
		return Symbol::T_call;
	if (match.second == "T_type")
		return Symbol::T_type;


	if (match.second == "T_as")
		return Symbol::T_as;
	if (match.second == "T_inherit")
		return Symbol::T_inherit;
	if (match.second == "T_self")
		return Symbol::T_self;
	if (match.second == "T_dot")
		return Symbol::T_dot;
	if (match.second == "T_subtype")
		return Symbol::T_subtype;
	if (match.second == "T_cast")
		return Symbol::T_cast;


	if (match.second == "T_logical_and")
		return T_logical_and;
	if (match.second == "T_logical_or")
		return T_logical_or;
	if (match.second == "T_logical_not")
		return T_logical_not;


	if (match.second == "T_op_plus")
		return Symbol::T_op_plus;
	if (match.second == "T_op_minus")
		return Symbol::T_op_minus;
	if (match.second == "T_op_star")
		return Symbol::T_op_star;
	if (match.second == "T_op_div")
		return Symbol::T_op_div;


	if (match.second == "T_op_equals")
		return Symbol::T_op_equals;
	if (match.second == "T_op_comp_less")
		return Symbol::T_op_comp_less;
	if (match.second == "T_op_comp_greater")
		return Symbol::T_op_comp_greater;
	if (match.second == "T_op_comp_lesseq")
		return Symbol::T_op_comp_lesseq;
	if (match.second == "T_op_comp_greatereq")
		return Symbol::T_op_comp_greatereq;
	if (match.second == "T_op_comp_eq")
		return Symbol::T_op_comp_eq;
	if (match.second == "T_op_comp_noteq")
		return Symbol::T_op_comp_noteq;


	if (match.second == "T_hash")
		return Symbol::T_hash;
	if (match.second == "T_epsilon")
		return Symbol::T_epsilon;


	if (match.second == "T_l_parens")
		return Symbol::T_l_parens;
	if (match.second == "T_r_parens")
		return Symbol::T_r_parens;


	if (match.second == "T_semicolon")
		return Symbol::T_semicolon;
	if (match.second == "T_comma")
		return Symbol::T_comma;
	if (match.second == "T_begin")
		return Symbol::T_begin;
	if (match.second == "T_end")
		return Symbol::T_end;
	if (match.second == "T_entry")
		return Symbol::T_entry;


	if (match.second == "T_if")
		return Symbol::T_if;
	if (match.second == "T_then")
		return Symbol::T_then;
	if (match.second == "T_else")
		return Symbol::T_else;
	if (match.second == "T_endif")
		return Symbol::T_endif;


	if (match.second == "T_return")
		return Symbol::T_return;


	if (match.second == "T_while")
		return Symbol::T_while;
	if (match.second == "T_do")
		return Symbol::T_do;
	if (match.second == "T_endloop")
		return Symbol::T_endloop;


	if (match.second == "N_numeric_expression")
		return Symbol::N_numeric_expression;
	if (match.second == "N_numeric_expression_helper")
		return Symbol::N_numeric_expression_helper;
	if (match.second == "N_conditional_expression_helper")
		return Symbol::N_conditional_expression_helper;
	if (match.second == "N_conditional_expression")
		return Symbol::N_conditional_expression;
	if (match.second == "N_term")
		return Symbol::N_term;
	if (match.second == "N_term_helper")
		return Symbol::N_term_helper;
	if (match.second == "N_factor")
		return Symbol::N_factor;
	if (match.second == "N_statement")
		return Symbol::N_statement;
	if (match.second == "N_statement_list")
		return Symbol::N_statement_list;
	if (match.second == "N_expression")
		return Symbol::N_expression;
	if (match.second == "N_expression_list")
		return Symbol::N_expression_list;
	if (match.second == "N_expression_list_helper")
		return Symbol::N_expression_list_helper;


	if (match.second == "N_declaration")
		return Symbol::N_declaration;
	if (match.second == "N_var_declaration")
		return Symbol::N_var_declaration;
	if (match.second == "N_param_declaration_list")
		return Symbol::N_param_declaration_list;
	if (match.second == "N_param_declaration_list_helper")
		return Symbol::N_param_declaration_list_helper;
	if (match.second == "N_param_declaration")
		return Symbol::N_param_declaration;
	if (match.second == "N_fn_declaration")
		return Symbol::N_fn_declaration;
	if (match.second == "N_type_declaration")
		return Symbol::N_type_declaration;

#ifndef NDEBUG
	printf("ToSymbol(): Unidentified string symbol: %s\n", match.second.c_str());
	exit(1);
#endif
	return Symbol::Invalid;
}

struct GrammarRule
{
	Symbol LHS_Symbol;
	std::string LHS_String;

	std::vector<Symbol> RHS_Symbols;
	std::string RHS_String;

	explicit GrammarRule(std::string LHS, std::string RHS)
		: LHS_String(LHS)
		, RHS_String(RHS)
	{

	}
};

std::map<uint32_t, GrammarRule> BuildGrammarMap()
{
	std::map<uint32_t, GrammarRule> RuleMap;
	uint32_t lastIndex = 1;


	// Open rule file
	std::ifstream rulesFile("rules.txt");

	assert(!rulesFile.fail());

	std::string rule;

	while (std::getline(rulesFile, rule))
	{
		RuleMap.insert(
						std::make_pair(
										lastIndex, 
										GrammarRule(
													  rule.substr(0, rule.find_first_of(' '))
													, rule.substr(rule.find_first_of(' ') + 1, rule.size() - rule.find_first_of(' ') - 1)
												   ) 
									  )
					  );

		std::regex re("[A-Za-z_]+");
		auto&& words_begin = std::sregex_iterator(RuleMap.at(lastIndex).RHS_String.begin(), RuleMap.at(lastIndex).RHS_String.end(), re);
		auto&& words_end = std::sregex_iterator();

		for (auto it = words_begin; it != words_end; ++it)
		{
			RuleMap.at(lastIndex).RHS_Symbols.push_back(ToSymbol(std::make_pair("", it->str())));
		}	

		lastIndex++;
	}

	return RuleMap;
}

std::map<Symbol, std::map<Symbol, uint32_t>> BuildParsingTable()
{
	std::map<Symbol, std::map<Symbol, uint32_t>> ParsingTable;

	ParsingTable[Symbol::N_numeric_expression][Symbol::T_hash] = 1;
	ParsingTable[Symbol::N_numeric_expression][Symbol::T_r_parens] = 1;
	ParsingTable[Symbol::N_numeric_expression][Symbol::T_number] = 1;

	ParsingTable[N_conditional_expression][T_if] = 36;
	ParsingTable[N_conditional_expression][T_while] = 39;

	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_hash] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_l_parens] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_op_plus] = 2;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_op_minus] = 3;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_op_star] = 50;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_op_div] = 50;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_semicolon] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_comma] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_then] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_do] = 4;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_logical_and] = 42;
	ParsingTable[Symbol::N_numeric_expression_helper][Symbol::T_logical_or] = 43;

	ParsingTable[Symbol::N_term][Symbol::T_r_parens] = 5;
	ParsingTable[Symbol::N_term][Symbol::T_number] = 5;

	ParsingTable[Symbol::N_term_helper][Symbol::T_hash] = 8;
	ParsingTable[Symbol::N_term_helper][Symbol::T_l_parens] = 8;
	ParsingTable[Symbol::N_term_helper][Symbol::T_op_plus] = 8;
	ParsingTable[Symbol::N_term_helper][Symbol::T_op_minus] = 8;
	ParsingTable[Symbol::N_term_helper][Symbol::T_op_div] = 7;
	ParsingTable[Symbol::N_term_helper][Symbol::T_op_star] = 6;
	ParsingTable[Symbol::N_term_helper][Symbol::T_semicolon] = 8;
	ParsingTable[Symbol::N_term_helper][T_comma] = 8;
	ParsingTable[Symbol::N_term_helper][T_logical_and] = 8;
	ParsingTable[Symbol::N_term_helper][T_logical_or] = 8;

	ParsingTable[Symbol::N_term_helper][T_then] = 8;
	ParsingTable[Symbol::N_term_helper][T_do] = 8;
	ParsingTable[Symbol::N_term_helper][T_op_comp_less] = 37;
	ParsingTable[Symbol::N_term_helper][T_op_comp_greater] = 44;
	ParsingTable[Symbol::N_term_helper][T_op_comp_lesseq] = 45;
	ParsingTable[Symbol::N_term_helper][T_op_comp_greatereq] = 46;
	ParsingTable[Symbol::N_term_helper][T_op_comp_eq] = 47;
	ParsingTable[Symbol::N_term_helper][T_op_comp_noteq] = 48;

	ParsingTable[Symbol::N_factor][Symbol::T_r_parens] = 9;
	ParsingTable[Symbol::N_factor][Symbol::T_number] = 10;

	ParsingTable[Symbol::N_statement_list][T_number] = 13;
	ParsingTable[Symbol::N_statement_list][T_return] = 13;
	ParsingTable[Symbol::N_statement_list][T_name] = 13;
	ParsingTable[Symbol::N_statement_list][T_hash] = 14;
	ParsingTable[Symbol::N_statement_list][T_end] = 14;
	ParsingTable[Symbol::N_statement_list][T_var] = 13;
	ParsingTable[Symbol::N_statement_list][T_type] = 13;
	ParsingTable[Symbol::N_statement_list][T_subtype] = 13;
	ParsingTable[Symbol::N_statement_list][T_fn] = 13;
	ParsingTable[Symbol::N_statement_list][T_call] = 13;
	ParsingTable[Symbol::N_statement_list][T_entry] = 28;
	ParsingTable[Symbol::N_statement_list][T_if] = 13;
	ParsingTable[Symbol::N_statement_list][T_while] = 13;
	ParsingTable[Symbol::N_statement_list][T_endif] = 14;
	ParsingTable[Symbol::N_statement_list][T_endloop] = 14;
	ParsingTable[Symbol::N_statement_list][T_else] = 38;
	ParsingTable[Symbol::N_statement_list][T_self] = 13;
	ParsingTable[Symbol::N_statement_list][T_cast] = 13;

	ParsingTable[Symbol::N_statement][T_number] = 12;
	ParsingTable[Symbol::N_statement][T_return] = 12;
	ParsingTable[Symbol::N_statement][T_name] = 15;
	ParsingTable[Symbol::N_statement][T_var] = 16;
	ParsingTable[Symbol::N_statement][T_type] = 16;
	ParsingTable[Symbol::N_statement][T_subtype] = 16;
	ParsingTable[Symbol::N_statement][T_fn] = 16;
	ParsingTable[Symbol::N_statement][T_call] = 12;
	ParsingTable[Symbol::N_statement][T_if] = 12;
	ParsingTable[Symbol::N_statement][T_while] = 12;
	ParsingTable[Symbol::N_statement][T_self] = 12;
	ParsingTable[Symbol::N_statement][T_cast] = 12;

	ParsingTable[Symbol::N_declaration][T_var] = 17;
	ParsingTable[Symbol::N_declaration][T_type] = 19;
	ParsingTable[Symbol::N_declaration][T_subtype] = 19;
	ParsingTable[Symbol::N_declaration][T_fn] = 18;

	ParsingTable[Symbol::N_var_declaration][T_var] = 20;
	ParsingTable[Symbol::N_type_declaration][T_type] = 21;
	ParsingTable[Symbol::N_type_declaration][T_subtype] = 52;
	ParsingTable[Symbol::N_fn_declaration][T_fn] = 22;

	ParsingTable[Symbol::N_param_declaration][T_var] = 27;
	ParsingTable[Symbol::N_param_declaration_list][T_var] = 23;
	ParsingTable[Symbol::N_param_declaration_list][T_l_parens] = 24;
	ParsingTable[Symbol::N_param_declaration_list_helper][T_comma] = 25;
	ParsingTable[Symbol::N_param_declaration_list_helper][T_l_parens] = 26;

	ParsingTable[Symbol::N_expression][T_number] = 11;
	ParsingTable[Symbol::N_expression][T_return] = 55;
	ParsingTable[Symbol::N_expression][T_call] = 29;
	ParsingTable[Symbol::N_expression][T_if] = 35;
	ParsingTable[Symbol::N_expression][T_while] = 35;
	ParsingTable[Symbol::N_expression][T_name] = 49;
	ParsingTable[Symbol::N_expression][T_self] = 54;
	ParsingTable[Symbol::N_expression][T_dot] = 51;
	ParsingTable[Symbol::N_expression][T_cast] = 53;

	ParsingTable[Symbol::N_expression_list][T_l_parens] = 30;
	ParsingTable[Symbol::N_expression_list][T_number] = 31;

	ParsingTable[Symbol::N_expression_list_helper][T_comma] = 32;
	ParsingTable[Symbol::N_expression_list_helper][T_number] = 33;
	

	return ParsingTable;
}

int main(int argc, char** argv)
{
	bool pretty_print = false;
	std::ifstream inputFile;

	if (argc < 2)
	{
		printf("No file was given as input. Will default to file example.sp\n");
		pretty_print = true;
		inputFile.open("example.sp");
	}
	else
	{
		if (argc >= 3 && strcmp(argv[2], "pretty_print") == 0)
			pretty_print = true;
		
		inputFile.open(argv[1]);
	}

	assert(!inputFile.fail());

	std::string str;
	std::stringstream temp;
	temp << inputFile.rdbuf();
	str = temp.str();

	std::vector<std::pair<std::string, std::string>> RegexMap
	{
		{ "fn", "T_fn" },
		{ "call", "T_call"},
		{ "var", "T_var" },

		{ "entry", "T_entry" },

		{ "create", "T_create" },
		{ "self", "T_self" },
		{ "as", "T_as" },
		{ "cast", "T_cast" },

		{ "type", "T_type" },
		{ "subtype", "T_subtype"},
		{ "begin", "T_begin"},

		{ "&&", "T_logical_and"},
		{ "\\|\\|", "T_logical_or" },
		{ "not", "T_logical_not" },

		{ "endif", "T_endif" },
		{ "endloop", "T_endloop" },
		{ "end", "T_end"},
		
		{ "break", "T_break" },
		{ "continue", "T_continue" },
		{ "do", "T_do" },
		{ "return", "T_return" },
		{ "panic!", "T_panic" },
		{ "\".*\"", "T_quoted_string" },
		{ "for", "T_for" },
		{ "from", "T_from" },
		{ "to", "T_to" },
		{ "inherit", "T_inherit" },
		{ "exit", "T_exit" },
		{ "while", "T_while" },
		{ "if", "T_if" },
		{ "then", "T_then" },
		{ "else", "T_else" },
		

		
		{ "[_a-zA-Z][_a-zA-Z]*[0-9]*[_a-zA-Z]*" , "T_name" },
		{ "[0-9]\\.[0-9]+", "T_number" },
		{ "[1-9][0-9]*\\.[0-9]*", "T_number" },
		{ "[1-9][0-9]+", "T_number" },
		
		{ "[0-9]", "T_number" },

		{ "\\.", "T_dot" },

		{ "bitfield", "T_bitfield" },
		{ "string", "T_string" },


		{ "<=", "T_op_comp_lesseq" },
		{ "<", "T_op_comp_less" },
		{ ">=", "T_op_comp_greatereq" },
		{ ">", "T_op_comp_greater" },
		{ "==", "T_op_comp_eq" },
		{ "!=", "T_op_comp_noteq" },


		{ "\\+", "T_op_plus"},
		{ "-", "T_op_minus" },
		{ "/", "T_op_div" },
		{ "\\*", "T_op_star" },
		{ "=", "T_op_equals" },
		

		{"\\(", "T_r_parens"},
		{ "\\)", "T_l_parens" },
		{ ";", "T_semicolon" },
		{ ",", "T_comma" }
	};

	std::string reg;

	for (auto const& x : RegexMap)
		reg += "(" + x.first + ")|"; // parenthesize the submatches

	reg.pop_back();
	std::cout << "Tokenizing input using regex: " << reg << std::endl << std::endl;

	std::regex re(reg);
	auto&& words_begin = std::sregex_iterator(str.begin(), str.end(), re);
	auto&& words_end = std::sregex_iterator();
	std::vector<std::pair<std::string, std::string>> InputTokens;

	for (auto it = words_begin; it != words_end; ++it)
	{
		size_t index = 0;

		for (; index < it->size(); ++index)
			if (!it->str(index + 1).empty()) // determine which submatch was matched
				break;

		InputTokens.push_back(std::make_pair(it->str(), RegexMap[index].second));
	}

	InputTokens.push_back(std::make_pair("#", "T_hash"));


#ifndef NDEBUG
	for (const auto& token : InputTokens)
	{
		std::cout << "<" << token.first << "> was matched as a " << token.second << std::endl;
	}
	std::cout << std::endl << std::endl;
#endif

	auto RuleMap = BuildGrammarMap();


#ifndef NDEBUG
	printf("Grammar rules:\n");
	for (const auto& rule : RuleMap)
	{
		printf("%d: %s -> %s\n", rule.first, rule.second.LHS_String.c_str(), rule.second.RHS_String.c_str());
		printf("RHS as vector: ");
		for (const auto& sym : rule.second.RHS_Symbols)
		{
			std::cout << ToString(sym) << " ";
		}
		std::cout << std::endl;
	}
	printf("\n\n");
#endif

	auto ParsingTable = BuildParsingTable();

#ifndef NDEBUG
	printf("Parsing table:\n");
	for (const auto& p : ParsingTable)
	{
		for (const auto & new_p : p.second)
		{
			printf("( %s, %s ): Expand with rule %u\n", ToString(p.first).c_str(), ToString(new_p.first).c_str(), new_p.second);
		}
	}
	printf("\n\n");
#endif

	std::stack<Symbol> SymbolStack;

	// Put the EOS symbol at the bottom of the stack
	// and the starting symbol after it

	SymbolStack.push(Symbol::T_hash);
	SymbolStack.push(Symbol::N_statement_list);

	auto&& TokenIter = InputTokens.begin();

	while (!SymbolStack.empty())
	{
		Symbol InputSymbol = ToSymbol(*TokenIter);

		#ifndef NDEBUG
		printf("Trying to parse for stack symbol %s and input symbol %s\n", ToString(SymbolStack.top()).c_str(), ToString(InputSymbol).c_str());
		#endif

		if (SymbolStack.top() == InputSymbol)
		{
			#ifndef NDEBUG
			printf("Matched symbols: %s %s\n", ToString(SymbolStack.top()).c_str(), ToString(InputSymbol).c_str());
			#endif

			SymbolStack.pop();
			
			TokenIter++;
			continue;
		}
		else
		{
			// If there are expansions in the parsing table that contain the current stack symbol
			if (ParsingTable.find(SymbolStack.top()) != ParsingTable.end())
			{
				auto&& ruleNoIter = ParsingTable.find(SymbolStack.top())->second.find(InputSymbol);
				// If any of that expansions also contains the input symbol
				if (ruleNoIter != ParsingTable.find(SymbolStack.top())->second.end())
				{
					assert(!RuleMap.at(ruleNoIter->second).RHS_Symbols.empty());
					#ifndef NDEBUG
					printf("( %s, %s ): Expanding with rule %u: ", ToString(SymbolStack.top()).c_str(), ToString(InputSymbol).c_str(), ruleNoIter->second);
					printf("%s -> %s\n", RuleMap.at(ruleNoIter->second).LHS_String.c_str(), RuleMap.at(ruleNoIter->second).RHS_String.c_str());
					#endif

					SymbolStack.pop();

					#ifndef NDEBUG
					printf("Pushing: ");
					#endif
					for (auto& symbolIter = RuleMap.at(ruleNoIter->second).RHS_Symbols.rbegin(); symbolIter != RuleMap.at(ruleNoIter->second).RHS_Symbols.rend(); symbolIter++)
					{
						if (*symbolIter != Symbol::T_epsilon)
						{
							SymbolStack.push(*symbolIter);
							#ifndef NDEBUG
							printf("%s ", ToString(*symbolIter).c_str());
							#endif
						}
					}
					printf("\n");

					
				}
				else
				{
					printf("Syntax error.\n");
					exit(1);
				}
			}
			else
			{
				#ifndef NDEBUG
				printf("\nSyntax error: No rule was found to contain %s\n", ToString(SymbolStack.top()).c_str());
				
				printf("Stack: ");
				while (!SymbolStack.empty())
				{
					std::cout << ToString(SymbolStack.top()) << " ";
					SymbolStack.pop();
				}

				printf("\nInput: ");
				while (TokenIter != InputTokens.end())
				{
					std::cout << TokenIter->second << " ";
					TokenIter++;
				}


				#endif
				exit(1);
			}
		}
	}

	printf("\nThe program is syntactically correct.\n\n");

	int a;
	std::cin >> a;

	return 0;
}
