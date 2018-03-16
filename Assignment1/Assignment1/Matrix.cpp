#include "Matrix.hpp"
#include "SizeException.hpp"

Matrix::Matrix(const int _row,const int _col)
	:row(_row), col(_col)
{
	matrix = new double[_row * _col];
	clear();
}

Matrix::Matrix(const Matrix & rhs)
{
	row = rhs.row;
	col = rhs.col;
	//matrix = rhs.matrix;
	matrix = new double[row * col];
	std::memcpy(matrix, rhs.matrix, sizeof(double) * row * col);
}

Matrix::~Matrix()
{
	delete[] matrix;
}

void Matrix::clear() {
	for (int i = 0; i < row * col; ++i) {
			matrix[i] = 0;
		
	}
}


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

//Matrix operator/(Matrix lhs, const Matrix & rhs)
//{
//	return Matrix();
//}

Matrix operator/(Matrix lhs, const double factor)
{
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			lhs.matrix[i * lhs.col + j] /= factor;
		}
	}
	return lhs;
}

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
				matrix[i * col + j] =
				matrix[i * col + j] +
				(temp.matrix[i * temp.col + k] * rhs.matrix[k * rhs.col + j]);

			}
		}
	}
	return *this;
}


Matrix operator*(Matrix lhs, const Matrix & rhs)
{
	//if (lhs.col != rhs.row) {
	//	throw SizeException{};
	//}
	//Matrix result(lhs);
	//lhs.col = rhs.col;
	//lhs.matrix = new double[lhs.row * lhs.col];
	//lhs.clear();
	//for (int i = 0; i < result.row; ++i) {
	//	for (int j = 0; j < result.col; ++j) {
	//			for (int k = 0; k < lhs.col; ++k)
	//			lhs.matrix[i * result.col + j] +=
	//			//result.matrix[i * result.col + j] +
	//			(result.matrix[i * result.col + k] * rhs.matrix[k * rhs.col + j]);
	//	}
	//}
	//
	////std::cout << result << std::endl;
	//return lhs;
	lhs *= rhs;
	return lhs;
}

Matrix operator*(Matrix lhs, const double factor)
{
	for (int i = 0; i < lhs.row; ++i) {
		for (int j = 0; j < lhs.col; ++j) {
			lhs.matrix[i * lhs.col + j] *= factor;
		}
	}
	return lhs;
}


void swap(Matrix & rhs, Matrix & lhs)
{
	std::swap(rhs.row, lhs.row);
	std::swap(rhs.col, lhs.col);
	std::swap(rhs.matrix, lhs.matrix);
}

Matrix & Matrix::operator=(Matrix rhs)
{
	swap(*this, rhs);
	return *this;
}

std::ostream& operator<<(std::ostream & out, Matrix & obj) 
{
	for (int i = 0; i < obj.row; ++i) {
		for (int j = 0; j < obj.col; ++j) {
			out << obj.matrix[i * obj.col + j] << "\t";
		}
		out << std::endl;
	}

	return out;
}

void Matrix::setValue(int _row, int _col, double value)
{
	if (_row >= row || _col >= col) {
		throw SizeException{};
	}
	matrix[_row * col + _col] = value;
}