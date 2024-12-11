#include "matrix.h"
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

// Конструктор по умолчанию
Matrix::Matrix() : rows(0), cols(0), data(nullptr) {}

// Конструктор с параметром
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new int* [rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

Matrix::~Matrix() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}


void Matrix::freeMemory() {
    if (data) {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}


Matrix Matrix::multiply(const Matrix& other) const {
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < other.cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}


Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[j][i] = data[i][j];
        }
    }
    return result;
}


// Перегруженная операция присваивания
Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        freeMemory();
        rows = other.rows;
        cols = other.cols;
        data = new int* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// Перегруженная операция вычитания
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Перегруженная операция сложения
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1.rows, m1.cols);
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

// Перегрузка оператора ввода для матриц
istream& operator>>(istream& is, Matrix& matrix) {
    cout << "Add matrix numbers " << matrix.rows << "x" << matrix.cols << ":" << endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            while (true) {
                int value;
                is >> value;
                if (is.fail()) {
                    is.clear(); // Сброс состояния
                    is.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
                    cout << "Invalid input, please enter a number: ";
                } else {
                    matrix.data[i][j] = value;
                    break;
                }
            }
        }
    }
    return is;
}

// Перегрузка оператора вывода для матриц
ostream& operator<<(ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

// Сохранение матрицы в текстовый файл
ofstream& operator<<(ofstream& ofs, const Matrix& matrix) {
    ofs << matrix.rows << " " << matrix.cols << endl;
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            ofs << matrix.data[i][j] << " ";
        }
        ofs << endl;
    }
    return ofs;
}


// Загрузка матрицы из текстового файла
ifstream& operator>>(ifstream& ifs, Matrix& matrix) {
    ifs >> matrix.rows >> matrix.cols;
    matrix.resize(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            ifs >> matrix.data[i][j];
        }
    }
    return ifs;
}


// Метод для сохранения матрицы в бинарный файл
void Matrix::saveToBinary(const string& filename) const {
    ofstream ofs(filename, ios::binary );
    if (ofs.is_open()) {
        ofs << *this; // Используем перегруженный оператор для записи
        ofs.close();
    }
}

// Метод для загрузки матрицы из бинарного файла
void Matrix::loadFromBinary(const string& filename) {
    ifstream ifs(filename, ios::binary);
    if (ifs.is_open()) {
        ifs >> *this; // Используем перегруженный оператор для чтения
        ifs.close();
    }
}

// Печать матрицы
void Matrix::print() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::resize(int newRows, int newCols) {
    freeMemory();
    rows = newRows;
    cols = newCols;
    data = new int*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new int[cols]();
    }
}