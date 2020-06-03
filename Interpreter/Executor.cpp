#include "Executor.h"

Executor::Executor()
{
	VarManager = new VariableManager();
}


void Executor::TraverseParams(Node* NodeToTraverse)
{
	if (NodeToTraverse->Params == nullptr)
	{
		return;
	}

	do 
	{
		TraverseNode(NodeToTraverse);
	} while (NodeToTraverse->Params->Next()->Type != NodeType::INVALID);
}

void Executor::TraverseNode(Node* NodeToTraverse)
{

}

void Executor::OnEnterVarDefine()
{

}

void Executor::OnExitVarDefine()
{

}

void Executor::OnEnterVarUse()
{

}

void Executor::OnExitVarUse()
{

}

void Executor::OnEnterFunctionDefine()
{

}

void Executor::OnExitFunctionDefine()
{

}

void Executor::OnEnterFunctionCall()
{

}

void Executor::OnExitFunctionCall()
{

}

void Executor::OnEnterCodeBlock()
{

}

void Executor::OnExitCodeBlock()
{

}

void Executor::OnEnterNumber()
{

}

void Executor::OnExitNumber()
{

}

void Executor::OnEnterBoolean()
{

}

void Executor::OnExitBoolean()
{

}

void Executor::OnEnterString()
{

}

void Executor::OnExitString()
{

}

bool Executor::RunProgram(Node* ProgramNode)
{
	if (ProgramNode->Type != NodeType::MAIN)
	{
		std::cout << "Program node not passed!\n";
		return false;
	}

	NodeTree* Params = ProgramNode->Params;
	if (Params == nullptr)
	{
		std::cout << "Program is empty\n";
		return false;
	}

	Params->GoToStart();
	do 
	{
		if (RunNode(Params->CurrentNode) == "Error")
		{
			return false;
		}
	} while (Params->Next()->Type != NodeType::INVALID);
}

std::string Executor::RunNode(Node* NodeToRun)
{
	if (NodeToRun->Type == NodeType::STRING)
	{
		return NodeToRun->Name;
	}
	if (NodeToRun->Type == NodeType::NUMBER)
	{
		return NodeToRun->Name;
	}
	if (NodeToRun->Type == NodeType::BOOLEAN)
	{
		return NodeToRun->Name;
	}
	if (NodeToRun->Type == NodeType::NEWLINE)
	{
		return "";
	}
	if (NodeToRun->Type == NodeType::VARIABLEUSE)
	{
		if (VarManager->DoesVariableExist(NodeToRun->Name))
		{
			return VarManager->FindVariable(NodeToRun->Name)->Value;
		}
	}
	if (NodeToRun->Type == NodeType::VARIABLEDEFINE)
	{
		NodeTree* Params = NodeToRun->Params;
		Params->GoToStart();
		if (Params->CurrentNode->Type == NodeType::BOOLEAN)
		{
			VarManager->Add(NodeToRun->Name, RunNode(Params->CurrentNode), VarType::BOOLEAN);
			return "Boolean initialized";
		}
		if (Params->CurrentNode->Type == NodeType::NUMBER)
		{
			VarManager->Add(NodeToRun->Name, RunNode(Params->CurrentNode), VarType::NUMBER);
			return "Number initialized";
		}
		if (Params->CurrentNode->Type == NodeType::STRING)
		{
			VarManager->Add(NodeToRun->Name, RunNode(Params->CurrentNode), VarType::STRING);
			return "String initialized";
		}
		std::cout << "Illegal assignation\n";
		return "Fatal Error";
	}
	if (NodeToRun->Type == NodeType::FUNCTIONCALL)
	{
		if (NodeToRun->Name == "print")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			do 
			{
				std::cout << RunNode(FunctionParams->CurrentNode);
			} while (FunctionParams->Next()->Type != NodeType::INVALID);
			std::cout << "\n";
		}
		return "Cannot convert to string";
	}

	std::cout << "Unidentified identifier\n";
	return "Error";
}

VariableManager::VariableManager()
{
	FirstVar = LastVar = CurrentVar = nullptr;
}

void VariableManager::GoToFirstVar()
{
	CurrentVar = FirstVar;
}

bool VariableManager::Next()
{
	if (CurrentVar->NextVar != nullptr)
	{
		CurrentVar = CurrentVar->NextVar;
		return true;
	}
	return false;
}

bool VariableManager::Prev()
{
	if (CurrentVar->PrevVar != nullptr)
	{
		CurrentVar = CurrentVar->PrevVar;
		return true;
	}
	return false;
}

Variable* VariableManager::Add(Variable* VarToAdd)
{
	if (FirstVar == nullptr)
	{
		FirstVar = LastVar = CurrentVar = VarToAdd;
		FirstVar->NextVar = LastVar;
		FirstVar->PrevVar = nullptr;
		LastVar->PrevVar = FirstVar;
		LastVar->NextVar = nullptr;
	}
	else
	{
		Variable* OldLast = LastVar;
		LastVar = VarToAdd;
		OldLast->NextVar = LastVar;
		LastVar->PrevVar = OldLast;
	}
	return LastVar;
}

Variable* VariableManager::Add(std::string NameOfVar, std::string ValueOfVar, VarType TypeOfVar)
{
	if (FirstVar == nullptr)
	{
		FirstVar = LastVar = CurrentVar = new Variable(NameOfVar, ValueOfVar, TypeOfVar);
		FirstVar->NextVar = LastVar;
		FirstVar->PrevVar = nullptr;
		LastVar->PrevVar = FirstVar;
		LastVar->NextVar = nullptr;
	}
	else
	{
		Variable* OldLast = LastVar;
		LastVar = new Variable(NameOfVar, ValueOfVar, TypeOfVar);
		OldLast->NextVar = LastVar;
		LastVar->PrevVar = OldLast;
	}
	return LastVar;
}

void VariableManager::Remove(std::string NameOfVar)
{
	FindVariable(NameOfVar);
	CurrentVar->PrevVar->NextVar = CurrentVar->NextVar;
	CurrentVar->NextVar->PrevVar = CurrentVar->PrevVar;
	delete CurrentVar;
	CurrentVar = FirstVar;
}

Variable* VariableManager::FindVariable(std::string NameOfVar)
{
	GoToFirstVar();
	while (CurrentVar->Name != NameOfVar)
	{
		Next();
		if (CurrentVar->NextVar == nullptr)
		{
			return nullptr;
		}
	}
	return CurrentVar;
}

bool VariableManager::DoesVariableExist(std::string NameOfVar)
{
	if (FindVariable(NameOfVar))
	{
		return true;
	}
	return false;
}
