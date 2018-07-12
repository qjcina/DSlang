#include "Lex.h"
#include <string>
#include <cctype>
#include <iostream>

std::queue<Token*> Lex::generateTokens()
{
	std::string line;
	unsigned linenumber = 0;
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
				tokens.push(new Token(std::string(1,token), Token::Type::Special));
				if (token == ';')
					break;
				offset++;
			}
			else {			
				throw SyntaxError(linenumber, std::string(1,line[tokenStart]));
			}
		} while (offset != std::string::npos);
		linenumber++;
	}
	return tokens;
}



Lex::Lex(std::istream* input)
{
	this->input = input;
}

Lex::SyntaxError::SyntaxError(int line, std::string token) : std::runtime_error("Syntax error")
{
	std::stringstream message;
	message << "Error at line " << line;
	message << ": " << token << " is not recognized word!";
	this->message = message.str();
}

const char * Lex::SyntaxError::what() const throw()
{	
	return message.c_str();
}
