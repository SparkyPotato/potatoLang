#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Variable
{
public:
	Variable(std::string NameToSet, std::string ValueToSet);

	std::string Name;
	std::string Value;

	Variable* NextVar;
	Variable* PrevVar;
};

