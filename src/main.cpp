#include "lexer.hpp"
#include "result.hpp"
#include "token.hpp"
#include <expected>
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

std::optional<unilang::Error> run(std::string source) {
	unilang::Result<std::vector<unilang::Token>> maybeTokens = unilang::Lexer::lex(source);

	if (maybeTokens.isError()) {
		return maybeTokens.err();
	}

	std::vector<unilang::Token> tokens = maybeTokens.unwrap();
	for (const unilang::Token &token : tokens) {
		std::cout << token.type << ' ' << token.lexeme << '\n';
	}

	return std::nullopt;
}

void runPrompt() {
	while (true) {
		std::string source;

		std::cout << "> ";
		std::cin >> source;

		std::optional<unilang::Error> maybeError = run(source);
		if (maybeError.has_value()) {
			std::cerr << "\nError: " << maybeError.value().getError() << '\n';
		}
	}
}

void runFile(char *filePath) {
	std::ifstream file(filePath);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file!");
	}

	std::string source;

	while (file) {
		std::string line;
		std::getline(file, line);
		source += line;
		source += '\n';
	}

	std::optional<unilang::Error> maybeError = run(source);
	if (maybeError.has_value()) {
		maybeError.value().raise();
	}
}

int main(int argc, char **argv) {
	if (argc == 2) {
		runFile(argv[1]);
	} else {
		runPrompt();
	}
	return 0;
}
