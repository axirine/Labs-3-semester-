#include "matrix.h"
using namespace std;

int main() {
    Menu_print menu;
    List list;
    Node* head;
        Matrix* result;
        while (1) {
            int MatrixType;
            bool is_result_stored = false;
            menu.matrixTypes();
            while (1) {
                try {
                    cin >> MatrixType;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        throw invalid_argument("Invalid input");
                    }
                    if (MatrixType < 0 || MatrixType > 3) {
                        throw out_of_range("Invalid matrix type. Please choose between 0 to 3");
                    }
                    break;
                }
                catch (const exception& e) {
                    cerr << "Error: " << e.what() << '\n';
                }
            }
            if (MatrixType == 1) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    try {
                        cin >> choice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument("Invalid input");
                        }
                        if (choice < 0 || choice > 8) {
                            throw out_of_range("Invalid option. Please choose between 0 to 8");
                        }
                    }
                    catch (const exception& e) {
                        cerr << "Error: " << e.what() << '\n';
                    }
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:";
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows != cols) {
                                        throw logic_error("Rows and cols must be equal");
                                    }
                                    if ((rows == 1) && (cols == 1)) {
                                        throw logic_error("Identity matrix");
                                    }
                                    break;
                                }
                                SquareMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1 + matrix2;
                                result = new SquareMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 2) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows != cols) {
                                        throw logic_error("Rows and cols must be equal");
                                    }
                                    if ((rows == 1) && (cols == 1)) {
                                        throw logic_error("Identity matrix");
                                    }
                                    break;
                                }
                                SquareMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1- matrix2;
                                result = new SquareMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 3) {
                        if (is_result_stored == false) {
                            int rows1, cols1, rows2, cols2;
                            cout << "Size of first matrix: " << endl;
                            try {
                                while (1) {
                                    cin >> rows1;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols1;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows1 != cols1) {
                                        throw logic_error("Rows and cols must be equal");
                                    }
                                    if ((rows1 == 1) && (cols1 == 1)) {
                                        throw logic_error("Identity matrix");
                                    }
                                    break;
                                }
                                SquareMatrix matrix1(rows1, cols1);
                                cout << "Size of second matrix: " << endl;
                                while (1) {
                                    cin >> rows2;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols2;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows2 != cols2) {
                                        throw logic_error("Rows and cols must be equal");
                                    }
                                    if ((rows2 == 1) && (cols2 == 1)) {
                                        throw logic_error("Identity matrix");
                                    }
                                    break;
                                }
                                SquareMatrix matrix2(rows2, cols2);
                                if (cols1 != rows2) {
                                    throw logic_error("Matrices can't be multiplied");
                                }
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1.multiply(matrix2);
                                result = new SquareMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 4) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Size of matrix: ";
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows != cols) {
                                        throw logic_error("Rows and cols must be equal");
                                    }
                                    if ((rows == 1) && (cols == 1)) {
                                        throw logic_error("Identity matrix");
                                    }
                                    break;
                                }
                                SquareMatrix matrix1(rows, cols);
                                cin >> matrix1;
                                Matrix temp = matrix1.transpose();
                                result = new SquareMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            try {
                                ofstream ofs("matrix.txt");
                                ofs << *result;
                                ofs.close();
                                cout << "Result saved to file." << endl;
                            }
                            catch (const ios_base::failure& e) {
                                cerr << "File error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << endl;
                            }
                            catch (const exception& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        try {
                            ifstream ifs("matrix.txt");
                            if (ifs.is_open()) {
                                ifs >> *result;
                                cout << "Matrix loaded from file: " << "\n" << *result << endl;
                                is_result_stored = true;
                                ifs.close();
                            }
                            else {
                                throw ios_base::failure("Unable to open file");
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    if (choice == 7) {
                        try {
                            if (is_result_stored) {
                                result->saveToBinary("matrix.bin");
                            }
                            else {
                                cout << "No result to save!" << endl;
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    if (choice == 8) {
                        try {
                            result->loadFromBinary("matrix.bin");
                            is_result_stored = true;
                            result->print();
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Memory allocation error: " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                }
            }
            else if (MatrixType == 2) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    try {
                        cin >> choice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument("Invalid input");
                        }
                        if (choice < 0 || choice > 8) {
                            throw out_of_range("Invalid option. Please choose between 0 to 8");
                        }
                    }
                    catch (const exception& e) {
                        cerr << "Error: " << e.what() << '\n';
                    }
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        try {
                            if (is_result_stored == false) {
                                int rows = 1;
                                int cols = 1;
                                IdentityMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1 + matrix2;
                                result = new IdentityMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            else {
                                cout << "Impossible to exceed the specified list size" << endl;
                            }
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << '\n';
                        }
                    }
                    if (choice == 2) {
                        try {
                            if (is_result_stored == false) {
                                int rows = 1;
                                int cols = 1;
                                IdentityMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1 - matrix2;
                                result = new IdentityMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            else {
                                cout << "Impossible to exceed the specified list size" << endl;
                            }
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << '\n';
                        }
                    }
                    if (choice == 3) {
                        try {
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
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            else {
                                cout << "Impossible to exceed the specified list size" << endl;
                            }
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << '\n';
                        }
                    }
                    if (choice == 4) {
                        try{
                            if (is_result_stored == false) {
                                int rows = 1;
                                int cols = 1;
                                IdentityMatrix matrix1(rows, cols);
                                cin >> matrix1;
                                Matrix temp = matrix1.transpose();
                                result = new IdentityMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            else {
                                cout << "Impossible to exceed the specified list size" << endl;
                            }
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << '\n';
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            try {
                                ofstream ofs("matrix.txt");
                                ofs << *result;
                                ofs.close();
                                cout << "Result saved to file." << endl;
                            }
                            catch (const ios_base::failure& e) {
                                cerr << "File error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << endl;
                            }
                            catch (const exception& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        try {
                            ifstream ifs("matrix.txt");
                            if (ifs.is_open()) {
                                ifs >> *result;
                                cout << "Matrix loaded from file: " << "\n" << *result << endl;
                                is_result_stored = true;
                                ifs.close();
                            }
                            else {
                                throw ios_base::failure("Unable to open file");
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    if (choice == 7) {
                        try {
                            if (is_result_stored) {
                                result->saveToBinary("matrix.bin");
                            }
                            else {
                                cout << "No result to save!" << endl;
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    if (choice == 8) {
                        try {
                            result->loadFromBinary("matrix.bin");
                            is_result_stored = true;
                            result->print();
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                }
            }
            else if (MatrixType == 3) {
                while (1) {
                    int choice;
                    menu.mathOptions();
                    try {
                        cin >> choice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            throw invalid_argument("Invalid input");
                        }
                        if (choice < 0 || choice > 8) {
                            throw out_of_range("Invalid option. Please choose between 0 to 8");
                        }
                    }
                    catch (const exception& e) {
                        cerr << "Error: " << e.what() << '\n';
                    }
                    if (choice == 0) {
                        break;
                    }
                    if (choice == 1) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows == cols) {
                                        throw logic_error("Rows and cols can't be equal");
                                    }
                                    break;
                                }
                                RectangularMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1 + matrix2;
                                result = new RectangularMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 2) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Enter matrix size:" << endl;
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows == cols) {
                                        throw logic_error("Rows and cols can't be equal");
                                    }
                                    break;
                                }
                                RectangularMatrix matrix1(rows, cols), matrix2(rows, cols);
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1 - matrix2;
                                result = new RectangularMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 3) {
                        if (is_result_stored == false) {
                            try {
                                int rows1, cols1, rows2, cols2;
                                cout << "Size of first matrix: ";
                                while (1) {
                                    cin >> rows1;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols1;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows1 == cols1) {
                                        throw logic_error("Rows and cols can't be equal");
                                    }
                                    break;
                                }
                                RectangularMatrix matrix1(rows1, cols1);
                                cout << "Size of second matrix: ";
                                while (1) {
                                    cin >> rows2;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols2;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows2 == cols2) {
                                        throw logic_error("Rows and cols can't be equal");
                                    }
                                    break;
                                }
                                RectangularMatrix matrix2(rows2, cols2);
                                if (cols1 != rows2) {
                                    throw logic_error("Matrices can't be multiplied");
                                }
                                cin >> matrix1 >> matrix2;
                                Matrix temp = matrix1.multiply(matrix2);
                                result = new RectangularMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 4) {
                        if (is_result_stored == false) {
                            int rows, cols;
                            cout << "Size of matrix: ";
                            try {
                                while (1) {
                                    cin >> rows;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    cin >> cols;
                                    if (cin.fail()) {
                                        throw invalid_argument("Invalid input");
                                    }
                                    if (rows == cols) {
                                        throw logic_error("Rows and cols can't be equal");
                                    }
                                    break;
                                }
                                RectangularMatrix matrix1(rows, cols);
                                cin >> matrix1;
                                Matrix temp = matrix1.transpose();
                                result = new RectangularMatrix(temp);
                                list.append(list, result);
                                is_result_stored = true;
                                cout << "Matrix added to the list." << endl;
                                list.display(list);
                            }
                            catch (const invalid_argument& e) {
                                cerr << "Error: " << e.what() << '\n';
                                cin.clear();
                                cin.ignore(1000, '\n');
                            }
                            catch (const out_of_range& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << '\n';
                            }
                            catch (const logic_error& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "Impossible to exceed the specified list size" << endl;
                        }
                    }
                    if (choice == 5) {
                        if (is_result_stored) {
                            try {
                                ofstream ofs("matrix.txt");
                                ofs << *result;
                                ofs.close();
                                cout << "Result saved to file." << endl;
                            }
                            catch (const ios_base::failure& e) {
                                cerr << "File error: " << e.what() << '\n';
                            }
                            catch (const bad_alloc& e) {
                                cerr << "Error (memory allocation): " << e.what() << endl;
                            }
                            catch (const exception& e) {
                                cerr << "Error: " << e.what() << '\n';
                            }
                        }
                        else {
                            cout << "No result to save!" << endl;
                        }
                    }
                    if (choice == 6) {
                        try {
                            ifstream ifs("matrix.txt");
                            if (ifs.is_open()) {
                                ifs >> *result;
                                cout << "Matrix loaded from file: " << "\n" << *result << endl;
                                is_result_stored = true;
                                ifs.close();
                            }
                            else {
                                cout << "Unable to open file" << endl;
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << '\n';
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << '\n';
                        }
                    }
                    if (choice == 7) {
                        try {
                            if (is_result_stored) {
                                result->saveToBinary("matrix.bin");
                            }
                            else {
                                cout << "No result to save!" << endl;
                            }
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Error (memory allocation): " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                    if (choice == 8) {
                        try {
                            result->loadFromBinary("matrix.bin");
                            is_result_stored = true;
                            result->print();
                        }
                        catch (const ios_base::failure& e) {
                            cerr << "File error: " << e.what() << endl;
                        }
                        catch (const bad_alloc& e) {
                            cerr << "Memory allocation error: " << e.what() << endl;
                        }
                        catch (const exception& e) {
                            cerr << "Error: " << e.what() << endl;
                        }
                    }
                }
            }
            else if (MatrixType == 0) {
                break;
            }
        }
    cout << "List of matrices:" << endl;
    list.display(list);
    int choice;
    do {
        menu.listOptions();
        try {
            cin >> choice;
            if (cin.fail()) {
                throw invalid_argument("Invalid input");
            }
            if (choice < 0 || choice > 5) {
                throw out_of_range("Invalid option. Please choose between 0 to 5");
            }
        }
        catch (const invalid_argument& e) {
            cerr << "Error: " << e.what() << '\n';
            cin.clear();
            cin.ignore(1000, '\n');
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << '\n';
        }
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
                try {
                    cout << "Enter index of the node to place:" << endl;
                    cin >> index;
                    cout << "Enter the number of rows and columns:" << endl;
                    cin >> rows >> cols;
                    Matrix* newMatrix = new Matrix(rows, cols);
                    cout << "Enter new matrix data:" << endl;
                    cin >> *newMatrix;
                    list.insertNode(list, index, newMatrix);
                    cout << "Node placed." << endl;
                    list.display(list);
                }
                catch (const invalid_argument& e) {
                    cerr << "Error: " << e.what() << '\n';
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << '\n';
                }
                catch (const bad_alloc& e) {
                    cerr << "Error (memory allocation): " << e.what() << '\n';
                }
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
                try {
                    cout << "Enter index:" << endl;
                    int index2;
                    cin >> index2;
                    list.displayNode(list, index2);
                }
                catch (const invalid_argument& e) {
                    cerr << "Error: " << e.what() << '\n';
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                catch (const out_of_range& e) {
                    cerr << "Error: " << e.what() << '\n';
                }
                break;
            }
            case 5: {
                list.display(list);
                break;
            }
        }
    } while (choice != 0);
    return 0;
}

