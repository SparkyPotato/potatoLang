#pragma once

#include <fstream>
#include <iostream>
#include <string>

enum class TokenType
{
	NAME, // Anything that isn't a number or string
	OPERATOR, // +, -, /, *, >, <, =, ^
	NUMBER, // A sequence of consecutive digits
	STRING, // Anything surrounded by quotes (")
	NEWLINE, // A newline character '\n'
	BRACE, // A curly brace '{' or '}'
	PARENTHESIS, // A parenthesis '(' or ')'
	START, // Only returned when trying to go out of bounds going backwards
	END // Only returned when trying to go out of bounds going forwards
};

class Token
{
public:
	Token(TokenType TypeToSet, std::string ValueToSet);

public:
	TokenType Type;
	std::string Value;

	Token* NextToken; // Next Token in the Linked List
	Token* PrevToken; // Previous Token in the Linked List
};

