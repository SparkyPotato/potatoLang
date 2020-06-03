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
	Variable* Add(std::string NameOfVar, std::string ValueOfVar, VarType TypeOfVar);
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

	void TraverseParams(Node* NodeToTraverse);
	void TraverseNode(Node* NodeToTraverse);
	std::string RunNode(Node* NodeToRun);

	void OnEnterVarDefine();
	void OnExitVarDefine();

	void OnEnterVarUse();
	void OnExitVarUse();

	void OnEnterFunctionDefine();
	void OnExitFunctionDefine();

	void OnEnterFunctionCall();
	void OnExitFunctionCall();

	void OnEnterCodeBlock();
	void OnExitCodeBlock();

	void OnEnterNumber();
	void OnExitNumber();

	void OnEnterBoolean();
	void OnExitBoolean();

	void OnEnterString();
	void OnExitString();

public:
	bool RunProgram(Node* ProgramNode);
};

