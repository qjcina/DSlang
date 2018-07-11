#include "Lex.h"
#include <string>
#include <cctype>
#include <iostream>

void Lex::generateTokens()
{
	std::string line;
	while (std::getline(*input, line)) {
		unsigned tokenStart = std::string::npos;
		unsigned offset = 0;
		do {
			tokenStart = line.find_first_not_of(_ignoreChars, offset);
			if (std::isalpha(line[tokenStart])) {
				//**********************************************************
				// When lex finds a letter it tries to find end of the word
				// Then checks for reserved words and if it is not found
				// it assumes it is a variable
				//**********************************************************
				unsigned tokenStop = line.find_first_not_of(_acceptChars, tokenStart);
				std::string token = line.substr(tokenStart, tokenStop - tokenStart);
				if (std::find(_reservedWords.begin(), _reservedWords.end(), token) != _reservedWords.end()) {
					tokens.push(new Token(token, Token::Type::Word));
				}
				else {
					tokens.push(new Token(token, Token::Type::Variable));
				}
				offset = tokenStop;
			}
			else if(std::isdigit(line[tokenStart])){
				unsigned tokenStop = line.find_first_not_of(_digitsChars, tokenStart);
				std::string token = line.substr(tokenStart, tokenStop - tokenStart);
				if (std::find(token.begin(), token.end(), '.') != token.end()) {
					tokens.push(new Token(token, Token::Type::Float));
				}
				else {
					tokens.push(new Token(token, Token::Type::Integer));
				}
				offset = tokenStop;
			}
			else if (std::find(std::begin(_specialChars), std::end(_specialChars), line[tokenStart]) != std::end(_specialChars)) {
				auto token = line[tokenStart];
				std::cout << token << " ";
				if (token == ';')
					break;
				offset++;
			}
			else {
				offset++;
			}
		} while (offset != std::string::npos);
	}
}

Lex::Lex(std::istream* input)
{
	this->input = input;
	generateTokens();
}
