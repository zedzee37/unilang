#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "core_defs.hpp"
#include <string>

namespace unilang {
enum TokenType {
	LEFT_PAREN,
	RIGHT_PAREN,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	LEFT_BRACE,
	RIGHT_BRACE,
	MINUS,
	PLUS,
	EQUALS,
	STAR,
	SLASH,
	DOT,
	COMMA,
	STRING,
	NUMBER,
	NIL,

	IDENTIFIER,
	BREAK,
	TRUE,
	FALSE,
	PROCEDURE,
	WHILE,
	IF,
	OTHERWISE,
	START,
	END,
	CONVERSELY,
	AND,
	MATCHES,
	LESS,
	GREATER,
	RETURN,
	NOT,
	EOP,
};

typedef std::variant<std::string, f64, std::nullptr_t> Literal;

struct Token {
	TokenType type;
	std::string lexeme;
	u32 line;
	Literal literal;
};

} //namespace unilang

#endif
