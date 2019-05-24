#include "Graph.h"


Graph::Graph()
{
	edges.resize(0);
	nodes.resize(0);
}

Graph::Graph(size_t dimension)
{
	Init(dimension);
}


Graph::~Graph()
= default;

void Graph::Init(size_t dimension)
{
	nodes.resize(0);
	edges.resize(dimension);
	for (size_t i = 0; i < dimension; i++)
	{
		edges[i].resize(dimension);
	}
}

void Graph::AddNode(const Node& n)
{
	nodes.push_back(n);
	nodes[nodes.size() - 1].SetIndex(nodes.size() - 1);
}

void Graph::AddNodes(const vector<Node>& n)
{
	size_t i = nodes.size();
	nodes.insert(nodes.end(), n.begin(), n.end());
	for (; i < nodes.size(); i++)
	{
		nodes[i].SetIndex(i);
	}
}

void Graph::AddEdge(const size_t& from, const size_t& to, const int& capacity)
{
	if (from >= nodes.size() || to >= nodes.size())
	{
		throw "AddEdge: Node index out of range.";
	}
	edges[from][to].SetCapacity(capacity);
	edgeCount++;
}

void Graph::DeleteEdge(const size_t& from, const size_t& to)
{
	edges[from][to].SetCapacity(0);
	edges[from][to].SetFlow(0);
}

void Graph::SetFlow(const size_t& from, const size_t& to, const int& flow)
{
	if (from >= nodes.size() || to >= nodes.size())
	{
		throw "SetFlow: Node index out of range.";
	}
	edges[from][to].SetFlow(flow);
}

Node& Graph::GetNode(const size_t& index)
{
	if (index >= nodes.size())
	{
		throw "GetNode: Index out of range.";
	}
	return nodes[index];
}

size_t Graph::GetNodeSize() const
{
	return nodes.size();
}

size_t Graph::GetEdgeSize() const
{
	return edgeCount;
}

vector<Node>& Graph::GetAllNodes()
{
	return nodes;
}

vector<int> Graph::GetAdjacentNodes(const size_t& index) const
{
	if (index >= nodes.size())
	{
		throw "GetAdjacentNodes: index out of range.";
	}
	vector<int> ans;
	for (int i = 0; i < nodes.size(); i++)
	{
		const int cap = edges[index][i].GetCapacity();
		if (cap != 0 && cap != edges[index][i].GetFlow())
		{
			ans.push_back(i);
		}
	}
	return ans;
}

vector<int> Graph::GetAdjacentNodes(const Node& n) const
{
	return GetAdjacentNodes(n.GetIndex());
}

bool Graph::isConnected(const size_t& from, const size_t& to) const
{
	if (from >= edges.size() || to >= edges.size())
	{
		throw "isConnected: index out of range";
	}
	return edges[from][to].GetCapacity() != 0;
}

bool Graph::isMatched(const size_t& from, const size_t& to) const
{
	return edges[from][to].GetFlow() != 0;
}

void Graph::Clear()
{
	nodes.clear();
	edges.clear();
}
