#pragma once

#include <fstream>
#include <iostream>
#include <string>

enum class VarType
{
	NUMBER,
	STRING,
	BOOLEAN,
};

class Variable
{
public:
	Variable(std::string NameToSet, std::string ValueToSet, VarType TypeToSet);

	std::string Name;
	std::string Value;
	VarType Type;

	Variable* NextVar;
	Variable* PrevVar;
};

