#pragma once
#include <vector>
#include <string>


#include "Node.h"
#include "Edge.h"

using namespace std;

class Graph
{
	vector<Node> nodes;
	vector<vector<Edge>> edges; //adjacent matrix
	size_t edgeCount = 0;

	//vector<vector<int>>residualMat;	//residual
public:
	Graph();
	Graph(size_t dimension);
	~Graph();
	void Init(size_t dimension);
	void AddNode(const Node& n);
	void AddNodes(const vector<Node>& n);
	void AddEdge(const size_t& from, const size_t& to, const int& capacity);

	void DeleteEdge(const size_t& from, const size_t& to);
	void SetFlow(const size_t& from, const size_t& to, const int& flow);

	Node& GetNode(const size_t& index);
	size_t GetNodeSize() const;
	size_t GetEdgeSize() const;

	vector<Node>& GetAllNodes();

	vector<int> GetAdjacentNodes(const size_t& index) const;
	vector<int> GetAdjacentNodes(const Node& n) const;


	bool isConnected(const size_t& from, const size_t& to) const;
	bool isMatched(const size_t& from, const size_t& to) const;

	void Clear();
};
