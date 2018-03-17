#pragma once
#include <iostream>
#include <vector>

class Matrix {
private:
	int row, col;
	double * matrix;
	void clear();

public:
	
	Matrix();
	explicit Matrix(const int rowAndCol);
	Matrix(const int _row, const int _col);
	Matrix(const Matrix & rhs);
	~Matrix();
	
	
	friend Matrix operator+(Matrix lhs, const Matrix & rhs);
	friend Matrix operator-(Matrix lhs, const Matrix & rhs);
	Matrix & operator/=(const double factor);
	friend Matrix operator/(Matrix lhs, const double factor);
	friend Matrix operator*(Matrix lhs, const Matrix & rhs);
	friend Matrix operator*(Matrix lhs, const double factor);
	friend Matrix operator*(const double factor, Matrix lhs);
	friend bool operator==(const Matrix & lhs, const Matrix & rhs);
	friend bool operator!=(const Matrix & lhs, const Matrix & rhs);
	friend void swap(Matrix & rhs, Matrix & lhs);
	Matrix & operator=(Matrix rhs);
	Matrix & operator*=(const Matrix & rhs);
	friend std::ostream& operator<<(std::ostream & out, Matrix & obj);

	int getRow() const { return row; }
	int getCol() const { return col; }
	double getValue(const int row_index, const int col_index) const { return matrix[row_index * col + col_index]; }
	double getValue(const int index) const { return matrix[index]; }
	double* getMatrix() const { return matrix; }
	void setValue(int _row, int _col, double value);
	void setValue(int index, double value);
	Matrix calculateImportance(std::vector<double> & sumOfCols);
	Matrix getQMatrix();
	
};