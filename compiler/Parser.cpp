#include "Parser.h"
#include "Compiler.h"

Parser::Parser(std::queue<Token*> tokens)
{
	this->tokens = tokens;
}

std::stringstream Parser::parse()
{
	while (!tokens.empty()) {
		auto token = popToken();
		handleFunction(token);
	}
	return std::stringstream();
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

bool Parser::handleFunction(Token* token) {
	if (token->get().type == Token::Word) {
		auto bracket = popToken()->get();
		if (bracketCheck(bracket) != -1)
			throw MissingToken(std::string(1, '('), bracket.value.sVal);
		std::vector<Token*> arguments;
		while (!tokens.empty()) {
			auto token = popToken();
			if (bracketCheck(token->get()) == 1) {
				break;
			}
			arguments.push_back(token);
		}
		handler function = handlers.at(token->get().value.sVal);
		(this->*function)(arguments);
	}
	else {
		return false;
	}
}

void Parser::handlePrint(std::vector<Token*> arguments) {

}

void Parser::handleSet(std::vector<Token*> arguments) {
	if (arguments.size() > 1 || arguments.at(0)->get().type != Token::Type::Integer)
		throw WrongDeclaration("set");
	if (modyfingVariable) {
		collector << "PUS " << arguments.at(0)->get().value.iVal << "\n";
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
