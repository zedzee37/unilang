#include "lexer.hpp"
#include "result.hpp"
#include "token.hpp"
#include <expected>
#include <iostream>
#include <string>
#include <vector>

void run(std::string source) {
	std::vector<unilang::Token> tokens = unilang::Lexer::lex(source).unwrap();

	for (const unilang::Token &token : tokens) {
		std::cout << token.type << ' ' << token.lexeme << '\n';
	}
}

int main() {
	run("g a b 12343 {}");
	return 0;
}
