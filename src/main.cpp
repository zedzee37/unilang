#include "lexer.hpp"
#include "result.hpp"
#include "token.hpp"
#include <expected>
#include <iostream>
#include <string>
#include <vector>

int main() {
	std::string source = "(){} \"guh\" 15.34324 a";
	unilang::Result<std::vector<unilang::Token>, std::string> maybeTokens = unilang::Lexer::lex(source);
	std::vector<unilang::Token> tokens = maybeTokens.unwrap();

	for (const unilang::Token &tok : tokens) {
		std::cout << "Token: " << tok.lexeme << '\n';
	}

	return 0;
}
