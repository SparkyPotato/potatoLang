#pragma once

#include <fstream>
#include <iostream>
#include <string>

class NodeTree;

enum class NodeType
{
	VARIABLEDEFINE,
	VARIABLEUSE,
	FUNCTIONDEFINE,
	FUNCTIONCALL,
	OPERATOR,
	STRING,
	NUMBER,
	BOOLEAN,
	INVALID
};

class Node
{
public:
	Node();
	Node(Node* Parent, NodeType TypeOfNode, std::string NodeName);

private:
	Node* ParentNode;

public:
	NodeType Type;
	std::string Name;
	NodeTree* Params;

	Node* NextNode;
	Node* PrevNode;

	NodeTree* GetParams() { return Params; }
	Node* GetParent() { return ParentNode; }
};