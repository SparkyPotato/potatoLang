#include "Executor.h"

Executor::Executor()
{
	VarManager = new VariableManager();
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
	return true;
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
	if (NodeToRun->Type == NodeType::VARIABLEDEFINE)
	{
		NodeTree* Params = NodeToRun->Params;
		Params->GoToStart();
		if (Params->CurrentNode->Type == NodeType::BOOLEAN || Params->CurrentNode->Type == NodeType::NUMBER || Params->CurrentNode->Type == NodeType::STRING || 
			Params->CurrentNode->Type == NodeType::FUNCTIONCALL || Params->CurrentNode->Type == NodeType::VARIABLEUSE)
		{
			return VarManager->Add(NodeToRun->Name, RunNode(Params->CurrentNode))->Value;
		}
		std::cout << "Illegal assignation\n";
		return "Error";
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
		if (NodeToRun->Name == "add")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			float Value = 0.f;
			do 
			{
				if (FunctionParams->CurrentNode->Type == NodeType::VARIABLEUSE || FunctionParams->CurrentNode->Type == NodeType::NUMBER || FunctionParams->CurrentNode->Type == NodeType::FUNCTIONCALL)
				{
					Value += std::stof(RunNode(FunctionParams->CurrentNode));
				}
				else if (FunctionParams->CurrentNode->Type == NodeType::STRING)
				{
					std::cout << "You cannot add strings. How about giving them as separate parameters to print?\n";
					return "Error";
				}
				else
				{
					std::cout << "Illegal Operation\n";
					return "Error";
				}
			} while (FunctionParams->Next()->Type != NodeType::INVALID);
			return std::to_string(Value);
		}
		if (NodeToRun->Name == "subtract")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			float Value = 0.f;
			if (FunctionParams->CurrentNode->Type == NodeType::VARIABLEUSE || FunctionParams->CurrentNode->Type == NodeType::NUMBER || FunctionParams->CurrentNode->Type == NodeType::FUNCTIONCALL)
			{
				Value = std::stof(RunNode(FunctionParams->CurrentNode));
				FunctionParams->Next();
				Value -= std::stof(RunNode(FunctionParams->CurrentNode));
			}
			else
			{
				std::cout << "Illegal Operation\n";
				return "Error";
			}
			if (FunctionParams->Next()->Type != NodeType::INVALID)
			{
				std::cout << "Ignoring all arguments after argument 2\n";
			}
			return std::to_string(Value);
		}
		if (NodeToRun->Name == "multiply")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			float Value = 1.f;
			do
			{
				if (FunctionParams->CurrentNode->Type == NodeType::VARIABLEUSE || FunctionParams->CurrentNode->Type == NodeType::NUMBER || FunctionParams->CurrentNode->Type == NodeType::FUNCTIONCALL)
				{
					Value *= std::stof(RunNode(FunctionParams->CurrentNode));
				}
				else
				{
					std::cout << "Illegal Operation\n";
					return "Error";
				}
			} while (FunctionParams->Next()->Type != NodeType::INVALID);
			return std::to_string(Value);
		}
		if (NodeToRun->Name == "divide")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			float Value = 0.f;
			if (FunctionParams->CurrentNode->Type == NodeType::VARIABLEUSE || FunctionParams->CurrentNode->Type == NodeType::NUMBER || FunctionParams->CurrentNode->Type == NodeType::FUNCTIONCALL)
			{
				Value = std::stof(RunNode(FunctionParams->CurrentNode));
				FunctionParams->Next();
				Value /= std::stof(RunNode(FunctionParams->CurrentNode));
			}
			else
			{
				std::cout << "Illegal Operation\n";
				return "Error";
			}
			if (FunctionParams->Next()->Type != NodeType::INVALID)
			{
				std::cout << "Ignoring all arguments after argument 2\n";
			}
			return std::to_string(Value);
		}
		if (NodeToRun->Name == "power")
		{
			NodeTree* FunctionParams = NodeToRun->Params;
			FunctionParams->GoToStart();
			float Value = 0.f;
			if (FunctionParams->CurrentNode->Type == NodeType::VARIABLEUSE || FunctionParams->CurrentNode->Type == NodeType::NUMBER || FunctionParams->CurrentNode->Type == NodeType::FUNCTIONCALL)
			{
				Value = std::stof(RunNode(FunctionParams->CurrentNode));
				int Base = Value;
				FunctionParams->Next();
				for (int i = std::stof(RunNode(FunctionParams->CurrentNode)); i != 1; i--)
				{
					Value *= Base;
				}
			}
			else
			{
				std::cout << "Illegal Operation\n";
				return "Error";
			}
			if (FunctionParams->Next()->Type != NodeType::INVALID)
			{
				std::cout << "Ignoring all arguments after argument 2\n";
			}
			return std::to_string(Value);
		}
		return "Cannot convert to string";
	}
	if (NodeToRun->Type == NodeType::VARIABLEUSE)
	{
		if (VarManager->DoesVariableExist(NodeToRun->Name))
		{
			return VarManager->FindVariable(NodeToRun->Name)->Value;
		}
		else
		{
			std::cout << "Unidentified identifier\n";
			return "Error";
		}
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
		if (DoesVariableExist(VarToAdd->Name))
		{
			FindVariable(VarToAdd->Name)->Value = VarToAdd->Value;
		}
		Variable* OldLast = LastVar;
		LastVar = VarToAdd;
		OldLast->NextVar = LastVar;
		LastVar->PrevVar = OldLast;
	}
	return LastVar;
}

Variable* VariableManager::Add(std::string NameOfVar, std::string ValueOfVar)
{
	if (FirstVar == nullptr)
	{
		FirstVar = LastVar = CurrentVar = new Variable(NameOfVar, ValueOfVar);
		FirstVar->NextVar = LastVar;
		FirstVar->PrevVar = nullptr;
		LastVar->PrevVar = FirstVar;
		LastVar->NextVar = nullptr;
	}
	else
	{
		if (DoesVariableExist(NameOfVar))
		{
			FindVariable(NameOfVar)->Value = ValueOfVar;
		}
		Variable* OldLast = LastVar;
		LastVar = new Variable(NameOfVar, ValueOfVar);
		OldLast->NextVar = LastVar;
		LastVar->PrevVar = OldLast;
	}
	return LastVar;
}

void VariableManager::Remove(std::string NameOfVar)
{
	Variable* VarToDelete = FindVariable(NameOfVar);
	VarToDelete->PrevVar->NextVar = VarToDelete->NextVar;
	VarToDelete->NextVar->PrevVar = VarToDelete->PrevVar;
	delete VarToDelete;
	CurrentVar = FirstVar;
}

Variable* VariableManager::FindVariable(std::string NameOfVar)
{
	GoToFirstVar();
	while (CurrentVar->Name != NameOfVar)
	{
		if (!Next())
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
