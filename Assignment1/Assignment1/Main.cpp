#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>
#include <stack>
using namespace std;

Matrix * readFile(Matrix *, vector<double>*);
void getResult( Matrix & rank, const Matrix & M);

int main() {
	constexpr double P = 0.85;

	Matrix *inputMatrix = nullptr;
	vector<double> sumOfCols;
	
	Matrix S = inputMatrix->calculateImportance(sumOfCols);
	Matrix Q = inputMatrix->getQMatrix();

	Matrix M = P * S + (1 - P) * Q;

	Matrix rank(inputMatrix->getCol(), 1);
	for (int i = 0; i < rank.getRow(); ++i) {
		for (int j = 0; j < rank.getCol(); ++j) {
			rank.setValue(i, j, 1);
		}
	}
	
		
	rank = M * rank;
	getResult(rank, M);
	double sum = 0;
	for (int i = 0; i < rank.getRow() * rank.getCol(); ++i) {
		sum += rank.getValue(i);
	}
	rank /= sum;

	cout << "PageRank:" << endl << rank << endl;

	
	ofstream out("PageRank.txt");
	out << rank;
	out.close();

	cout << "Press any button to exit";
	_getche();

	delete inputMatrix;
	return 0;
}

Matrix * readFile(Matrix * matrix, vector<double> * sumOfCols) {
	ifstream in("example.txt");

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

void getResult( Matrix & rank, const Matrix & M) 
{
	Matrix preRank(rank.getRow(), rank.getCol());
	while (preRank != rank) {
		preRank = rank;
		rank = M * rank;
	}
}
