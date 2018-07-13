#pragma once
#include <string>
#include <vector>
class Token {
public:
	enum Type {
		Integer, Float, Variable, Special, Word, Arythmetic, Stacked
	};
private:
	const std::vector<char> arythmetic{ '+','-','*','/' };
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