#include "lexer.hpp"
#include "result.hpp"
#include <optional>
#include <string>

namespace unilang {
std::optional<Error<std::string>> Lexer::lexNext() {
	char ch = advance().unwrap();

	switch (ch) {
		default:
			std::string errorString = "Unknown character: ";
			errorString.push_back(ch);
			return Error<std::string>(errorString);
	}
}

Result<char, std::string> Lexer::advance() {
	if (isAtEnd()) {
		return Error<std::string>("Attempted to advance while at the end of the string!");
	}

	return source[current++];
}

bool Lexer::isAtEnd() const {
	return current < source.size();
}
}; //namespace unilang
