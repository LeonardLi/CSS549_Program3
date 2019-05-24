#include "FordFulkerson.h"

int main()
{
	try
	{
		FordFulkerson sol("program3data.txt");
		sol.Run();
		sol.PrintResult();
		system("pause");
	}
	catch(string &e)
	{
		cout << e << endl;
	}
}