#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Token.h"
#include "TokenList.h"
#include "NodeTree.h"
#include "Executor.h"

class Parser
{
public:
	static TokenList Tokenizer(std::ifstream& FileToParse, bool& ErrorFound);
	
	static Node ParseLine(Executor& CodeExecutor, TokenList List, bool& ErrorFound);
};