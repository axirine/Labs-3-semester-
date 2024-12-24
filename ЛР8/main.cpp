#include <iostream>
#include <stack>
#include <set>
#include <random>
#include <chrono>
#include <vector>
#include "matrix.h"
#include "custom_stack.h"

using namespace std;
using namespace chrono;

// Генерация случайных матриц
vector<Matrix> generateMatrixData(mt19937& gen, int count, int size) {
    uniform_int_distribution<int> valueDist(1, 100);
    vector<Matrix> data(count);

    for (Matrix& matrix : data) {
        matrix = Matrix(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                matrix.add(Matrix(size));
            }
        }
    }
    return data;
}

// Генерация случайных чисел типа int
vector<int> generateIntData(mt19937& gen, int count) {
    uniform_int_distribution<int> dist(1, 1000);
    vector<int> data(count);
    for (int& value : data) {
        value = dist(gen);
    }
    return data;
}

// Тестирование стеков
template <typename T>
void testStacks(const string& typeName, const vector<T>& elements) {
    T newElement = elements.back();

    cout << "\nTesting Stack with type: " << typeName << "\n";

    // STL стек
    stack<T> stdStack;
    auto start = high_resolution_clock::now();
    for (const T& elem : elements) {
        stdStack.push(elem);
    }
    auto end = high_resolution_clock::now();
    cout << "[STL Stack] Time to fill: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    stdStack.push(newElement);
    end = high_resolution_clock::now();
    cout << "[STL Stack] Time to add one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    stdStack.pop();
    end = high_resolution_clock::now();
    cout << "[STL Stack] Time to remove one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    // Пользовательский стек
    CustomStack<T> customStack;
    start = high_resolution_clock::now();
    for (const T& elem : elements) {
        customStack.push(elem);
    }
    end = high_resolution_clock::now();
    cout << "[Custom Stack] Time to fill: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    customStack.push(newElement);
    end = high_resolution_clock::now();
    cout << "[Custom Stack] Time to add one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    customStack.pop();
    end = high_resolution_clock::now();
    cout << "[Custom Stack] Time to remove one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;
}

// Тестирование множества с дубликатами
template <typename T>
void testMultiset(const string& typeName, const vector<T>& elements) {
    T newElement = elements.back();

    cout << "\nTesting Multiset with type: " << typeName << "\n";

    multiset<T> stdMultiset;

    auto start = high_resolution_clock::now();
    for (const T& elem : elements) {
        stdMultiset.insert(elem);
    }
    auto end = high_resolution_clock::now();
    cout << "[Multiset] Time to fill: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    stdMultiset.insert(newElement);
    end = high_resolution_clock::now();
    cout << "[Multiset] Time to add one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    stdMultiset.erase(stdMultiset.begin());
    end = high_resolution_clock::now();
    cout << "[Multiset] Time to remove one element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;

    start = high_resolution_clock::now();
    auto it = stdMultiset.find(newElement);
    end = high_resolution_clock::now();
    cout << "[Multiset] Time to search an element: "
         << duration_cast<microseconds>(end - start).count() << " mcs" << endl;
}

int main() {
    const int initialSize = 10000;
    const int matrixSize = 3;

    mt19937 gen(42);

    // Генерация данных
    vector<int> intData = generateIntData(gen, initialSize);
    vector<Matrix> matrixData = generateMatrixData(gen, initialSize, matrixSize);

    testStacks("int", intData);
    testStacks("Matrix", matrixData);

    testMultiset("int", intData);
    testMultiset("Matrix", matrixData);

    return 0;
}

