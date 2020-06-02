#include "Node.h"

Node::Node()
{
	ParentNode = nullptr;
	Type = NodeType::INVALID;
	Name = "\0";
	Params = nullptr;
}

Node::Node(Node* Parent, NodeType TypeOfNode, std::string NodeName)
{
	ParentNode = Parent;
	Type = TypeOfNode;
	Name = NodeName;
	Params = nullptr;
}