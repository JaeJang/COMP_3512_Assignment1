#include "Matrix.hpp"
#include "SizeException.hpp"
#include <iomanip>
#include <iostream>

//Default Constructor
//Place holder
Matrix::Matrix() {
	row = 0;
	col = 0;
	matrix = nullptr;
}

//Constructor
//Same size of row and col
Matrix::Matrix(const int rowAndCol) 
	:row(rowAndCol), col(rowAndCol)
{
	matrix = new double[row * col];
	clear();
}

//Constructor
//Initialize a matrix with row and col
Matrix::Matrix(const int _row,const int _col)
	:row(_row), col(_col)
{
	matrix = new double[_row * _col];
	clear();
}

//Copy constructor
Matrix::Matrix(const Matrix & rhs)
{
	row = rhs.row;
	col = rhs.col;
	//matrix = rhs.matrix;
	matrix = new double[row * col];
	std::memcpy(matrix, rhs.matrix, sizeof(double) * row * col);
}

//Destructor
Matrix::~Matrix()
{
	delete[] matrix;
}

//Initialize a matrix with 0
//PRE	: memory for matrix assigned
//POST	: all elements in matrix are 0
void Matrix::clear() {
	for (int i = 0; i < row * col; ++i) {
			matrix[i] = 0;
		
	}
}

//Overloaded + operator
//PRE	: both Matrix have to have the same size
//POST	: rhs matrix is added to lhs matrix
//RETURN: current Matrix object
Matrix operator+(Matrix lhs, const Matrix & rhs)
{
	if (lhs.row != rhs.row && lhs.col != rhs.col) {
		throw SizeException{};
	}
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			lhs.matrix[i * lhs.col + j] += rhs.matrix[i * rhs.col + j];
		}
	}
	return lhs;
}

//Overloaded - operator
//PRE	: both Matrix have to have the same size
//POST	: lhs maxtrix is subtracted by rhs
//RETURN: current Matrix object
Matrix operator-(Matrix lhs, const Matrix & rhs)
{
	if (lhs.row != rhs.row && lhs.col != rhs.col) {
		throw SizeException{};
	}
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			lhs.matrix[i * lhs.col + j] -= rhs.matrix[i * rhs.col + j];
		}
	}
	return lhs;
}

//Overloaded / operator
//PRE	: should be in order of Matrix and factor
//POST	: lhs maxtrix has been divided by the factor	
//RETURN: current Matrix object
Matrix operator/(Matrix lhs, const double factor)
{
	
	lhs /= factor;
	return lhs;
}

//Overloaded / operator
//PRE	: this object should be a Matrix
//POST	: lhs maxtrix has been divided by the factor	
//RETURN: current Matrix object
Matrix & Matrix::operator/=(const double factor) 
{
	

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			matrix[i * col + j] /= factor;
		}
	}
	return *this;
}

//Overloaded *= operator
//PRE	: both objects are Matrices
//POST	: lhs Matrix has been multiplied by rhs matrix
//RETURN: new Matrix multiplied
Matrix & Matrix::operator*=(const Matrix & rhs) {
	if (col != rhs.row) {
		throw SizeException{};
	}
	Matrix temp(*this);
	col = rhs.col;
	delete[] matrix;
	matrix = new double[row * col];
	
	clear();
	int i, j, k;
	for (i = 0; i < row; ++i) {
		for (j = 0; j < col; ++j) {
			for (k = 0; k < temp.col; ++k) {
				double left = temp.matrix[i * temp.col + k];
				matrix[i * col + j] +=
				(temp.matrix[i * temp.col + k] * rhs.matrix[k * rhs.col + j]);

			}
		}
	}
	
	return *this;
}

//Overloaded * operator
//PRE	: both objects are Matrices
//POST	: lhs Matrix has been multiplied by rhs matrix
//RETURN: new Matrix multiplied
Matrix operator*(Matrix lhs, const Matrix & rhs)
{
	lhs *= rhs;
	return lhs;
}

