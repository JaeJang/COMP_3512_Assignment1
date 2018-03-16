#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void readFile(Matrix *);

int main() {

	Matrix *inputMatrix = nullptr;
	readFile(inputMatrix);

	cout << "Press any button to exit";
	_getche();

	return 0;
}

void readFile(Matrix * matrix) {
	ifstream in("example.txt");
	string temp;
	int element;
	bool firstLineDone = false;
	while (getline(in, temp)) {
		istringstream iss(temp);
		if (!firstLineDone) {
			vector<double> first;
			while (iss >> element) {
				first.push_back(element);
			}
			matrix = new Matrix(first.size(), first.size());

		}
	}
}