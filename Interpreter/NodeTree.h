#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include "Node.h"

class Node;
enum class NodeType;

class NodeTree
{
public:
	NodeTree(Node* Parent, NodeType TypeOfNode, std::string NodeName);

private:
	Node* FirstNode;
	Node* LastNode;
	Node* ParentNode;

public:
	Node* CurrentNode;

	Node* GetParent() { return ParentNode; }

	Node* Add(NodeType TypeOfNode, std::string NodeName);
	Node* Next();
	Node* Prev();
	Node* GoToStart();
};