//Overloaded * operator
//PRE	: Matrix * factor(double)
//POST	: lhs Matrix has been multiplied by the factor
//RETURN: new Matrix multiplied
Matrix operator*(Matrix lhs, const double factor)
{
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			lhs.matrix[i * lhs.col + j] *= factor;
		}
	}
	return lhs;
}

//Overloaded * operator
//PRE	: factor(double) * Matrix
//POST	: lhs Matrix has been multiplied by the factor
//RETURN: new Matrix multiplied
Matrix operator*(const double factor, Matrix lhs) 
{
	lhs = operator*(lhs, factor);
	return lhs;
}

//Overloaded == operator
//PRE	: both objects are Matrix
//POST	: NULL
//RETURN: true if all elements in matrices are same
bool operator==(const Matrix & lhs, const Matrix & rhs) 
{
	if ((lhs.row != rhs.row) || (lhs.col != rhs.col))
		return false;
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			double left = lhs.matrix[i * lhs.col + j];
			double right = rhs.matrix[i * rhs.col + j];
			if (left != right)
				return false;
		}
	}
	return true;
}

//Overloaded == operator
//PRE	: both objects are Matrix
//POST	: NULL
//RETURN: true if there is any difference in the matrices
bool operator!=(const Matrix & lhs, const Matrix & rhs) 
{
	return !operator==(lhs, rhs);
}

//Swap values between two objects
//PRE	: both are Matrix object
//POST	: swap each other
void swap(Matrix & rhs, Matrix & lhs)
{
	std::swap(rhs.row, lhs.row);
	std::swap(rhs.col, lhs.col);
	std::swap(rhs.matrix, lhs.matrix);
}

//Overloaded assignment operator
//PRE	: both are Matrix object
//POST	: lhs is overrided with rhs
Matrix & Matrix::operator=(Matrix rhs)
{
	swap(*this, rhs);
	return *this;
}

//overloaded insertion operator
//PRE    : (ostream) << (Matrix object)
//POST   : when compiler sees above, it will implement the definition
//RETURN : ostream
std::ostream& operator<<(std::ostream & out, Matrix & obj) 
{
	for (int i = 0; i < obj.row; ++i) {
		for (int j = 0; j < obj.col; ++j) {
			out << std::setprecision(3) << obj.matrix[i * obj.col + j] << "\t";
		}
		out << std::endl;
	}

	return out;
}

//Set value at specified row and column.
//PRE	: NULL
//POST	: the value has been assigned at specified index
void Matrix::setValue(int _row, int _col, double value)
{
	if (_row >= row || _col >= col) {
		throw SizeException{};
	}
	matrix[_row * col + _col] = value;
}

//Set value at specified row and column.
//PRE	: NULL
//POST	: the value has been assigned at specified index
void Matrix::setValue(int index, double value)
{
	if (index >= row * col) {
		throw SizeException{};
	}
	matrix[index] = value;
}


//Calculate the importance and modify the connectivie matrix
//Each element in each column is divided by the number 1's in the column
//If there is no 1s in a column, 1/n will be assigned
//PRE	: sum of each column is determined
//POST	: the connectivity matrix has been modified
//RETURN: modified matrix
Matrix Matrix::calculateImportance(std::vector<double> & sumOfCols)
{
	Matrix s(*this);

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (sumOfCols[j] != 0) {
				s.matrix[i * col + j] /= sumOfCols[j];
			}
			else {
				s.matrix[i * col + j] = 1.0 / s.row;
			}
				
			
		}
	}

	return s;
}

//Get a matrix Q, whose every element = 1 / n
//PRE	: NULL
//POST	: every element has same value with 1/n
//RETURN: the new matrix created
Matrix Matrix::getQMatrix()
{
	Matrix s(*this);
	s.clear();
	for (int i = 0; i < row * col; ++i) {
		s.matrix[i] = 1.0 / row;
	}

	return s;
}