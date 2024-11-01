#ifndef LEXER_HPP
#define LEXER_HPP

#include "core_defs.hpp"
#include "result.hpp"
#include "token.hpp"
#include <expected>
#include <optional>
#include <vector>

namespace unilang {
class Lexer {
public:
	Lexer(std::string source) :
			source(source), start(0), current(0), line(1) {}
	~Lexer();

	static Result<std::vector<Token>, std::string> lex(std::string source);

private:
	std::string source;
	std::vector<Token> tokens;
	u32 start;
	u32 current;
	u32 line;

	std::optional<Error<std::string>> lexNext();
	Result<char, std::string> advance();
	bool isAtEnd() const;
};

} //namespace unilang

#endif
