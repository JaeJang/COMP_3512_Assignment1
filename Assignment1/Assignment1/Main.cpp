#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Matrix * readFile(Matrix *, vector<double>*);
void MarkovProcess( Matrix & rank, const Matrix & M);

int main() {
	constexpr double P = 0.85;

	
	Matrix *inputMatrix = nullptr;
	vector<double> sumOfCols;
	inputMatrix = readFile(inputMatrix, &sumOfCols);

	Matrix S = inputMatrix->calculateImportance(sumOfCols);

	Matrix Q = inputMatrix->getQMatrix();

	Matrix M = P * S + (1 - P) * Q;

	Matrix rank(inputMatrix->getCol(), 1);
	for (int i = 0; i < rank.getRow(); ++i) {
		for (int j = 0; j < rank.getCol(); ++j) {
			rank.setValue(i, j, 1);
		}
	}

	MarkovProcess(rank, M);

	cout << "PageRank:" << endl << rank << endl;

	//Save the data in a text file
	ofstream out("Rank.txt");
	if (out << rank) {
		cout << "File written successed" << endl;

	}
	out.close();

	cout << "Press any button to exit";
	_getche();

	delete inputMatrix;
	return 0;
}

//Reads file and stores the data in Matrix object
//Calculates the sum of each column
//PRE	: NULL
//POST	: matrix is allocated dynamically
//	      sum of each column is calcaulated
//RETURN: fully assigned matrix
Matrix * readFile(Matrix * matrix, vector<double> * sumOfCols) {
	string filename;
	cout << "Enter your file name: ";
	cin >> filename;

	ifstream in(filename);

	string temp;
	double element, sum = 0;
	bool firstLineDone = false;
	int i = 0, j = 0;

	while (getline(in, temp)) {
		istringstream iss(temp);
		if (!firstLineDone) {
			vector<double> first;
			while (iss >> element) {
				first.push_back(element);
				sumOfCols->push_back(element);
			}
			matrix = new Matrix(first.size());
			for (double n : first) {
				matrix->setValue(i, n);
				++i;
			}
			
			//j is now the number of columns
			j = i;
			firstLineDone = true;
		}
		else {
			while (iss >> element) {
				matrix->setValue(i, element);
				(*sumOfCols)[i % j] += element;
				++i;
			}
		}
		
	}
	in.close();
	return matrix;
}

//Markov Process
//PRE	: rank matrix is initialized and m matrix is calculated
//POST	: Markov Process is done
void MarkovProcess( Matrix & rank, const Matrix & M)
{
	Matrix preRank(rank.getRow(), rank.getCol());
	while (preRank != rank) {
		preRank = rank;
		rank = M * rank;
	}

	double sum = 0;
	for (int i = 0; i < rank.getRow() * rank.getCol(); ++i) {
		sum += rank.getValue(i);
	}
	rank /= sum;
}
