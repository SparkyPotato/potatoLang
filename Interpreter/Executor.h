#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Variable.h"
#include "Node.h"

enum class ComparatorType
{
	GREATER,  // > - Greater Than
	LESSER, // < Lesser Than
	EQUAL, // = - Equal To
	GREATEREQUAL, // >= - Greater Than or Equal To
	LESSEREQUAL, //  <= - Lesser Than or Equal To
	IGNORE // Used if a comparator is not being used
};

class VariableManager
{
public:
	VariableManager();

private:
	Variable* CurrentVar;
	Variable* FirstVar;
	Variable* LastVar;

	void GoToFirstVar();
	bool Next();
	bool Prev();

public:
	Variable* Add(Variable* VarToAdd);
	Variable* Add(std::string NameOfVar, std::string ValueOfVar);
	void Remove(std::string NameOfVar);
	Variable* FindVariable(std::string NameOfVar);
	bool DoesVariableExist(std::string NameOfVar);
};

class Executor
{
public:
	Executor();

private:
	VariableManager* VarManager;

	bool ShouldRunElse;

	std::string RunNode(Node* NodeToRun);

public:
	bool RunProgram(Node* ProgramNode);
};

