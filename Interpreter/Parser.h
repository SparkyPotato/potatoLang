#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Token.h"
#include "TokenList.h"

class Parser
{
public:
	static TokenList Tokenizer(std::ifstream& FileToParse);
};