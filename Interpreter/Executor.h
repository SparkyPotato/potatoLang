#pragma once

#include <fstream>
#include <iostream>
#include <string>

class Executor
{
public:
	Executor();

private:

public:
	bool DoesFunctionExist(std::string FunctionName);
	bool DoesVariableExist(std::string VariableName);
};

