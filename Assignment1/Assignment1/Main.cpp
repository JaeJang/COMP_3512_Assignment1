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
	double element;
	bool firstLineDone = false;
	int i = 0;

	while (getline(in, temp)) {
		istringstream iss(temp);
		if (!firstLineDone) {
			vector<double> first;
			while (iss >> element) {
				first.push_back(element);
			}
			matrix = new Matrix(first.size());
			for (double n : first) {
				matrix->setValue(i, n);
				++i;
			}
			firstLineDone = true;
		}
		else {
			while (iss >> element) {
				matrix->setValue(i, element);
				++i;
			}
		}
	}
	in.close();

}