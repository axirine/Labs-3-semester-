#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
public:
    static int method_cnt;
    Matrix(); // Конструктор по умолчанию
    Matrix(int size); // Конструктор с параметром
    Matrix(const Matrix&); // Конструктор копирования
    ~Matrix(); // Деструктор

    void input();
    void output() const;
    Matrix add(const Matrix&) const;
    Matrix subtract(const Matrix&) const;
    Matrix multiply(const Matrix&) const;
    Matrix transpose() const;
    int determinant() const;

    Matrix& operator=(const Matrix&);

private:
    int size;
    int** data;
    void freeMemory();
};

#endif