#pragma once

#include <fstream>
#include <iostream>
#include <string>

class NodeTree;

enum class NodeType
{
	MAIN, // Main program node
	VARIABLEDEFINE, // Defining a variable
	VARIABLEUSE, // Using a variable
	FUNCTIONDEFINE, // Defining a function
	FUNCTIONCALL, // Calling a function - anything which follow the format - <name>(<argument-list>)
	OPERATOR, // Operator node - read TokenType::OPERATOR
	STRING, // String literal
	NUMBER, // Number literal
	BOOLEAN, // Boolean literal
	CODEBLOCK, // A code block in a function
	NEWLINE,
	INVALID // Invalid type, has no use in a working AST
};

class Node
{
public:
	Node();
	Node(Node* Parent, NodeType TypeOfNode, std::string NodeName);

	Node* ParentNode;

	NodeType Type;
	std::string Name;
	NodeTree* Params;

	Node* NextNode;
	Node* PrevNode;

	Node* GetParent() { return ParentNode; }
};

class NodeTree
{
public:
	NodeTree(Node* Parent, NodeType TypeOfNode, std::string NodeName);
	NodeTree(Node* Parent, Node* StartingNode);

private:
	Node* FirstNode;
	Node* LastNode;
	Node* ParentNode;

public:
	Node* CurrentNode;

	Node* GetParent() { return ParentNode; }

	Node* Add(NodeType TypeOfNode, std::string NodeName);
	Node* Add(Node* NodeToAdd);
	Node* Next();
	Node* Prev();
	Node* GoToStart();
};