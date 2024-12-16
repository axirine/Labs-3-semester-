#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    cout << "Choose data type to test" << endl;
    cout << "1. int" << endl;
    cout << "2. float" << endl;
    cout << "3. matrix" << endl;
    int type_choice;
    cin >> type_choice;

    while (1) {
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input" << endl;
        } else {
            break;
        }
    }

    List<int> intList;
    List<float> floatList;
    List<Matrix> matrixList;

    int type_choice_flag;

    while (1) {
        switch (type_choice) {
            case 1: {

                intList.append(intList, -4);
                intList.append(intList, -2);
                intList.append(intList, 1);
                intList.append(intList, 2);
                intList.append(intList, 4);
                intList.append(intList, 8);
                intList.append(intList, 16);
                intList.append(intList, 32);
                intList.append(intList, 64);
                intList.append(intList, 128);
                intList.append(intList, 256);
                intList.append(intList, 512);
                intList.append(intList, 1024);
                intList.append(intList, 2048);
                intList.append(intList, 4096);
                intList.append(intList, 8192);
                intList.append(intList, 16384);
                intList.append(intList, 32768);
                intList.append(intList, 65536);
                intList.display(intList);
                type_choice_flag = 1;
                break;
            }
            case 2: {
                floatList.append(floatList, 2.71828);
                floatList.append(floatList, 3.1415926535);
                floatList.append(floatList, 2.0);
                floatList.append(floatList, 2.1);
                floatList.append(floatList, 2.23);
                floatList.append(floatList, 123.123);
                floatList.display(floatList);
                type_choice_flag = 2;
                break;
            }
            case 3: {
                Matrix matrix(2);
                matrix.data[0][0] = 1;
                matrix.data[0][1] = 2;
                matrix.data[1][0] = 3;
                matrix.data[1][1] = 4;
                matrixList.append(matrixList, matrix);

                Matrix matrix1add(2);
                matrix1add.data[0][0] = 2;
                matrix1add.data[0][1] = 5;
                matrix1add.data[1][0] = 6;
                matrix1add.data[1][1] = 8;
                Matrix matrix2add(2);
                matrix2add.data[0][0] = 1;
                matrix2add.data[0][1] = 3;
                matrix2add.data[1][0] = 3;
                matrix2add.data[1][1] = 1;
                Matrix addresult = matrix1add.add(matrix2add);
                matrixList.append(matrixList, addresult);

                Matrix matrix1sub(2);
                matrix1sub.data[0][0] = 2;
                matrix1sub.data[0][1] = 5;
                matrix1sub.data[1][0] = 6;
                matrix1sub.data[1][1] = 8;
                Matrix matrix2sub(2);
                matrix2sub.data[0][0] = 1;
                matrix2sub.data[0][1] = 3;
                matrix2sub.data[1][0] = 3;
                matrix2sub.data[1][1] = 1;
                Matrix subresult = matrix1sub.subtract(matrix2sub);
                matrixList.append(matrixList, subresult);

                Matrix matrix1mul(2);
                matrix1mul.data[0][0] = 2;
                matrix1mul.data[0][1] = 5;
                matrix1mul.data[1][0] = 6;
                matrix1mul.data[1][1] = 8;
                Matrix matrix2mul(2);
                matrix2mul.data[0][0] = 1;
                matrix2mul.data[0][1] = 3;
                matrix2mul.data[1][0] = 3;
                matrix2mul.data[1][1] = 1;
                Matrix mulresult = matrix1mul.multiply(matrix2mul);
                matrixList.append(matrixList, mulresult);

                Matrix matrix1tr(3);
                matrix1tr.data[0][0] = 1;
                matrix1tr.data[0][1] = 2;
                matrix1tr.data[0][2] = 3;
                matrix1tr.data[1][0] = 4;
                matrix1tr.data[1][1] = 5;
                matrix1tr.data[1][2] = 6;
                matrix1tr.data[2][0] = 7;
                matrix1tr.data[2][1] = 8;
                matrix1tr.data[2][2] = 9;
                Matrix trresult = matrix1tr.transpose();
                matrixList.append(matrixList, trresult);

                Matrix matrix1det(4);
                matrix1det.data[0][0] = 3;
                matrix1det.data[0][1] = 5;
                matrix1det.data[0][2] = 7;
                matrix1det.data[0][3] = 8;
                matrix1det.data[1][0] = -1;
                matrix1det.data[1][1] = 7;
                matrix1det.data[1][2] = 0;
                matrix1det.data[1][3] = 1;
                matrix1det.data[2][0] = 0;
                matrix1det.data[2][1] = 5;
                matrix1det.data[2][2] = 3;
                matrix1det.data[2][3] = 2;
                matrix1det.data[3][0] = 1;
                matrix1det.data[3][1] = -1;
                matrix1det.data[3][2] = 7;
                matrix1det.data[3][3] = 4;
                int intermediate_detresult = matrix1det.determinant();
                Matrix detresult(1);
                detresult.data[0][0] = intermediate_detresult;
                matrixList.append(matrixList, detresult);

                type_choice_flag = 3;

                matrixList.display(matrixList);
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
                break;
            }
        }
        break;
    }
    while (1) {
        int flag = 0;
        cout << "Choose option:" << endl;
        cout << "1. Delete list" << endl;
        cout << "2. Insert node" << endl;
        cout << "3. Delete node" << endl;
        cout << "4. Show list" << endl;
        cout << "0. Exit" << endl;
        int list_action_choice;
        cin >> list_action_choice;
        while (1) {
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input" << endl;
            } else {
                break;
            }
        }
        switch (list_action_choice) {
            case 1: {
                if (type_choice_flag == 1) {
                    intList.deleteList();
                    cout << "List deleted." << endl;
                    break;
                } else if (type_choice_flag == 2) {
                    floatList.deleteList();
                    cout << "List deleted." << endl;
                    break;
                } else if (type_choice_flag == 3) {
                    matrixList.deleteList();
                    cout << "List deleted." << endl;
                    break;
                }
            }
            case 2: {
                if (type_choice_flag == 1) {
                    int index;
                    int value;
                    cout << "Enter index to insert" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    cout << "Enter value to insert" << endl;
                    cin >> value;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    intList.insertNode(intList, index, value);
                    intList.display(intList);
                    break;
                }
                if (type_choice_flag == 2) {
                    int index;
                    float value;
                    cout << "Enter index to insert" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    cout << "Enter value to insert" << endl;
                    cin >> value;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    floatList.insertNode(floatList, index, value);
                    floatList.display(floatList);
                    break;
                }
                if (type_choice_flag == 3) {
                    int size, index;
                    cout << "Enter index of the node to place:" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    cout << "Enter the number of rows and columns:" << endl;
                    cin >> size;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    if (size <= 0) {
                        cout << "Invalid matrix dimensions. Rows and columns must be greater than zero." << endl;
                        break;
                    }
                    Matrix value(size);
                    cout << "Enter new matrix data:" << endl;
                    cin >> value;
                    matrixList.insertNode(matrixList, index, value);
                    cout << "Node placed." << endl;
                    matrixList.display(matrixList);
                    break;
                }
            }
            case 3: {
                int index;
                if (type_choice_flag == 1) {
                    cout << "Enter index to delete node" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    intList.deleteNode(intList, index);
                    intList.display(intList);
                    break;
                }
                if (type_choice_flag == 2) {
                    cout << "Enter index to delete node" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    floatList.deleteNode(floatList, index);
                    floatList.display(floatList);
                    break;
                }
                if (type_choice_flag == 3) {
                    cout << "Enter index to delete node" << endl;
                    cin >> index;
                    while (1) {
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid input" << endl;
                        } else {
                            break;
                        }
                    }
                    matrixList.deleteNode(matrixList, index);
                    matrixList.display(matrixList);
                    break;
                }
            }
            case 4: {
                if (type_choice_flag == 1) {
                    intList.display(intList);
                } else if (type_choice_flag == 2) {
                    floatList.display(floatList);
                } else if (type_choice_flag == 3) {
                    matrixList.display(matrixList);
                }
                break;
            }
            case 0: {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            break;
            return 0;
        }
    }
}