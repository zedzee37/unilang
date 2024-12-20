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
	~Lexer() = default;

	static Result<std::vector<Token>> lex(std::string source);

private:
	std::string source;
	std::vector<Token> tokens;
	u32 start;
	u32 current;
	u32 line;

	std::optional<Error> lexNext();
	Result<char> advance();
	Result<char> peek() const;
	std::optional<Error> stringToken();
	std::optional<Error> numberToken();
	void emptyToken(TokenType type);
	void token(TokenType type, Literal literal);
	void addToken(Token token);
	bool isAtEnd() const;
	std::vector<Token> getTokens() const;
};

} //namespace unilang

#endif
