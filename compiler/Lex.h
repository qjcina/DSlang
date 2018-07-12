#pragma once
#include <istream>
#include <vector>
#include <queue>
#include <stdexcept>
#include <exception>
#include <string>
#include <sstream>
#include "Token.h"

class Lex {
	std::istream* input;
	static constexpr char _ignoreChars[] = " \t";
	static constexpr char _acceptChars[] = "qQwWeErRtTyYuUiIoOpPaAsSdDfFgGhHjJkKlLzZxXcCvVbBnNmM_";
	static constexpr char _digitsChars[] = "1234567890.";
	static constexpr char _specialChars[] = "+-*/(){}[];\"\'.";
	const std::vector<std::string> _reservedWords{ "init","set","print" };

	std::queue<Token*> tokens;

	void handleToken(char token);
public:
	Lex(std::istream* input);
	std::queue<Token*> generateTokens();
	// LEX EXCEPTIONS
	class SyntaxError: public std::runtime_error {
		std::string message;
	public:
		SyntaxError(int line, std::string token);
		virtual const char* what() const throw();
	};
};