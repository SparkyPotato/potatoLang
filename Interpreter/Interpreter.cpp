#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Parser.h"
#include "TokenList.h"
#include "Token.h"

int main()
{
	std::cout << "Enter file directory: ";
	std::string FileDirectory;
	std::cin >> FileDirectory;
	std::ifstream InputFile;
	InputFile.open(FileDirectory);

	TokenList Tokens = Parser::Tokenizer(InputFile);
	Tokens.GoToStart();
	
}
