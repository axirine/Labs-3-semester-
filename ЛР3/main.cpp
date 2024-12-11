#include "matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    Matrix result;
    bool is_result_stored = false;

    while (true) {
        int choice;
        cout << "Choose option:" << endl;
        cout << "1. Matrix addition" << endl;
        cout << "2. Matrix subtraction" << endl;
        cout << "3. Matrix multiplication" << endl;
        cout << "4. Transposition" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Load from file" << endl;
        cout << "7. Save to bin file" << endl;
        cout << "8. Load from bin file" << endl;
        cout << "0. Exit" << endl;
        cin >> choice;

        if (choice == 0) {
            break;
        }

        int size;
        switch (choice) {
            case 1: { // Сложение матриц
                cout << "Size of square matrices: ";
                cin >> size;
                Matrix matrix1(size), matrix2(size);
                cin >> matrix1 >> matrix2;
                result = matrix1 + matrix2;
                cout << "Result of addition:" << endl << result;
                is_result_stored = true; // Результат сохранен
                break;
            }

            case 2: { // Вычитание матриц
                cout << "Size of square matrices: ";
                cin >> size;
                Matrix matrix1(size), matrix2(size);
                cin >> matrix1 >> matrix2;
                result = matrix1 - matrix2;
                cout << "Result of subtraction:" << endl << result;
                is_result_stored = true;
                break;
            }

            case 3: { // Умножение матриц
                cout << "Size of square matrices: ";
                cin >> size;
                Matrix matrix1(size), matrix2(size);
                cin >> matrix1 >> matrix2;
                result = matrix1.multiply(matrix2);
                cout << "Result of multiplication:" << endl << result;
                is_result_stored = true;
                break;
            }

            case 4: { // Транспонирование матрицы
                cout << "Size of square matrix: ";
                cin >> size;
                Matrix matrix1(size);
                cin >> matrix1;
                result = matrix1.transpose();
                cout << "Result of transposition:" << endl << result;
                is_result_stored = true;
                break;
            }
            case 5: { // Сохранение результата в файл
                if (is_result_stored) {
                    ofstream ofs("matrix.txt");
                    ofs << result;
                    ofs.close();
                    cout << "Result saved to file." << endl;
                } else {
                    cout << "No result to save!" << endl;
                }
                break;
            }
            case 6: { // Загрузка матрицы из файла
                ifstream ifs("matrix.txt");
                if (ifs.is_open()) {
                    ifs >> result;
                    cout << "Matrix loaded from file: " << result << endl;
                    is_result_stored = true;
                    ifs.close();
                } else {
                    cout << "Unable to open file" << endl;
                }
                break;
            }
            case 7: { // Сохранение результата в бинарный файл
                if (is_result_stored) {
                    result.saveToBinary("matrix.bin");
                } else {
                    cout << "No result to save!" << endl;
                }
                break;
            }

            case 8: { // Загрузка матрицы из бинарного файла
                result.loadFromBinary("matrix.bin");
                is_result_stored = true;
                result.print();
                break;
            }
            default:
                cout << "Invalid option, try again." << endl;
                break;
        }
    }

    return 0;
}
