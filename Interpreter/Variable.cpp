#include "Variable.h"

Variable::Variable(std::string NameToSet, std::string ValueToSet, VarType TypeToSet)
{
	Name = NameToSet;
	Value = ValueToSet;
	Type = TypeToSet;
	NextVar = nullptr;
	PrevVar = nullptr;
}
