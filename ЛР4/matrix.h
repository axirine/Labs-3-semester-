#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
using namespace std;

class Matrix {
public:
    Matrix();
    Matrix(int rows, int cols);
    Matrix(const Matrix&);
    ~Matrix();
    Matrix multiply(const Matrix&) const;
    Matrix transpose() const;
    Matrix operator=(const Matrix&);
    Matrix operator-(const Matrix&) const;
    int operator()() const;
    int& operator()(int row, int column);
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend istream& operator>>(istream& is, Matrix& matrix);
    friend ostream& operator<<(ostream& os, const Matrix& matrix);
    friend ofstream& operator<<(ofstream& ofs, const Matrix& matrix);
    friend ifstream& operator>>(ifstream& ifs, Matrix& matrix);
    int* operator[](int i) const;
    void saveToBinary(const string& filename) const;
    void loadFromBinary(const string& filename);
    void print() const;
    void resize(int newRows, int newCols);
protected:
    int rows;
    int cols;
    int** data;
private:
    void freeMemory();
};

class SingleMatrix : public Matrix {
public:
    SingleMatrix() : Matrix() {}
    SingleMatrix(int rows, int cols) : Matrix(rows, cols) {}
    SingleMatrix(const SingleMatrix& other) : Matrix(other) {}
    ~SingleMatrix() {}
};

class RectangularMatrix : public Matrix {
public:
    RectangularMatrix() : Matrix() {}
    RectangularMatrix(int rows, int cols) : Matrix(rows, cols) {}
    RectangularMatrix(const SingleMatrix& other) : Matrix(other) {}
    ~RectangularMatrix() {}
};

#endif
