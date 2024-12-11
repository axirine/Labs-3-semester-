#include "matrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int ListLen;
    cout << "Enter length of list:";
    cin >> ListLen;
    if (ListLen <= 0) {
        cout << "Invalid list size \n";
        return 1;
    }
    Menu_print menu;
    List list;
    Node* head;
    for (int i = 0; i < ListLen; i++) {
        Matrix* result;
        int NodesMade = 0;
        while (1) {
            int MatrixType;
            bool is_result_stored = false;
            menu.matrixTypes();
            while (1) {
                cin >> MatrixType;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input" << endl;
                } else {
                    break;
                }
            }
            if (MatrixType == 1) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    cin >> choice;
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:";
                            while (1) {
                                cin >> rows >> cols;
                                if (rows == cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are not equal. Enter it again." << endl;
                                }
                            }
                            Matrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            result = new Matrix(matrix1 + matrix2);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 2) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            while (1) {
                                cin >> rows >> cols;
                                if (rows == cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are not equal. Enter it again." << endl;
                                }
                            }
                            Matrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            result = new Matrix(matrix1 - matrix2);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 3) {
                        if (is_result_stored == false) {
                            int rows1, cols1, rows2, cols2;
                            cout << "Size of first matrix: " << endl;
                            while (1) {
                                cin >> rows1 >> cols1;
                                if (rows1 == cols1) {
                                    break;
                                } else {
                                    cout << "Rows and cols are not equal. Enter it again." << endl;
                                }
                            }
                            Matrix matrix1(rows1, cols1);
                            cout << "Size of second matrix: " << endl;
                            while (1) {
                                cin >> rows2 >> cols2;
                                if (rows2 == cols2) {
                                    break;
                                } else {
                                    cout << "Rows and cols are not equal. Enter it again." << endl;
                                }
                            }
                            Matrix matrix2(rows2, cols2);
                            if (cols1 != rows2) {
                                cout << "Matrices can't be multiplied" << endl;
                                break;
                            }
                            cin >> matrix1 >> matrix2;
                            result = new Matrix(matrix1.multiply(matrix2));
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 4) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Size of matrix: ";
                            while (1) {
                                cin >> rows >> cols;
                                if (rows == cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are not equal. Enter it again." << endl;
                                }
                            }
                            Matrix matrix1(rows, cols);
                            cin >> matrix1;
                            result = new Matrix(matrix1.transpose());
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            ofstream ofs("matrix.txt");
                            ofs << *result;
                            ofs.close();
                            cout << "Result saved to file." << endl;
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        ifstream ifs("matrix.txt");
                        if (ifs.is_open()) {
                            ifs >> *result;
                            cout << "Matrix loaded from file: " << "\n" << *result << endl;
                            is_result_stored = true;
                            ifs.close();
                        } else {
                            cout << "Unable to open file" << endl;
                        }
                    }
                    if (choice == 7) {
                        if (is_result_stored) {
                            result->saveToBinary("matrix.bin");
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 8) {
                        result->loadFromBinary("matrix.bin");
                        is_result_stored = true;
                        result->print();
                    }
                }
            } else if (MatrixType == 2) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    cin >> choice;
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        if (is_result_stored == false) {
                            int rows = 1;
                            int cols = 1;
                            IdentityMatrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1 + matrix2;
                            result = new IdentityMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 2) {
                        if (is_result_stored == false) {
                            int rows = 1;
                            int cols = 1;
                            IdentityMatrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1 - matrix2;
                            result = new IdentityMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 3) {
                        if (is_result_stored == false) {
                            int rows1 = 1;
                            int cols1 = 1;
                            int rows2 = 1;
                            int cols2 = 1;
                            IdentityMatrix matrix1(rows1, cols1);
                            IdentityMatrix matrix2(rows2, cols2);
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1.multiply(matrix2);
                            result = new IdentityMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 4) {
                        if (is_result_stored == false) {
                            int rows = 1;
                            int cols = 1;
                            IdentityMatrix matrix1(rows, cols);
                            cin >> matrix1;
                            Matrix temp = matrix1.transpose();
                            result = new IdentityMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            ofstream ofs("matrix.txt");
                            ofs << *result;
                            ofs.close();
                            cout << "Result saved to file." << endl;
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        ifstream ifs("matrix.txt");
                        if (ifs.is_open()) {
                            ifs >> *result;
                            cout << "Matrix loaded from file: " << "\n" << *result << endl;
                            is_result_stored = true;
                            ifs.close();
                        } else {
                            cout << "Unable to open file" << endl;
                        }
                    }
                    if (choice == 7) {
                        if (is_result_stored) {
                            result->saveToBinary("matrix.bin");
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 8) {
                        result->loadFromBinary("matrix.bin");
                        is_result_stored = true;
                        result->print();
                    }
                }
            } else if (MatrixType == 3) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    cin >> choice;
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            while (1) {
                                cin >> rows >> cols;
                                if (rows != cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are equal. Enter it again." << endl;
                                }
                            }
                            RectangularMatrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1 + matrix2;
                            result = new RectangularMatrix(temp);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 2) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            while (1) {
                                cin >> rows >> cols;
                                if (rows != cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are equal. Enter it again." << endl;
                                }
                            }
                            RectangularMatrix matrix1(rows, cols), matrix2(rows, cols);
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1 - matrix2;
                            result = new RectangularMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 3) {
                        if (is_result_stored == false) {
                            int rows1, cols1, rows2, cols2;
                            cout << "Size of first matrix: ";
                            while (1) {
                                cin >> rows1 >> cols1;
                                if (rows1 != cols1) {
                                    break;
                                } else {
                                    cout << "Rows and cols are equal. Enter it again." << endl;
                                }
                            }
                            RectangularMatrix matrix1(rows1, cols1);
                            cout << "Size of second matrix: ";
                            while (1) {
                                cin >> rows2 >> cols2;
                                if (rows2 != cols2) {
                                    break;
                                } else {
                                    cout << "Rows and cols are equal. Enter it again." << endl;
                                }
                            }
                            RectangularMatrix matrix2(rows2, cols2);
                            if (cols1 != rows2) {
                                cout << "Matrices can't be multiplied" << endl;
                                break;
                            }
                            cin >> matrix1 >> matrix2;
                            Matrix temp = matrix1.multiply(matrix2);
                            result = new RectangularMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 4) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Size of matrix: ";
                            while (1) {
                                cin >> rows >> cols;
                                if (rows != cols) {
                                    break;
                                } else {
                                    cout << "Rows and cols are equal. Enter it again." << endl;
                                }
                            }
                            RectangularMatrix matrix1(rows, cols);
                            cin >> matrix1;
                            Matrix temp = matrix1.transpose();
                            result = new RectangularMatrix(temp);
                            list.append(list, result);
                            NodesMade++;
                            is_result_stored = true;
                            cout << "Matrix added to the list." << endl;
                            list.display(list);
                        } else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            ofstream ofs("matrix.txt");
                            ofs << *result;
                            ofs.close();
                            cout << "Result saved to file." << endl;
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        ifstream ifs("matrix.txt");
                        if (ifs.is_open()) {
                            ifs >> *result;
                            cout << "Matrix loaded from file: " << "\n" << *result << endl;
                            is_result_stored = true;
                            ifs.close();
                        } else {
                            cout << "Unable to open file" << endl;
                        }
                    }
                    if (choice == 7) {
                        if (is_result_stored) {
                            result->saveToBinary("matrix.bin");
                        } else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 8) {
                        result->loadFromBinary("matrix.bin");
                        is_result_stored = true;
                        result->print();
                    }
                }
            } else if (MatrixType == 0) {
                break;
            }
            else {
                cout << "Invalid choice. Try again." << endl;
            }
            if (NodesMade >= ListLen) {
                break;
            }
        }
    }
    cout << "List of matrices:" << endl;
    list.display(list);
    int choice;
    do {
        menu.listOptions();
        cin >> choice;
        switch (choice) {
            case 0: {
                break;
            }
            case 1: {
                list.deleteList(list);
                cout << "List deleted." << endl;
                break;
            }
            case 2: {
                int index, rows, cols;
                cout << "Enter index of the node to place:" << endl;
                cin >> index;
                cout << "Enter the number of rows and columns:" << endl;
                cin >> rows >> cols;
                if (rows <= 0 || cols <= 0) {
                    cout << "Invalid matrix dimensions. Rows and columns must be greater than zero." << endl;
                    break;
                }
                Matrix* newMatrix = new Matrix(rows, cols);
                cout << "Enter new matrix data:" << endl;
                cin >> *newMatrix;
                list.insertNode(list, index, newMatrix);
                cout << "Node placed." << endl;
                list.display(list);
                break;
            }
            case 3: {
                int index1;
                cout << "Enter index of the node to delete:" << endl;
                cin >> index1;
                cout << "Index:" << index1 << endl;
                list.deleteNode(list, index1);
                cout << "Node deleted." << endl;
                list.display(list);
                break;
            }
            case 4: {
                cout << "Enter index:" << endl;
                int index2;
                cin >> index2;
                list.displayNode(list, index2);
                break;
            }
            case 5: {
                list.display(list);
                break;
            }
            default: {
                cout << "Invalid choice. ";
            }
        }
    }
    while (choice != 0);
    return 0;
}