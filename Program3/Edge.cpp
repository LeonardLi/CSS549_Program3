#include "Edge.h"



Edge::Edge()
{
}

Edge::Edge(int capacity)
{
	this->capacity = capacity;
}

int Edge::GetCapacity() const
{
	return capacity;
}

int Edge::GetFlow() const
{
	return flow;
}

void Edge::SetCapacity(const int& val)
{
	this->capacity = val;
}

void Edge::SetFlow(const int& val)
{
	this->flow = val;
}


Edge::~Edge()
= default;
