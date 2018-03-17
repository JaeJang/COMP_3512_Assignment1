#pragma once
#include <iostream>

class Matrix {
private:
	int row, col;
	double * matrix;
	void clear();

public:
	
	explicit Matrix(const int rowAndCol);
	Matrix(const int _row, const int _col);
	Matrix(const Matrix & rhs);
	~Matrix();
	
	
	friend Matrix operator+(Matrix lhs, const Matrix & rhs);
	friend Matrix operator-(Matrix lhs, const Matrix & rhs);
	friend Matrix operator/(Matrix lhs, const Matrix & rhs);
	friend Matrix operator/(Matrix lhs, const double factor);
	friend Matrix operator*(Matrix lhs, const Matrix & rhs);
	friend Matrix operator*(Matrix lhs, const double factor);
	friend void swap(Matrix & rhs, Matrix & lhs);
	Matrix & operator=(Matrix rhs);
	Matrix & operator*=(const Matrix & rhs);
	friend std::ostream& operator<<(std::ostream & out, Matrix & obj);

	int getRow() const { return row; }
	int getCol() const { return col; }
	double* getMatrix() const { return matrix; }
	void setValue(int _row, int _col, double value);
	void setValue(int index, double value);
	
};