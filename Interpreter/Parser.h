#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Token.h"
#include "TokenList.h"
#include "Node.h"
#include "Executor.h"

class Parser
{
public:
	static TokenList Tokenizer(std::ifstream& FileToParse, bool& ErrorFound); // Tokenizer or Lexer which takes the entire file and spits out a TokenList to be parsed
	
	static Node* ParseProgram(TokenList* List, bool& ErrorFound); // Parse function that parses the entire TokenList

private:
	static Node* Parse(TokenList* List, bool& ErrorFound, Node* Parent); // Recursive function - called in ParseProgram.
};