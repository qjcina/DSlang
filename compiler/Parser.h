#pragma once
#include "Token.h"
#include <queue>
#include <string>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <map>
#include <tuple>

class Parser {
	typedef void(Parser::*handler)(std::vector<Token*>);

	std::vector<Token*> nullV;

	std::queue<Token*> tokens;
	std::stringstream collector;

	Token * popToken();
	const std::map<std::string, handler> handlers =
	{
		{std::string("init"), &Parser::handleInit},
		{std::string("set"), &Parser::handleSet},
		{std::string("print"), &Parser::handlePrint}
	};
	bool handleFunction(Token * token);
	char Parser::bracketCheck(Token::ImmutableToken token);

	// init() function handler
	bool modyfingVariable = false;
	void handleInit(std::vector<Token*> arguments);
	// set() function
	void handleSet(std::vector<Token*> arguments);
	// print() function
	void handlePrint(std::vector<Token*> arguments);

public:
	Parser(std::queue<Token*> tokens);
	std::stringstream parse();

	// Parser exceptions
	class ParserException : public std::runtime_error {
	protected:
		std::string message;
	public:
		ParserException(std::string runtimeMessage);
		virtual const char* what() const throw();
	};
	class MissingToken : public ParserException {
	public:
		MissingToken(std::string expected, std::string found);
	};
	class WrongDeclaration : public ParserException {
	public:
		WrongDeclaration(std::string functionName);
	};

};