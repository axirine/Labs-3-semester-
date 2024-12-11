#include "matrix.h"
#include <iostream>
using namespace std;

int main() {
    int size, choice;
    cout << "Choose option:" << endl;
    cout << "1. Matrix addition" << endl;
    cout << "2. Matrix subtraction" << endl;
    cout << "3. Matrix multiplication" << endl;
    cout << "4. Transposition" << endl;
    cout << "5. Determinant" << endl;
    cin >> choice;
    switch (choice) {
        case 1: {
            cout << "Size of square matrices: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix matrix2(size);
            matrix2.input();
            Matrix result = matrix1.add(matrix2);
            cout << "Result of addition:" << endl;
            result.output();
            break;
        }
        case 2: {
            cout << "Size of square matrices: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix matrix2(size);
            matrix2.input();
            Matrix result = matrix1.subtract(matrix2);
            cout << "Result of subtraction:" << endl;
            result.output();
            break;
        }
        case 3: {
            cout << "Size of square matrices: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix matrix2(size);
            matrix2.input();
            Matrix result = matrix1.multiply(matrix2);
            cout << "Result of mulptiply:" << endl;
            result.output();
            break;
        }
        case 4: {
            cout << "Size of square matrix: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix result = matrix1.transpose();
            cout << "Transposition result:" << endl;
            result.output();
            break;
        }
        case 5: {
            cout << "Size of square matrix: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            int det = matrix1.determinant();
            cout << "Determinant: " << det << endl;
            break;
        }
        default: {
            cout << "n/a" << endl;
            break;
        }
    }
    cout << "Number of matrix methods used: " << Matrix::method_cnt << endl;
    return 0;
}



