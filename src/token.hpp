#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "core_defs.hpp"
#include <string>
#include <variant>

namespace unilang {
enum TokenType {

};

struct Token {
	TokenType type;
	std::string lexeme;
	u32 line;
	std::variant<std::string, f32> literal;
};

} //namespace unilang

#endif
