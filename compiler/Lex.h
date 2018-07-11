#pragma once
#include <istream>
#include <vector>
#include <queue>
#include "Token.h"

class Lex {
	std::istream* input;
	static constexpr char _ignoreChars[] = " \t";
	static constexpr char _acceptChars[] = "qQwWeErRtTyYuUiIoOpPaAsSdDfFgGhHjJkKlLzZxXcCvVbBnNmM_";
	static constexpr char _digitsChars[] = "1234567890.";
	static constexpr char _specialChars[] = "+-*/(){}[];\"\'";
	const std::vector<std::string> _reservedWords{ "init","set","print" };

	std::queue<Token*> tokens;
	void generateTokens();
public:
	Lex(std::istream* input);
};