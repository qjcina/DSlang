#include "Token.h"

Token::Token(std::string value, Type type): type(type)
{
	if (type == Type::Integer) {
		values.iVal = stoi(value);
	}
	else if (type == Type::Float) {
		values.fVal = stod(value);
	}
	else if (type == Type::Special) {
		values.sVal = value;
		if (std::find(arythmetic.begin(), arythmetic.end(), value.c_str()[0]) != arythmetic.end()) {
			this->type = Type::Arythmetic;
		}
	}
	else {
		values.sVal = value;
	}
	
}
Token::ImmutableToken Token::get() {
	return ImmutableToken(this);
}

Token::ImmutableToken::ImmutableToken(Token* token): value(token->values), type(token->type){
}
