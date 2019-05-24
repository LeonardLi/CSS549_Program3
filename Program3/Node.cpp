#include "Node.h"


Node::Node()
{
}

Node::Node(string name)
{
	this->name = name;
}

int Node::GetIndex() const
{
	return index;
}

string Node::GetName() const
{
	return name;
}

int Node::GetLevel() const
{
	return level;
}

void Node::SetIndex(int index)
{
	this->index = index;
}

void Node::SetLevel(int level)
{
	this->level = level;
}


Node::~Node()
= default;
