#include "Parser.h"

TokenList Parser::Tokenizer(std::ifstream& FileToParse, bool& ErrorFound)
{
	ErrorFound = false;
	TokenList List(TokenType::START, "Program");
	std::string CurrentLine;
	while (std::getline(FileToParse, CurrentLine))
	{
		for (unsigned int i = 0; i < CurrentLine.length(); i++)
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
			if (CurrentLine[i] >= '0' && CurrentLine[i] <= '9' || CurrentLine[i] == '.' || CurrentLine[i] == '-')
			{
				std::string String = "";
				if (CurrentLine[i] == '-')
				{
					String = "-";
					i++;
				}
				while (CurrentLine[i] >= '0' && CurrentLine[i] <= '9' || CurrentLine[i] == '.')
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
			if (CurrentLine[i] == '{' || CurrentLine[i] == '}')
			{
				std::string String;
				std::string Character(1, CurrentLine[i]);
				String.append(Character);
				List.Add(TokenType::BRACE, String);
				continue;
			}
			if (CurrentLine[i] == '=' || CurrentLine[i] == '>' || CurrentLine[i] == '<')
			{
				std::string String;
				std::string Character(1, CurrentLine[i]);
				String.append(Character);
				List.Add(TokenType::OPERATOR, String);
				continue;
			}
			if (CurrentLine[i] == '(' || CurrentLine[i] == ')')
			{
				std::string String;
				std::string Character(1, CurrentLine[i]);
				String.append(Character);
				List.Add(TokenType::PARENTHESIS, String);
				continue;
			}
		}
		List.Add(TokenType::NEWLINE, "\n");
		List.Add(TokenType::NEWLINE, "\n");
	}
	return List;
}

Node* Parser::ParseProgram(TokenList* List, bool& ErrorFound)
{
	Node* ProgramNode = new Node(nullptr, NodeType::MAIN, "Program");
	do 
	{
		if (List->CurrentToken->Type != TokenType::NEWLINE)
		{
			if (ProgramNode->Params == nullptr)
			{
				ProgramNode->Params = new NodeTree(ProgramNode, Parse(List, ErrorFound, ProgramNode));
			}
			else
			{
				ProgramNode->Params->Add(Parse(List, ErrorFound, ProgramNode));
			}
		}
	} while (List->Next()->Type != TokenType::END);

	return ProgramNode;
}

Node* Parser::Parse(TokenList* List, bool& ErrorFound, Node* Parent)
{
	// Code Blocks
	if (List->CurrentToken->Type == TokenType::BRACE && List->CurrentToken->Value == "{")
	{
		Node* CurrentNode = new Node(Parent, NodeType::CODEBLOCK, "Block");
		std::cout << "CODEBLOCK\n";
		List->Next();
		while (List->CurrentToken->Type != TokenType::BRACE && List->CurrentToken->Value != "}")
		{
			if (List->CurrentToken->Type != TokenType::NEWLINE)
			{
				if (CurrentNode->Params == nullptr)
				{
					CurrentNode->Params = new NodeTree(CurrentNode, Parse(List, ErrorFound, CurrentNode));
				}
				else
				{
					CurrentNode->Params->Add(Parse(List, ErrorFound, CurrentNode));
				}
			}
			else
			{
				List->Next();
			}
		}
		return CurrentNode;
	}
	// Operators
	if (List->CurrentToken->Type == TokenType::OPERATOR)
	{
		Node* CurrentNode = new Node(Parent, NodeType::OPERATOR, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "OPERATOR\n";
		List->Next();
		return CurrentNode;
	}
	// Numbers
	if (List->CurrentToken->Type == TokenType::NUMBER)
	{
		Node* CurrentNode = new Node(Parent, NodeType::NUMBER, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "NUMBER\n";
		List->Next();
		return CurrentNode;
	}
	// Strings
	if (List->CurrentToken->Type == TokenType::STRING)
	{
		Node* CurrentNode = new Node(Parent, NodeType::STRING, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "STRING\n";
		List->Next();
		return CurrentNode;
	}
	// Booleans
	if (List->CurrentToken->Type == TokenType::NAME && (List->CurrentToken->Value == "true" || List->CurrentToken->Value == "false"))
	{
		Node* CurrentNode = new Node(Parent, NodeType::BOOLEAN, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "BOOLEAN\n";
		List->Next();
		return CurrentNode;
	}
	// Function Calls
	if (List->CurrentToken->Type == TokenType::NAME && List->GetNext()->Type == TokenType::PARENTHESIS && List->GetNext()->Value == "(")
	{
		Node* CurrentNode = new Node(Parent, NodeType::FUNCTIONCALL, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "FUNCTIONCALL\n";
		List->Next();
		List->Next();
		while (List->CurrentToken->Type != TokenType::PARENTHESIS && List->CurrentToken->Value != ")" /*&& List->CurrentToken->Type != TokenType::NEWLINE && List->CurrentToken->Value != "\n"*/)
		{
			if (CurrentNode->Params == nullptr)
			{
				CurrentNode->Params = new NodeTree(CurrentNode, Parse(List, ErrorFound, CurrentNode));
			}
			else
			{
				CurrentNode->Params->Add(Parse(List, ErrorFound, CurrentNode));
			}
		}
		List->Next();
		return CurrentNode;
	}
	// Variable Assignation
	if (List->CurrentToken->Type == TokenType::NAME && List->CurrentToken->Value == "set")
	{
		List->Next();
		Node* CurrentNode = new Node(Parent, NodeType::VARIABLEDEFINE, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "VARIABLEDEFINE\n";
		List->Next();
		if (List->CurrentToken->Type == TokenType::NAME && List->CurrentToken->Value == "as")
		{
			List->Next();
		}
		CurrentNode->Params = new NodeTree(CurrentNode, Parse(List, ErrorFound, CurrentNode));
		return CurrentNode;
	}
	// Function Definition
	if (List->CurrentToken->Type == TokenType::NAME && List->CurrentToken->Value == "learn")
	{
		List->Next();
		Node* CurrentNode = new Node(Parent, NodeType::FUNCTIONDEFINE, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "FUNCTIONDEFINE\n";
		List->Next();
		List->Next();
		while (List->CurrentToken->Type != TokenType::PARENTHESIS && List->CurrentToken->Value != ")")
		{
			if (CurrentNode->Params == nullptr)
			{
				CurrentNode->Params = new NodeTree(CurrentNode, Parse(List, ErrorFound, CurrentNode));
			}
			else
			{
				CurrentNode->Params->Add(Parse(List, ErrorFound, CurrentNode));
			}
		}
		List->Next();
		return CurrentNode;
	}
	// Variable Usage
	if (List->CurrentToken->Type == TokenType::NAME)
	{
		Node* CurrentNode = new Node(Parent, NodeType::VARIABLEUSE, List->CurrentToken->Value);
		std::cout << List->CurrentToken->Value << "\n";
		std::cout << "VARIABLEUSE\n";
		List->Next();
		return CurrentNode;
	}

	std::cout << "Error parsing: " << List->CurrentToken->Value << "\n";
	ErrorFound = true;
	List->Next();
	return new Node(Parent, NodeType::INVALID, "\0");
}