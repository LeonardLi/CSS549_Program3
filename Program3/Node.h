#pragma once
#include <string>
#include <vector>


using namespace std;

class Node
{
	int index = 0;
	string name;
	int level = 0;
public:
	Node();
	Node(string name);

	int GetIndex()const;
	string GetName()const;
	int GetLevel()const;

	void SetIndex(int index);
	void SetLevel(int level);
	~Node();
};

