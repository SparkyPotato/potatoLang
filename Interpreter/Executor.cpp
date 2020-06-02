#include "Executor.h"

Executor::Executor()
{

}

bool Executor::DoesFunctionExist(std::string FunctionName)
{
	if (FunctionName == "print")
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Executor::DoesVariableExist(std::string VariableName)
{
	return false;
}
