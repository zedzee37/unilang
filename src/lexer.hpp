#ifndef LEXER_HPP
#define LEXER_HPP

#include "core_defs.hpp"
#include "token.hpp"
#include <expected>
#include <vector>

namespace unilang {
class Lexer {
public:
	Lexer(std::string source) :
			source(source), start(0), current(0), line(1) {}
	~Lexer();

	static std::vector<Token> lex(std::string source);

private:
	std::string source;
	std::vector<Token> tokens;
	u32 start;
	u32 current;
	u32 line;

	void lexNext();
	char advance();
	bool isAtEnd();
};

} //namespace unilang

#endif
