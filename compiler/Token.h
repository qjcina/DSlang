#pragma once
#include <string>
class Token {
public:
	enum Type {
		Integer, Float, Variable, LBracket, RBracket, LBrace, RBrace, Word, Arythmetic
	};
private:
	Type type;
	std::string value;
public:
	Token(std::string value,Type type);
};