#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Parser.h"
#include "Token.h"
#include "TokenList.h"
#include "Node.h"

int main()
{
	std::cout << "Enter file directory: ";
	std::string FileDirectory;
	std::cin >> FileDirectory;
	std::ifstream InputFile;
	InputFile.open(FileDirectory);

	bool Error;
	TokenList Tokens = Parser::Tokenizer(InputFile, Error);
	if (Error)
	{
		return 1;
	}
	Tokens.GoToStart();

	do 
	{
		std::cout << Tokens.CurrentToken->Value << "\n";
		switch (Tokens.CurrentToken->Type)
		{
		case TokenType::NAME:
			std::cout << "NAME\n";
			break;
		case TokenType::OPERATOR:
			std::cout << "OPERATOR\n";
			break;
		case TokenType::NUMBER:
			std::cout << "NUMBER\n";
			break;
		case TokenType::STRING:
			std::cout << "STRING\n";
			break;
		case TokenType::NEWLINE:
			std::cout << "NEWLINE\n";
			break;
		case TokenType::BRACE:
			std::cout << "BRACE\n";
			break;
		case TokenType::PARENTHESIS:
			std::cout << "PARENTHESIS\n";
			break;
		default:
			std::cout << "Weird Token\n";
			break;
		}
	} while (Tokens.Next()->Type != TokenType::END);

	std::cout << "\nParser Output: \n\n";

	Tokens.GoToStart();

	Node* AST = Parser::ParseProgram(&Tokens, Error);

	//std::system("cls");
	std::cout << "Don't worry, that was just debug stuff\nProgram Output: \n\n";

	Executor CodeExecutor;
	if (!CodeExecutor.RunProgram(AST))
	{
		std::cout << "Fatal Error";
	}
}