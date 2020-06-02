#pragma once
#include "Token.h"

class TokenList
{
public:
	TokenList(TokenType Type, std::string Value);

private:
	Token* ListStart;
	Token* ListEnd;

public:
	Token* CurrentToken;

	Token* Add(TokenType Type, std::string Value);
	Token* Next();
	Token* Prev();
	Token* GoToStart();
};

