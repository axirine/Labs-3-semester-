#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
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
    virtual void print() const;
    void resize(int newRows, int newCols);
    bool operator==(const Matrix& other) const;
protected:
    int rows;
    int cols;
    int** data;
private:
    void freeMemory();
};

class IdentityMatrix : public Matrix {
public:
    IdentityMatrix() : Matrix() {}
    IdentityMatrix(int rows, int cols) : Matrix(rows, cols) {}
    IdentityMatrix(const IdentityMatrix& other) : Matrix(other) {}
    IdentityMatrix(const Matrix& other) : Matrix(other) {}
    ~IdentityMatrix() {}
    void print() const;
};


class RectangularMatrix : public Matrix {
public:
    RectangularMatrix() : Matrix() {}
    RectangularMatrix(int rows, int cols) : Matrix(rows, cols) {}
    RectangularMatrix(const RectangularMatrix& other) : Matrix(other) {}
    RectangularMatrix(const Matrix& other) : Matrix(other) {}
    ~RectangularMatrix() {}
    void print() const;
};

class Node {
public:
    Matrix* data;
    Node* next;
    Node* prev;

    Node(Matrix* newData = nullptr) : data(newData), next(this), prev(this) {}
};

class List {
private:
    Node* head;
    int size;
public:
    List() : head(nullptr), size(0) {}
    ~List() {
        deleteList(*this);
    }
    void append(List& list, Matrix* data);
    void deleteList(List& list);
    void insertNode(List& list, int index, Matrix* newMatrix);
    void deleteNode(List& list, int index);
    void displayNode(const List& list, int index);
    void display(const List& list);
    bool isEmptyList(const List& list);
    Node* findNode(const List& list, int index);
};

class Menu_print {
public:
    void matrixTypes();
    void mathOptions();
    void listOptions();
};

#endif