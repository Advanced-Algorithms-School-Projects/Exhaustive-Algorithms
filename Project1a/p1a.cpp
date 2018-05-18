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
#include "knapsack.h"

void exhaustiveKnapsack(knapsack &k, int t); //finds the best knapsack
void RKT(knapsack &k, knapsack &bestSol, int start, int numUnSelect, int unSelIndex, clock_t startT, int t);
void checkKnapsack(knapsack &k, knapsack &bestSol);
void softReset(knapsack &k, int currPos, int newPos);
void hardReset(knapsack &k, int numUnSelect);
void moveUnSelection(knapsack &k, int oldPos, int newPos);
int timer(int t);

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	fileName = "knapsack28.input";

	//cout << "Enter filename" << endl;
	//cin >> fileName;

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

		exhaustiveKnapsack(k, 600);

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

	system("pause");
}

//function takes a knapsack input and a time input to exhaustively determine the best combination
//of items that maximizes the knapsack value while remaining under the cost limit
void exhaustiveKnapsack(knapsack &k, int t) {
	clock_t startTime = clock();
	knapsack bestSol = knapsack(k);
	int numObjects = k.getNumObjects();

	checkKnapsack(k, bestSol);

	for (int j = 1; j < numObjects; j++) {
		int start = 0;
		hardReset(k, j);

		RKT(k, bestSol, start, j, 0, startTime, t);
	}

	hardReset(k, 8);
	checkKnapsack(k, bestSol);

	k = knapsack(bestSol);
	cout << "Time: " << (float)(clock() - startTime) / CLOCKS_PER_SEC << endl << "Best Solution:" << endl;
	for (int i = 0; i < k.getNumObjects(); i++) {
		cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
	}
	system("pause");
}

void RKT(knapsack &k, knapsack &bestSol, int start, int numUnSelect, int unSelIndex, clock_t startT, int t) {
	if (((float)(clock() - startT) / CLOCKS_PER_SEC) >= t) {
		return;
	}

	int end = k.getNumObjects() + unSelIndex - numUnSelect;

	for (int i = start; i <= end; i++) {
		checkKnapsack(k, bestSol);
		if (i == end) {
			softReset(k, i, start + 1);
			return;
		}
		if ((i + 1) < k.getNumObjects()) {
			if (!k.isSelected(i + 1)) {
				RKT(k, bestSol, i + 1, numUnSelect, unSelIndex + 1, startT, t);
				if (((float)(clock() - startT) / CLOCKS_PER_SEC) >= t) {
					return;
				}
			}
			if (k.isSelected(i + 1)) {
				moveUnSelection(k, i, i + 1);
			}
		}
	}
}

void checkKnapsack(knapsack &k, knapsack &bestSol) {
	if ((k.getCost() <= k.getCostLimit()) && (k.getValue() > bestSol.getValue())) {
		bestSol = knapsack(k);
	}
}

void softReset(knapsack &k, int currPos, int newPos) {
	int j = 0;
	for (int i = currPos; i < k.getNumObjects(); i++) {
		moveUnSelection(k, i, newPos + j);
		j++;
	}
	return;
}

void hardReset(knapsack &k, int numUnSelect) {
	for (int i = 0; i < numUnSelect; i++) {
		k.unSelect(i);
	}
	for (int i = numUnSelect; i < k.getNumObjects(); i++) {
		k.select(i);
	}
}

void moveUnSelection(knapsack &k, int oldPos, int newPos) {
	k.select(oldPos);
	k.unSelect(newPos);
}