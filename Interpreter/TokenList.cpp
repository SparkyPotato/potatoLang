#include "TokenList.h"

TokenList::TokenList(TokenType Type, std::string Value)
{
	ListStart = ListEnd = CurrentToken = new Token(Type, Value);
	ListStart->PrevToken = nullptr;
	ListStart->NextToken = ListEnd;
	ListEnd->PrevToken = ListStart;
	ListEnd->NextToken = nullptr;
}

Token* TokenList::Add(TokenType Type, std::string Value)
{
	Token* OldEnd = ListEnd;
	CurrentToken = new Token(Type, Value);
	ListEnd = CurrentToken;
	ListEnd->PrevToken = OldEnd;
	OldEnd->NextToken = ListEnd;

	return CurrentToken;
}

Token* TokenList::Next()
{
	if (CurrentToken->NextToken == nullptr)
	{
		return new Token(TokenType::END, "\0");
	}
	CurrentToken = CurrentToken->NextToken;
	return CurrentToken;
}

Token* TokenList::Prev()
{
	if (CurrentToken->PrevToken == nullptr)
	{
		return new Token(TokenType::START, "\0");
	}
	CurrentToken = CurrentToken->PrevToken;
	return CurrentToken;
}

Token* TokenList::GoToStart()
{
	CurrentToken = ListStart;
	return CurrentToken;
}
