#pragma once
#include <string>
#include <vector>

#include "Node.h"
using namespace std;

class Edge
{
	int capacity = 0;
	int flow = 0;

public:
	Edge();
	Edge(int capacity);

	int GetCapacity() const;
	int GetFlow() const;
	void SetCapacity(const int& val);
	void SetFlow(const int& val);
	~Edge();
};
