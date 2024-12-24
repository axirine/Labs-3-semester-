#include "matrix.h"

#include <cmath>
using namespace std;

//Конструктор по умолчанию
Matrix::Matrix() : size(0), data(nullptr) {}

//Конструктор с параметром размера
Matrix::Matrix(int size) : size(size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
    }
}

//Конструктор копирования
Matrix::Matrix(const Matrix& other) : size(other.size) {
    data = new int* [size];
    for (int i = 0; i < size; i++) {
        data[i] = new int[size];
        for (int j = 0; j < size; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

//Деструктор
Matrix::~Matrix() {
    freeMemory();
}

//Освобождение памяти
void Matrix::freeMemory() {
    for (int i = 0; i < size; i++) {
        delete[] data[i];
    }
    delete[] data;
}

// Ввод матрицы
void Matrix::input() {
    cout << "Add matrix numbers " << size << "x" << size << ":" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            while (true) {
                int value;
                cin >> value;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "n/a" << endl;
                    exit(1);
                } else {
                    data[i][j] = value;
                    break;
                }
            }
        }
    }
}

//Вывод матрицы
void Matrix::output() const {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

//Операция сложения
Matrix Matrix::add(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

//Операция вычитания
Matrix Matrix::subtract(const Matrix& other) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

//Операция умножения
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

//Транспонирование матрицы
Matrix Matrix::transpose() const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

//Вычисление детерминанта
int Matrix::determinant() const {
    if (size == 1) {
        return data[0][0];
    }
    if (size == 2) {
        return (data[0][0] * data[1][1] - data[1][0] * data[0][1]);
    } else {
        int det = 0;
        for (int x = 0; x < size; x++) {
            Matrix submatrix(size - 1);
            int subi = 0;
            for (int i = 1; i < size; i++) {
                int subj = 0;
                for (int j = 0; j < size; j++) {
                    if (j == x) {
                        continue;
                    }
                    submatrix.data[subi][subj] = data[i][j];
                    subj++;
                }
                subi++;
            }
            det += (pow(-1, x) * data[0][x] * submatrix.determinant());
        }
        return det;
    }
}

//Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
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

bool Matrix::operator<(const Matrix& other) const {
    if (size != other.size) {
        return size < other.size;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return data[i][j] < other.data[i][j];
            }
        }
    }
    return false;
}