// Project 1a: Solving knapsack using exhaustive search
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <queue>
#include <vector>
#include <time.h>

using namespace std;

#include "d_except.h"
#include "d_matrix.h"
//#include "graph.h"
#include "knapsack.h"

void exhaustiveKnapsack(knapsack &k, int t); //finds the best knapsack

int main()
{
	char x;
	ifstream fin;
//	stack <int> moves;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	// fileName = "knapsack16.input";

	cout << "Enter filename" << endl;
	cin >> fileName;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		cout << "Reading knapsack instance" << endl;
		knapsack k(fin);

//		exhaustiveKnapsack(k, 600);

		cout << endl << "Best solution" << endl;
		k.printSolution();

	}

	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
	catch (rangeError &ex)
	{
		cout << ex.what() << endl; exit(1);
	}
}

void exhaustiveKnapsack(knapsack &k, int t) {
	//function takes a knapsack input and a time input to exhaustively determine the best combination
	//of items that maximizes the knapsach value while remaining under the cost limit

	int costLimit = k.getCostLimit();
	int numObjects = k.getNumObjects();

	int numUnselected = 0;

	while (numUnselected != numObjects) {

		//do some stuff



		numUnselected++;
	}


}

void checkKnapsak(knapsack &k) {
	//checks if current knapsack is best - if so updates
}