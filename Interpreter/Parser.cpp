#include "Parser.h"

TokenList Parser::Tokenizer(std::ifstream& FileToParse, bool& ErrorFound)
{
	ErrorFound = false;
	TokenList List(TokenType::START, "Program");
	std::string CurrentLine;
	while (std::getline(FileToParse, CurrentLine))
	{
		for (int i = 0; i < CurrentLine.length(); i++)
		{
			if ((CurrentLine[i] >= 'a' && CurrentLine[i] <= 'z') || (CurrentLine[i] >= 'A' && CurrentLine[i] <= 'Z'))
			{
				std::string String = "";
				while ((CurrentLine[i] >= 'a' && CurrentLine[i] <= 'z') || (CurrentLine[i] >= 'A' && CurrentLine[i] <= 'Z'))
				{
					if (CurrentLine[i] == '\n')
					{
						break;
					}
					std::string Character(1, CurrentLine[i]);
					String.append(Character);
					i++;
				}
				List.Add(TokenType::NAME, String);
				i--;
				continue;
			}
			if (CurrentLine[i] == '"')
			{
				std::string String = "";
				i++;
				while (CurrentLine[i] != '"')
				{
					if (CurrentLine[i] == '\n' || CurrentLine[i] == '\0')
					{
						std::cout << "Error: String never ends.\n";
						ErrorFound = true;
						return TokenList(TokenType::END, "Error");
					}
					std::string Character(1, CurrentLine[i]);
					String.append(Character);
					i++;
				}
				List.Add(TokenType::STRING, String);
				continue;
			}
			if (CurrentLine[i] >= '0' && CurrentLine[i] <= '9')
			{
				std::string String = "";
				while (CurrentLine[i] >= '0' && CurrentLine[i] <= '9')
				{
					if (CurrentLine[i] == '\n')
					{
						break;
					}
					std::string Character(1, CurrentLine[i]);
					String.append(Character);
					i++;
				}
				List.Add(TokenType::NUMBER, String);
				i--;
				continue;
			}
			if (CurrentLine[i] == ',')
			{
				List.Add(TokenType::COMMA, ",");
				i++;
			}
			if (CurrentLine[i] == ':')
			{
				List.Add(TokenType::COLON, ":");
				i++;
			}
			if ((CurrentLine[i] == '+') || (CurrentLine[i] == '-') || (CurrentLine[i] == '*') || CurrentLine[i] == '/' || CurrentLine[i] == '=' || CurrentLine[i] == '>' || CurrentLine[i] == '<' || CurrentLine[i] == '^')
			{
				std::string String;
				std::string Character(1, CurrentLine[i]);
				String.append(Character);
				List.Add(TokenType::OPERATOR, String);
				i++;
			}
		}
		List.Add(TokenType::NEWLINE, "\n");
	}
	return List;
}

Node Parser::ParseLine(Executor& CodeExecutor, TokenList List, bool& ErrorFound)
{
	Node* CurrentNode = new Node();
	ErrorFound = false;
	if (List.CurrentToken->Type == TokenType::NAME && List.CurrentToken->Value == "set")
	{
		List.Next();
		CurrentNode->Type = NodeType::VARIABLEDEFINE;
		CurrentNode->Name = List.CurrentToken->Value;
		if (List.Next()->Value == "as")
		{
			List.Next();
		}
		if (List.CurrentToken->Type == TokenType::NUMBER)
		{
			CurrentNode->Params = new NodeTree(CurrentNode, NodeType::NUMBER, List.CurrentToken->Value);
		}
		else if (List.CurrentToken->Type == TokenType::STRING)
		{
			CurrentNode->Params = new NodeTree(CurrentNode, NodeType::STRING, List.CurrentToken->Value);
		}
		else if (List.CurrentToken->Type == TokenType::NAME && (List.CurrentToken->Value == "true" || List.CurrentToken->Value == "false"))
		{
			CurrentNode->Params = new NodeTree(CurrentNode, NodeType::BOOLEAN, List.CurrentToken->Value);
		}
		else
		{
			std::cout << "Error: Illegal assignation.\n";
			ErrorFound = true;
			return Node(nullptr, NodeType::INVALID, "Error");
		}
	}
	else if (List.CurrentToken->Type == TokenType::NAME && CodeExecutor.DoesFunctionExist(List.CurrentToken->Value))
	{
		CurrentNode->Type = NodeType::FUNCTIONCALL;
		CurrentNode->Name = List.CurrentToken->Value;
		CurrentNode->Params = new NodeTree(CurrentNode, NodeType::FUNCTIONCALL, "Function");
		while (List.Next()->Type != TokenType::NEWLINE)
		{
			if (List.CurrentToken->Type == TokenType::NAME  && CodeExecutor.DoesVariableExist(List.CurrentToken->Value))
			{
				CurrentNode->Params->Add(NodeType::VARIABLEUSE, List.CurrentToken->Value);
			}
			else if (List.CurrentToken->Type == TokenType::NUMBER)
			{
				CurrentNode->Params->Add(NodeType::NUMBER, List.CurrentToken->Value);
			}
			else if (List.CurrentToken->Type == TokenType::STRING)
			{
				CurrentNode->Params->Add(NodeType::STRING, List.CurrentToken->Value);
			}
			else if (List.CurrentToken->Type == TokenType::NAME && (List.CurrentToken->Value == "true" || List.CurrentToken->Value == "false"))
			{
				CurrentNode->Params->Add(NodeType::BOOLEAN, List.CurrentToken->Value);
			}
			else
			{
				std::cout << "Error: Illegal arguments passed.\n";
				ErrorFound = true;
				return Node(nullptr, NodeType::INVALID, "Error");
			}
		}
	}
	List.Next();
	return *CurrentNode;
}
