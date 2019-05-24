#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#include "Node.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

class FordFulkerson
{
	Graph raw, residual;

	Graph CreateResidual(Graph& raw) const;
	Graph BFS(Graph residual) const;
	void Augment(vector<int> path);
public:
	FordFulkerson(string filename);
	void Run();
	void PrintResult();
	~FordFulkerson();
};
