#include "FordFulkerson.h"


Graph FordFulkerson::CreateResidual(Graph& raw) const
{
	Graph gf(raw.GetAllNodes().size() + 1);
	const size_t nodeCount = raw.GetNodeSize();

	const Node s("source");
	const Node t("sink");
	gf.AddNode(s);
	for (size_t i = 1; i < nodeCount; i++)
	{
		gf.AddNode(raw.GetNode(i));
	}
	gf.AddNode(t);
	for (size_t i = 1; i < nodeCount; i++)
	{
		for (size_t j = 1; j < nodeCount; j++)
		{
			if (raw.isConnected(i, j))
			{
				gf.AddEdge(i, j, 1);
				gf.AddEdge(j, i, 1);
				gf.SetFlow(j, i, 1);
			}
		}
	}
	const size_t half = (nodeCount - 1) / 2;
	for (size_t i = 1; i <= half; i++)
	{
		gf.AddEdge(0, i, 1);
		gf.AddEdge(i, 0, 1);
		gf.SetFlow(i, 0, 1);
	}
	for (size_t i = half + 1; i < nodeCount; i++)
	{
		gf.AddEdge(i, nodeCount, 1);
		gf.AddEdge(nodeCount, i, 1);
		gf.SetFlow(nodeCount, i, 1);
	}
	return gf;
}

Graph FordFulkerson::BFS(Graph residual) const
{
	Graph lg(residual.GetAllNodes().size());
	lg.AddNodes(residual.GetAllNodes());
	queue<Node> q;
	lg.GetNode(0).SetLevel(1);
	q.push(lg.GetNode(0));
	while (!q.empty())
	{
		Node temp = q.front();
		q.pop();
		const int level = temp.GetLevel();
		for (auto& index : residual.GetAdjacentNodes(temp))
		{
			Node& n = lg.GetNode(index);
			if (n.GetLevel() == 0)
			{
				n.SetLevel(level + 1);
				q.push(n);
				lg.AddEdge(temp.GetIndex(), q.back().GetIndex(), 1);
			}
		}
	}
	return lg;
}

void FordFulkerson::Augment(vector<int> path)
{
	path.pop_back(); // pop sink node
	while (path.size() > 2)
	{
		const int index = path.back();
		path.pop_back();
		raw.SetFlow(path.back(), index, 1);
	}
}

FordFulkerson::FordFulkerson(string filename)
{
	try
	{
		ifstream ifs(filename);
		if (!ifs)
		{
			throw "File " + filename + " not found";
		}
		size_t count;

		// nodes input
		ifs >> count;
		raw = Graph(count + 1); // align index to 1-based
		const Node start("s");
		raw.AddNode(start);

		for (size_t i = 0; i < count; i++)
		{
			string nodeName;
			ifs >> nodeName;
			Node temp(nodeName);
			raw.AddNode(temp);
		}

		// edges input
		ifs >> count;
		for (size_t i = 0; i < count; i++)
		{
			size_t from, to;
			ifs >> from >> to;

			raw.AddEdge(from, to, 1);
		}

		residual = CreateResidual(raw);
	}
	catch (string& e)
	{
		cout << e << endl;
	}
}

void FordFulkerson::Run()
{
	while (true)
	{
		Graph lg = BFS(residual);
		Node sink = lg.GetNode(lg.GetAllNodes().size() - 1);
		if (sink.GetLevel() == 0) // sink node cannot be reached in level graph
		{
			break;
		}
	
		int location = 0;		// source node
		vector<int> path;
		vector<int> adjNodes;
		path.push_back(0);
		while (true)
		{
			adjNodes = lg.GetAdjacentNodes(location);
			if (location == 0 && adjNodes.empty()) // not stuck at source node
			{
				break;
			}
			if (location == sink.GetIndex()) // location is sink
			{
				Augment(path);
				// update gf
				for (size_t i = 0; i < path.size() - 1; i++)
				{
					residual.SetFlow(path[i], path[i + 1], 1);
					residual.SetFlow(path[i + 1], path[i], 0);
				}

				while (path.size() > 1)
				{
					// delete edges in path from lg
					const int index = path.back();
					path.pop_back();
					lg.DeleteEdge(path.back(), index);
				}
				//path.pop_back();		//clear path
				location = 0;
			}
			else
			{
				if (adjNodes.empty())
				{
					const int index = path.back();
					path.pop_back(); // delete last edge from path
					lg.DeleteEdge(path.back(), index); // remove incoming edges
					location = path.back(); // retreat
				}
				else
				{
					location = adjNodes[0]; //advance along first available edge
					path.push_back(adjNodes[0]);
				}
			}
		}
	}
}

void FordFulkerson::PrintResult()
{
	vector<Node> nodes = raw.GetAllNodes();
	const unsigned int half = (nodes.size() - 1) / 2;
	size_t count = 0;
	for (size_t i = 1; i <= half; i++)
	{
		for (size_t j = half + 1; j < nodes.size(); j++)
		{
			if (raw.isMatched(i, j))
			{
				cout << nodes[i].GetName() << "/" << nodes[j].GetName() << endl;
				count++;
			}
		}
	}
	cout << count << " total matches" << endl;
}

FordFulkerson::~FordFulkerson()
= default;
