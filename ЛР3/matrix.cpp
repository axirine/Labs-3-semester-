#include "matrix.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
using namespace std;

// Конструктор по умолчанию
Matrix::Matrix() : size(0), data(nullptr) {}

// Конструктор с параметром
Matrix::Matrix(int size) : size(size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : size(other.size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
        for (int j = 0; j < size; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Деструктор
Matrix::~Matrix() {
    freeMemory();
}

// Освобождение памяти
void Matrix::freeMemory() {
    if (data) {
        for (int i = 0; i < size; i++) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

// Операция умножения
Matrix Matrix::multiply(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < size; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

// Транспонирование матрицы
Matrix Matrix::transpose() const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

// Перегруженная операция присваивания
Matrix Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        freeMemory();
        size = other.size;
        data = new int* [size];
        for (int i = 0; i < size; i++) {
            data[i] = new int[size];
            for (int j = 0; j < size; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    return *this;
}

// Перегруженная операция вычитания
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// Перегруженная операция сложения
Matrix operator+(const Matrix& m1, const Matrix& m2) {
    Matrix result(m1.size);
    for (int i = 0; i < m1.size; i++) {
        for (int j = 0; j < m1.size; j++) {
            result.data[i][j] = m1.data[i][j] + m2.data[i][j];
        }
    }
    return result;
}

// Перегрузка оператора ввода для матриц
std::istream& operator>>(std::istream& is, Matrix& matrix) {
    std::cout << "Add matrix numbers " << matrix.size << "x" << matrix.size << ":" << std::endl;
    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            while (true) {
                int value;
                is >> value;
                if (is.fail()) {
                    is.clear(); // Сброс состояния
                    is.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
                    std::cout << "Invalid input, please enter a number: ";
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
std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    os << matrix.size << std::endl; // Вывод размера матрицы
    for (int i = 0; i < matrix.size; i++) {
        for (int j = 0; j < matrix.size; j++) {
            os << matrix.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

// Сохранение матрицы в бинарный файл
std::ofstream& operator<<(std::ofstream& ofs, const Matrix& matrix) {
    ofs.write(reinterpret_cast<const char*>(&matrix.size), sizeof(matrix.size)); // Записываем размер матрицы
    for (int i = 0; i < matrix.size; ++i) {
        ofs.write(reinterpret_cast<const char*>(matrix.data[i]), matrix.size * sizeof(int)); // Записываем данные
    }
    return ofs;
}

// Загрузка матрицы из бинарного файла
std::ifstream& operator>>(std::ifstream& ifs, Matrix& matrix) {
    ifs.read(reinterpret_cast<char*>(&matrix.size), sizeof(matrix.size)); // Считываем размер матрицы
    matrix.resize(matrix.size); // Изменяем размер матрицы
    for (int i = 0; i < matrix.size; ++i) {
        ifs.read(reinterpret_cast<char*>(matrix.data[i]), matrix.size * sizeof(int)); // Считываем данные
    }
    return ifs;
}

// Метод для сохранения матрицы в бинарный файл
void Matrix::saveToBinary(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary );
    if (ofs.is_open()) {
        ofs << *this; // Используем перегруженный оператор для записи
        ofs.close();
    }
}

// Метод для загрузки матрицы из бинарного файла
void Matrix::loadFromBinary(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (ifs.is_open()) {
        ifs >> *this; // Используем перегруженный оператор для чтения
        ifs.close();
    }
}

// Печать матрицы
void Matrix::print() const {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция изменения размера матрицы
void Matrix::resize(int newSize) {
    freeMemory();
    size = newSize;
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size]();
    }
}
