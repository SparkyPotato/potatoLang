#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Parser.h"
#include "Token.h"
#include "TokenList.h"
#include "Node.h"
#include "NodeTree.h"

int main()
{
	std::cout << "Enter file directory: ";
	std::string FileDirectory;
	std::cin >> FileDirectory;
	std::ifstream InputFile;
	InputFile.open(FileDirectory);

	bool Error;
	TokenList Tokens = Parser::Tokenizer(InputFile, Error);

	Tokens.GoToStart();

	Executor CodeExecutor;
	Parser::ParseLine(CodeExecutor, Tokens, Error);
	while (Tokens.Next()->Type != TokenType::END)
	{
		Parser::ParseLine(CodeExecutor, Tokens, Error);
	}
}
