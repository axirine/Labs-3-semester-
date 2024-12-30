#include "linked_file.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    LinkedFile file("linked_list.bin");
    int choice, index;
    string input;

    do {
        cout << "\n1. Add string" << endl;
        cout << "2. Display list" << endl;
        cout << "3. Insert string at index" << endl;
        cout << "4. Sort list" << endl;
        cout << "5. Delete stroke" << endl;
        cout << "6. Display node" << endl;
        cout << "7. Clear file and list" << endl;
        cout << "8. Load from text file" << endl;
        cout << "9. Save to text file" << endl;
        cout << "10. Save to binary file" << endl;
        cout << "11. Load from binary file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose option:";

        while (true) {
            cin >> choice;
            if (cin.fail() || choice < 0 || choice > 11) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Try again: ";
            } else {
                cin.ignore(1000, '\n');
                break;
            }
        }

        switch (choice) {
            case 1:
                cout << "Enter string: ";
                getline(cin, input);
                file.add(input);
                break;
            case 2:
                file.display();
                break;
            case 3:
                cout << "Enter index: ";
                cin >> index;
                cin.ignore(1000, '\n');
                cout << "Enter string: ";
                getline(cin, input);
                file.insertAt(index, input);
                break;
            case 4:
                file.shellSort();
                break;
            case 5:
                cout << "Enter index to delete: ";
                cin >> index;
                cin.ignore(1000, '\n');
                file.deleteNode(index);
                break;
            case 6:
                cout << "Enter index to get string: ";
                cin >> index;
                cin.ignore(1000, '\n');
                file.getStringAt(index);
                break;
            case 7:
                file.clear();
                break;
            case 8:
                file.clear();
                cout << "Enter text file name to load from: ";
                getline(cin, input);
                file.loadFromTextFile(input);
                break;
            case 9:
                cout << "Enter text file name to save to: ";
                getline(cin, input);
                file.saveToTextFile(input);
                break;
            case 10:
                cout << "Successfuly saved" << endl;
                break;
            case 11:
                file.display();
                break;
            case 0:
                cout << "Exit...\n";
                break;
            default:
                cout << "Incorrect choice.\n";
        }
    } while (choice != 0);

    return 0;
}
