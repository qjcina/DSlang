#include "Parser.h"
#include "Compiler.h"
#include "../structures/Commands.h"

Parser::Parser(std::queue<Token*> tokens)
{
	this->tokens = tokens;
}

std::string Parser::parse()
{
	while (!tokens.empty()) {
		auto token = popToken();
		handleFunction(token);
	}
	collector << "RRR";
	return collector.str();
}

Token* Parser::popToken() {
	auto token = tokens.front();
	tokens.pop();
	return token;
}

char Parser::bracketCheck(Token::ImmutableToken token) {
	if (token.type == Token::Type::Special)
		if (token.value.sVal == "(")
			return -1;
		else if (token.value.sVal == ")")
			return 1;
	return 0;
}


std::vector<Token*> Parser::collectArguments() {
	std::vector<Token*> arguments;
	while (!tokens.empty()) {
		auto token = popToken();
		if (bracketCheck(token->get()) == 1) {
			break;
		}
		if (token->get().type == Token::Type::Arythmetic) {
			auto left = arguments.back();
			arguments.pop_back();
			handleArythmetic(std::vector<Token*>{left, token, popToken()});
		}
		if (token->get().type == Token::Type::Word) {
			handleFunction(token);
		}
		arguments.push_back(token);
	}
	return arguments;
}

bool Parser::handleFunction(Token* token) {
	if (token->get().type == Token::Word) {
		auto bracket = popToken()->get();
		if (bracketCheck(bracket) != -1)
			throw MissingToken(std::string(1, '('), bracket.value.sVal);	
		handler function = handlers.at(token->get().value.sVal);
		auto arguments = collectArguments();
		(this->*function)(arguments);
	}
	else {
		return false;
	}
}

void Parser::getVariable(Token::ImmutableToken token) {
	if (token.type == Token::Variable)
		getVariable(token.value.sVal);
	else
		collector << "PUS " << std::hex << token.value.iVal << "\n";
}

void Parser::getVariable(std::string name) {
	collector << "RVM " << Compiler::hashVariable(name) << std::endl;
}

void Parser::handleArythmetic(std::vector<Token*> arguments) {
	if(arguments.size()>3)
		throw WrongDeclaration("arythmetic");
	getVariable(arguments.at(0)->get());
	getVariable(arguments.at(2)->get());
	char mark = arguments.at(1)->get().value.sVal[0];
	switch (mark) {
	case '+':
		collector << "ADD\n";
		break;
	case '-':
		collector << "SUB\n";
		break;
	case '/':
		collector << "DIV\n";
		break;
	case '*':
		collector << "MUL\n";
		break;
	}
}

void Parser::handlePrint(std::vector<Token*> arguments) {
	collector << "WSO \n";
}

void Parser::handleSet(std::vector<Token*> arguments) {
	if (arguments.size() > 1 || arguments.at(0)->get().type != Token::Type::Integer)
		throw WrongDeclaration("set");
	if (modyfingVariable) {
		collector << "PUS " << std::hex << arguments.at(0)->get().value.iVal << "\n";
	}
}

void Parser::handleInit(std::vector<Token*> arguments) {
	if (arguments.size() > 1 || arguments.at(0)->get().type != Token::Type::Variable)
		throw WrongDeclaration("init");
	modyfingVariable = true;
	int hash = Compiler::hashVariable(arguments.at(0)->get().value.sVal);
	if (tokens.front()->get().value.sVal == ".") {
		popToken();
		handleFunction(popToken());
	}
	else {
		collector << "PUS 0\n";
	}
	collector << "SVM " << hash <<"\n";
	modyfingVariable = false;
}

Parser::MissingToken::MissingToken(std::string expected, std::string found) : ParserException("Missing Token")
{
	std::stringstream builder;
	builder << "Syntax error - missing token";
	builder << " Expected: " << expected;
	builder << " Found:" << found;
	message = builder.str();
}

Parser::WrongDeclaration::WrongDeclaration(std::string functionName) : ParserException("Wrong Declaration")
{
	std::stringstream builder;
	builder << functionName << " - Wrong declaration or usage!";
	message = builder.str();
}

Parser::ParserException::ParserException(std::string runtimeMessage): std::runtime_error(runtimeMessage.c_str()) {
	message = "";
}

const char * Parser::ParserException::what() const throw()
{
	return message.c_str();
}
