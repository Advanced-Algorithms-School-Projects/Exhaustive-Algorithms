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
void RKT(knapsack &k, knapsack &bestSol, int start, int numUnSelect);
void checkKnapsack(knapsack &k, knapsack &bestSol);
void softReset(knapsack &k, int currPos, int newPos);
void hardReset(knapsack &k, int numUnSelect);
void moveUnSelection(knapsack &k, int oldPos, int newPos);

int main()
{
	char x;
	ifstream fin;
	string fileName;

	// Read the name of the graph from the keyboard or
	// hard code it here for testing.

	fileName = "knapsack8.input";

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

void exhaustiveKnapsack(knapsack &k, int t) {
	//function takes a knapsack input and a time input to exhaustively determine the best combination
	//of items that maximizes the knapsach value while remaining under the cost limit

	knapsack bestSol = knapsack(k);
	int numObjects = k.getNumObjects();

	checkKnapsack(k, bestSol);

	for (int j = 1; j <= numObjects; j++) {
		int start = 0;
		hardReset(k, j);

		RKT(k, bestSol, start, j);
		system("pause");
	}

	k = knapsack(bestSol);
	system("pause");

}

void RKT(knapsack &k, knapsack &bestSol, int start, int numUnSelect) {

	int end = k.getNumObjects() - numUnSelect + start;

	cout << "RKT end: " << end << ", NumObjects: " << k.getNumObjects() << ", numUnSelect: " << numUnSelect << ", start: " << start << endl;
	system("pause");
	for (int i = start; i <= end; i++) {
		checkKnapsack(k, bestSol);
		if (i == end) {
			softReset(k, i, start + 1);
			cout << "Option 1:" << endl;
			for (int i = 0; i < k.getNumObjects(); i++) {
				cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
			}
			system("pause");
			return;
		}
		if ((i + 1) < k.getNumObjects()) {
		if (!k.isSelected(i + 1)) {
			cout << "Option 2:" << endl;
			for (int i = 0; i < k.getNumObjects(); i++) {
				cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
			}
			system("pause");
			RKT(k, bestSol, i + 1, numUnSelect);
		}
		if (k.isSelected(i + 1)) {
			moveUnSelection(k, i, i + 1);

			cout << "Option 3:" << endl;
			for (int i = 0; i < k.getNumObjects(); i++) {
				cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
			}
			system("pause");
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
	cout << "Soft Reset: " << endl;
	for (int i = 0; i < k.getNumObjects(); i++) {
		cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
	}
	system("pause");

	/*
	moveUnSelection(k, currPos, newPos);
	cout << "Soft Reset: " << endl;
	for (int i = 0; i < k.getNumObjects(); i++) {
		cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
	}
	system("pause");
	if ((currPos + 1) < k.getNumObjects()) {
		softReset(k, currPos + 1, newPos + 1);
	}*/
	return;
}

void hardReset(knapsack &k, int numUnSelect) {
	for (int i = 0; i < numUnSelect; i++) {
		k.unSelect(i);
	}
	for (int i = numUnSelect; i < k.getNumObjects(); i++) {
		k.select(i);
	}
	cout << "Hard Reset:" << endl;
	for (int i = 0; i < k.getNumObjects(); i++) {
		cout << "Object " << i << " selected: " << k.isSelected(i) << endl;
	}
	system("pause");


}

void moveUnSelection(knapsack &k, int oldPos, int newPos) {
	k.select(oldPos);
	k.unSelect(newPos);
}