#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Variable.h"
#include "Node.h"

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

	std::string RunNode(Node* NodeToRun);

public:
	bool RunProgram(Node* ProgramNode);
};

