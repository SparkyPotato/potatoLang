#include "Variable.h"

Variable::Variable(std::string NameToSet, std::string ValueToSet)
{
	Name = NameToSet;
	Value = ValueToSet;
	NextVar = nullptr;
	PrevVar = nullptr;
}
