#include "Parser.h"

TokenList Parser::Tokenizer(std::ifstream& FileToParse)
{
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
					if (CurrentLine[i] == '\n')
					{
						break;
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
		}
		List.Add(TokenType::NEWLINE, "\n");
	}
	return List;
}
