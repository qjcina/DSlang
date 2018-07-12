#pragma once
#include <string>
class Token {
public:
	enum Type {
		Integer, Float, Variable, Special, Word, Arythmetic
	};
private:
	Type type;
	struct valuesCombined {
		std::string sVal;
		int iVal;
		double fVal;
	} values;
public:
	struct ImmutableToken {
		const Type type;
		const valuesCombined value;
		ImmutableToken(Token* token);
		ImmutableToken() = delete;
	};
	ImmutableToken get();
	Token(std::string value, Type type);
};