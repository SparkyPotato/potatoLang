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

NodeTree::NodeTree(Node* Parent, NodeType TypeOfNode, std::string NodeName)
{
	ParentNode = Parent;
	FirstNode = LastNode = CurrentNode = new Node(ParentNode, TypeOfNode, NodeName);

	FirstNode->PrevNode = nullptr;
	FirstNode->NextNode = LastNode;
	LastNode->PrevNode = FirstNode;
	LastNode->NextNode = nullptr;
}

NodeTree::NodeTree(Node* Parent, Node* StartingNode)
{
	ParentNode = Parent;
	FirstNode = LastNode = CurrentNode = StartingNode;

	FirstNode->PrevNode = nullptr;
	FirstNode->NextNode = LastNode;
	LastNode->PrevNode = FirstNode;
	LastNode->NextNode = nullptr;
}

Node* NodeTree::Add(NodeType TypeOfNode, std::string NodeName)
{
	Node* OldEnd = LastNode;
	CurrentNode = new Node(ParentNode, TypeOfNode, NodeName);
	LastNode = CurrentNode;
	LastNode->PrevNode = OldEnd;
	OldEnd->NextNode = LastNode;

	return CurrentNode;
}

Node* NodeTree::Add(Node* NodeToAdd)
{
	Node* OldEnd = LastNode;
	CurrentNode = NodeToAdd;
	LastNode = CurrentNode;
	LastNode->PrevNode = OldEnd;
	OldEnd->NextNode = LastNode;

	return CurrentNode;
}

Node* NodeTree::Next()
{
	if (CurrentNode->NextNode == nullptr)
	{
		return new Node(ParentNode, NodeType::INVALID, "End");
	}
	CurrentNode = CurrentNode->NextNode;
	return CurrentNode;
}

Node* NodeTree::Prev()
{
	if (CurrentNode->PrevNode == nullptr)
	{
		return new Node(ParentNode, NodeType::INVALID, "Start");
	}
	CurrentNode = CurrentNode->PrevNode;
	return CurrentNode;
}

Node* NodeTree::GoToStart()
{
	CurrentNode = FirstNode;
	return CurrentNode;
}
