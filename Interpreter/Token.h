#pragma once

#include <fstream>
#include <iostream>
#include <string>

enum class TokenType
{
	NAME,
	NUMBER,
	COMMA,
	STRING,
	NEWLINE,
	COLON,
	START,
	END
};

class Token
{
public:
	Token(TokenType TypeToSet, std::string ValueToSet);

public:
	TokenType Type;
	std::string Value;
	Token* NextToken;
	Token* PrevToken;
};

