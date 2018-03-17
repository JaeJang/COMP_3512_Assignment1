#include "Matrix.hpp"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Matrix * readFile(Matrix *, vector<double>*);
Matrix getResult(const Matrix & rank, const Matrix & M);

int main() {

	constexpr double P = 0.85;

	Matrix *inputMatrix = nullptr;
	vector<double> sumOfCols;
	inputMatrix = readFile(inputMatrix, &sumOfCols);
	
	
	
	Matrix S = inputMatrix->calculateImportance(sumOfCols);
	Matrix Q = inputMatrix->getQMatrix();
	cout << S << endl << endl;

	Matrix M = P * S + (1 - P) * Q;
	cout << M << endl << endl;

	Matrix rank(inputMatrix->getCol(), 1);
	for (int i = 0; i < rank.getRow(); ++i) {
		for (int j = 0; j < rank.getCol(); ++j) {
			rank.setValue(i, j, 1);
		}
	}
	
		
	rank = M * rank;
	rank = getResult(rank, M);
	cout << rank << endl << endl;
	double sum = 0;
	for (int i = 0; i < rank.getRow() * rank.getCol(); ++i) {
		sum += rank.getValue(i);
	}
	cout << sum << endl << endl;
	rank /= sum;

	cout << rank << endl;

	//Matrix a(4, 4);
	//double element = 0.2;
	//for (int i = 0; i < 4 ; ++i) {
	//	for(int j = 0; j < 4; ++j) {
	//	a.setValue(i,j, element);

	//	}
	//	element += 0.2;
	//}
	//cout << a << endl;
	//Matrix b(4, 1);
	//for (int i = 0; i < 4 ; ++i) {
	//	b.setValue(i, 1);
	//}
	//Matrix c = a * b;
	////c = c + b;
	//cout << c << endl;


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

void getResult(const Matrix & rank, const Matrix & M) {

}
