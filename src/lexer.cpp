#include "lexer.hpp"
#include "result.hpp"
#include "token.hpp"
#include <cctype>
#include <exception>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace unilang {
Result<std::vector<Token>, std::string> Lexer::lex(std::string source) {
	Lexer lexer(source);

	while (!lexer.isAtEnd()) {
		lexer.start = lexer.current;
		std::optional<Error<std::string>> err = lexer.lexNext();

		if (err.has_value()) {
			return err.value();
		}
	}

	lexer.emptyToken(EOP);
	std::cout << lexer.getTokens().size() << '\n';
	return lexer.getTokens();
}

// TODO: rewrite lexer
std::optional<Error<std::string>> Lexer::lexNext() {
	char ch = advance().unwrap();
	std::optional<Error<std::string>> maybeErr;

	switch (ch) {
		case '(':
			emptyToken(LEFT_PAREN);
			break;
		case ')':
			emptyToken(RIGHT_PAREN);
			break;
		case '[':
			emptyToken(LEFT_BRACKET);
			break;
		case ']':
			emptyToken(RIGHT_BRACKET);
			break;
		case '{':
			emptyToken(LEFT_BRACE);
			break;
		case '}':
			emptyToken(RIGHT_BRACE);
			break;
		case '-':
			emptyToken(MINUS);
			break;
		case '+':
			emptyToken(PLUS);
			break;
		case '=':
			emptyToken(EQUALS);
			break;
		case '*':
			emptyToken(STAR);
			break;
		case '/':
			emptyToken(SLASH);
			break;
		case '.':
			emptyToken(DOT);
			break;
		case ',':
			emptyToken(COMMA);
			break;
		case 't':
			emptyToken(TRUE);
			break;
		case 'f':
			emptyToken(FALSE);
			break;
		case 'b':
			emptyToken(BREAK);
			break;
		case 'p':
			emptyToken(PROCEDURE);
			break;
		case 'w':
			emptyToken(WHILE);
			break;
		case 'i':
			emptyToken(IF);
			break;
		case 'o':
			emptyToken(OTHERWISE);
			break;
		case 's':
			emptyToken(START);
			break;
		case 'e':
			emptyToken(END);
			break;
		case 'c':
			emptyToken(CONVERSELY);
			break;
		case 'a':
			emptyToken(AND);
			break;
		case 'l':
			emptyToken(LESS);
			break;
		case 'g':
			emptyToken(GREATER);
			break;
		case 'm':
			emptyToken(MATCHES);
			break;
		case 'n':
			emptyToken(NOT);
			break;
		case 'r':
			emptyToken(RETURN);
			break;
		case '"': // String stuff
			maybeErr = stringToken();
			break;
		case '\n':
			line++;
			break;
		case '\t':
			break;
		case '\r':
			break;
		case ' ':
			break;
		default:
			if (std::isalpha(ch)) {
				emptyToken(IDENTIFIER);
			} else if (std::isdigit(ch)) {
				maybeErr = numberToken();
			}

			std::string errorString = "Unknown character: ";
			errorString.push_back(ch);
			maybeErr = Error<std::string>(errorString);
	}

	if (maybeErr.has_value()) {
		return maybeErr.value();
	}

	return std::nullopt;
}

Result<char, std::string> Lexer::advance() {
	if (isAtEnd()) {
		return Error<std::string>("Attempted to advance while at the end of the string!");
	}

	return source[current++];
}

Result<char, std::string> Lexer::peek() const {
	if (current >= source.size()) {
		return Error<std::string>("Attempted to access string out of bounds!");
	}

	return source[current];
}

std::optional<Error<std::string>> Lexer::stringToken() {
	while (peek().unwrap() != '"') {
		if (isAtEnd()) {
			return Error<std::string>("String was unterminated!");
		}
		current++;
	}

	current++;

	Literal lit = source.substr(start + 1, current - 1);
	token(STRING, lit);
	return std::nullopt;
}

std::optional<Error<std::string>> Lexer::numberToken() {
	while (std::isdigit(peek().unwrap())) {
		current++;
	}

	if (peek().unwrap() == '.') {
		while (std::isdigit(peek().unwrap())) {
			current++;
		}
	}

	std::string str = source.substr(start, current);

	try {
		Literal lit = std::stod(str);
		token(NUMBER, lit);
		return std::nullopt;
	} catch (std::exception &e) {
		return Error<std::string>("Was unable to convert the number!");
	}
}

void Lexer::emptyToken(TokenType type) {
	token(type, nullptr);
}

void Lexer::token(TokenType type, Literal literal) {
	Token tok;
	tok.type = type;
	tok.lexeme = source.substr(start, current - 1);
	tok.line = line;
	tok.literal = literal;

	addToken(tok);
}

void Lexer::addToken(Token token) {
	tokens.push_back(token);
}

bool Lexer::isAtEnd() const {
	return current >= source.size() - 1;
}

std::vector<Token> Lexer::getTokens() const {
	return tokens;
}
}; //namespace unilang
