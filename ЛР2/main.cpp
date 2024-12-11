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
        cout << "6. Indexation" << endl;
        cout << "7. Assigment" << endl;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Size of square matrices: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix matrix2(size);
            matrix2.input();
            Matrix result = matrix1 + matrix2;
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
            Matrix result = matrix1 - matrix2;
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
            cout << "Result of multiplication:" << endl;
            result.output();
            break;
        }
        case 4: {
            cout << "Size of square matrix: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix result = matrix1.transpose();
            cout << "Result of transposition:" << endl;
            result.output();
            break;
        }
        case 5: {
            cout << "Size of square matrix: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            int det = matrix1();
            cout << "Determinant of the matrix: " << det << endl;
            break;
        }
        case 6: {
            cout << "Size of square matrix:";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            int row, column;
            cout << "Enter the row index: ";
            cin >> row;
            cout << "Enter the column index: ";
            cin >> column;
            try {
                int value = matrix1(row, column);
                cout << "Value at (" << row << ", " << column << "): " << value << endl;
                cout << "Enter new value for this element: ";
                cin >> value;
                matrix1(row, column) = value;
                cout << "Updated matrix: " << endl;
                matrix1.output();
            }
            catch (const std::out_of_range& e) {
                cout << e.what() << endl;
            }
            break;
        }
        case 7: {
            cout << "Size of square matrices: ";
            cin >> size;
            Matrix matrix1(size);
            matrix1.input();
            Matrix matrix2(size);
            matrix2 = matrix1;
            cout << "Matrix 2:" << endl;
            matrix2.output();
            break;
        }
        default:
            cout << "Invalid option" << endl;
            break;
        }

        // Вывод количества вызванных методов
        cout << "Number of matrix methods used: " << Matrix::method_cnt << endl;

        return 0;
    }
