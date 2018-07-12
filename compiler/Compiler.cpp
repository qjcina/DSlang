//
// Created by qj on 24.05.18.
//

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Compiler.h"
#include "../structures/Commands.h"
#include "../utils/Regex.h"

void Compiler::placeholder() {
    std::ofstream file("in.ds", std::ios::binary | std::ios::out);
    file << getLine(Commands::PUS,std::vector<std::bitset<64>>{3});
    file << getLine(Commands::PUS,std::vector<std::bitset<64>>{2});
    file << getLine(Commands::ADD,std::vector<std::bitset<64>>{});
    file << getLine(Commands::DUB,std::vector<std::bitset<64>>{});
    file << getLine(Commands::JNE,std::vector<std::bitset<64>>{7, 5});
    file << getLine(Commands::RRR,std::vector<std::bitset<64>>{});
    file << getLine(Commands::PUS,std::vector<std::bitset<64>>{2});
    file << getLine(Commands::ADD,std::vector<std::bitset<64>>{});
    file << getLine(Commands::POP,std::vector<std::bitset<64>>{});
    file << getLine(Commands::RRR,std::vector<std::bitset<64>>{});
    file.close();
}

std::stringstream Compiler::fileToBytes(std::ifstream& input){
    std::string line;
    std::stringstream out;
    while (std::getline(input, line)) {
        std::cmatch matches;
        if(std::regex_match(line.c_str(), matches, labelRegex)){
            out<<matches[1]<<": "<< hashVariable(matches[1])<<std::endl;
            continue;
        }
        if(line.empty())
            continue;
        std::string readValue;
        std::stringstream lineStream(line);
        std::vector<std::string> lineValues;
        while (lineStream >> readValue) {
            lineValues.push_back(readValue);
        }
        short command = CommandsUtils::valueOf(lineValues.at(0));
        std::vector<std::bitset<64>> values;
        bool first = true;
        for(const auto &value : lineValues){
            if(first){
                first = false;
                continue;
            }

            unsigned long long data;
            if(std::regex_match(value, labelName)){
                auto copiedValue = value;
                copiedValue.pop_back();
                data = hashVariable(copiedValue);
            } else {
                std::stringstream ssValue;
                ssValue << std::hex << value;
                ssValue >> data;
            }
            values.emplace_back(data);
        }
        out << getLine((Commands) command, values).c_str();
    }
    return out;
}

void Compiler::writeLine(std::ofstream stream, std::string line) {
    stream << line;
}

std::string Compiler::getLine(Commands command, std::vector<std::bitset<64>> data) {
    std::stringstream line;
    line << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << command;
    for(auto value : data){
        line << " ";
        line << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << value.to_ulong();
    }
    line << "\n";
    return line.str();
}

unsigned long Compiler::hashVariable(std::string var) {
    unsigned long hash = 5381;
    for(auto character : var)
        hash = ((hash<<5)+hash)+character; // NOLINT
    return hash;
}

#include "Lex.h"

Compiler::Compiler(std::string filename)
{
	lex = new Lex(new std::ifstream(filename));
}
void Compiler::compile() {
	std::queue<Token*> tokens;
	try {
		tokens = lex->generateTokens();
	}
	catch (Lex::SyntaxError& e) {
		std::cout << e.what() << std::endl;
		return;
	}
	delete lex;
}
