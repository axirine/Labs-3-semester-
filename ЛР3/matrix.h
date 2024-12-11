#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
using namespace std;

class Matrix {
public:
    Matrix();
    Matrix(int size);
    Matrix(const Matrix&);
    ~Matrix();
    void input();
    void output() const;
    Matrix multiply(const Matrix&) const;
    Matrix transpose() const;
    int determinant() const;
    Matrix operator=(const Matrix&);
    Matrix operator-(const Matrix&) const;
    int operator()() const;
    int& operator()(int row, int column);

    // Объявления перегруженных операторов
    friend Matrix operator+(const Matrix&, const Matrix&);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

    // Перегруженные операторы для файлов
    friend std::ofstream& operator<<(std::ofstream& ofs, const Matrix& matrix);
    friend std::ifstream& operator>>(std::ifstream& ifs, Matrix& matrix);

    int getSize() const;
    void resize(int newSize);
    int* operator[](int i) const;
    void saveToBinary(const std::string& filename) const;
    void loadFromBinary(const std::string& filename);
    void print() const;

private:
    int size;
    int** data;
    void freeMemory();
};

#endif
