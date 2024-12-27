#include "linked_file.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

// Конструктор
LinkedFile::LinkedFile(const string& filename) : filename(filename) {
    this->open(filename, ios::in | ios::out | ios::binary);
    if (!this->is_open()) {
        this->open(filename, ios::out | ios::binary);
        header.head = -1;
        header.count = 0;
        writeHeader();
        this->close();
        this->open(filename, ios::in | ios::out | ios::binary);
    } else {
        readHeader();
    }
}


// Запись заголовка в начало файла
void LinkedFile::writeHeader() {
    this->seekp(0, ios::beg);
    this->write(reinterpret_cast<char*>(&header.head), sizeof(header.head));
    this->write(reinterpret_cast<char*>(&header.count), sizeof(header.count));
}

// Чтение заголовка из файла
void LinkedFile::readHeader() {
    this->seekg(0, ios::beg);
    this->read(reinterpret_cast<char*>(&header.head), sizeof(header.head));
    this->read(reinterpret_cast<char*>(&header.count), sizeof(header.count));
}

// Добавление строки в конец списка
void LinkedFile::add(const string& str) {
    Node newNode;
    newNode.length = str.size();
    newNode.next = -1;

    // Переход в конец файла
    this->seekp(0, end);
    streampos currentPos = this->tellp();

    // Запись нового узла
    this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
    this->write(reinterpret_cast<char*>(&newNode.length), sizeof(newNode.length));
    this->write(str.c_str(), newNode.length);

    // Обновление предыдущего узла, если он есть
    if (header.head == -1) {
        header.head = currentPos;
    } else {
        streampos prevPos = header.head;
        Node prevNode;

        while (true) {
            this->seekg(prevPos, ios::beg);
            this->read(reinterpret_cast<char*>(&prevNode.next), sizeof(prevNode.next));
            if (prevNode.next == -1) {
                this->seekp(prevPos, ios::beg);
                this->write(reinterpret_cast<char*>(&currentPos), sizeof(currentPos));
                break;
            }
            prevPos = prevNode.next;
        }
    }

    header.count++;
    writeHeader();
}

// Отображение всех строк
void LinkedFile::display() {
    if (header.head == -1) {
        cout << "List is empty.\n";
        return;
    }

    streampos currentPos = header.head;
    Node node;
    string str;
    int counter = 0;
    while (currentPos != -1) {
        this->seekg(currentPos, ios::beg);

        this->read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        this->read(reinterpret_cast<char*>(&node.length), sizeof(node.length));

        str.resize(node.length);
        this->read(&str[0], node.length);
        counter++;
        cout << counter << ": " << str << "\n";

        currentPos = node.next;
    }
}

// Вставка строки по индексу
void LinkedFile::insertAt(int index, const string& str) {
    if (cin.fail()) {
        throw invalid_argument("Invalid input");
    }
    if (index < 0) {
        throw out_of_range("Index cannot be negative.");
    }
    if (index > header.count) {
        throw out_of_range("Index is out of range.");
    }

    Node newNode;
    newNode.length = str.size();
    newNode.next = -1;

    // Определение позиции нового узла
    streampos newPos = this->tellp();
    this->seekp(0, ios::end);
    this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
    this->write(reinterpret_cast<char*>(&newNode.length), sizeof(newNode.length));
    this->write(str.c_str(), newNode.length);

    if (header.count == 0) {
        // Вставка в пустой список
        header.head = newPos;
        cout << "Inserted first node.\n";
    } else if (index == 0) {
        // Вставка в начало списка
        newNode.next = header.head;
        header.head = newPos;
        this->seekp(newPos, ios::beg);
        this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
        cout << "Inserted node at the beginning.\n";
    } else {
        // Вставка в середину или конец списка
        streampos prevPos = header.head;
        Node prevNode;

        for (int i = 0; i < index - 1; i++) {
            this->seekg(prevPos, ios::beg);
            this->read(reinterpret_cast<char*>(&prevNode.next), sizeof(prevNode.next));
            prevPos = prevNode.next;
        }

        // Считывание предыдущего узла
        this->seekg(prevPos, ios::beg);
        this->read(reinterpret_cast<char*>(&prevNode.next), sizeof(prevNode.next));

        newNode.next = prevNode.next;
        prevNode.next = newPos;

        // Запись обновлённого предыдущего узла
        this->seekp(prevPos, ios::beg);
        this->write(reinterpret_cast<char*>(&prevNode.next), sizeof(prevNode.next));

        // Запись нового узла
        this->seekp(newPos, ios::beg);
        this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));

        cout << "Inserted node at index " << index << ".\n";
    }

    header.count++;
    writeHeader();
}

void LinkedFile::deleteNode(int index) {
    if (index < 0 || index >= header.count) {
        cout << "Out of bounds.\n";
        return;
    }

    streampos currentPos = header.head;
    streampos prevPos = -1;
    Node currentNode;

    for (int i = 0; i <= index; i++) {
        this->seekg(currentPos, ios::beg);
        this->read(reinterpret_cast<char*>(&currentNode.next), sizeof(currentNode.next));
        this->read(reinterpret_cast<char*>(&currentNode.length), sizeof(currentNode.length));

        if (i == index) {
            if (prevPos == -1) {
                header.head = currentNode.next;
            } else {
                this->seekp(prevPos, ios::beg);
                this->write(reinterpret_cast<char*>(&currentNode.next), sizeof(currentNode.next));
            }

            header.count--;
            writeHeader();
            cout << "Node deleted.\n";
            return;
        }

        prevPos = currentPos;
        currentPos = currentNode.next;
    }
}

void LinkedFile::getStringAt(int index) {
    if (index < 0 || index >= header.count) {
        cout << "Out of bounds.\n";
        return;
    }

    streampos currentPos = header.head;
    Node node;
    string str;

    for (int i = 0; i <= index; i++) {
        this->seekg(currentPos, ios::beg);
        this->read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        this->read(reinterpret_cast<char*>(&node.length), sizeof(node.length));

        if (i == index) {
            str.resize(node.length);
            this->read(&str[0], node.length);
            cout << "String at index " << index << ": " << str << "\n";
            return;
        }

        currentPos = node.next;
    }
}

void LinkedFile::clear() {
    this->close();
    this->open(filename, ios::out | ios::binary);
    if (this->is_open()) {
        header.head = -1;
        header.count = 0;
        writeHeader();
        cout << "File and list cleared.\n";
    } else {
        cout << "Failed to clear the file.\n";
    }
    this->close();
    this->open(filename, ios::in | ios::out | ios::binary);
}

void LinkedFile::shellSort() {
    if (header.count <= 1) {
        cout << "List is already sorted or empty.\n";
        return;
    }

    // Считывание всех узлов в память
    vector<string> strings; // Хранение строк
    streampos currentPos = header.head;
    Node node;
    string str;

    while (currentPos != -1) {
        this->seekg(currentPos, ios::beg);
        this->read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        this->read(reinterpret_cast<char*>(&node.length), sizeof(node.length));

        str.resize(node.length);
        this->read(&str[0], node.length);
        strings.push_back(str);

        currentPos = node.next;
    }
    int n = strings.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            string temp = strings[i];
            int j;
            for (j = i; j >= gap && strings[j - gap].size() > temp.size(); j -= gap) {
                strings[j] = strings[j - gap];
            }
            strings[j] = temp;
        }
    }
    this->close();
    this->open(filename, ios::out | ios::binary);
    header.head = -1;
    header.count = 0;
    writeHeader();
    streampos prevPos = -1;
    for (const auto& str : strings) {
        // Позиция текущего узла
        Node newNode;
        newNode.length = str.size();
        newNode.next = -1;
        this->seekp(0, ios::end);
        streampos currentPos = this->tellp();
        // Если первый узел, обновляем заголовок
        if (header.head == -1) {
            header.head = currentPos;
        }

        // Связывание предыдущего узла с текущим
        if (prevPos != -1) {
            this->seekp(prevPos, ios::beg);
            this->write(reinterpret_cast<char*>(&currentPos), sizeof(currentPos));
        }

        // Запись текущего узла
        this->seekp(currentPos, ios::beg);
        this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
        this->write(reinterpret_cast<char*>(&newNode.length), sizeof(newNode.length));
        this->write(str.c_str(), newNode.length);

        prevPos = currentPos;
        header.count++;
    }
    writeHeader();
    this->close();
    this->open(filename, ios::in | ios::out | ios::binary);
    cout << "List has been sorted by string length.\n";
}

// Загрузка списка из текстового файла
void LinkedFile::loadFromTextFile(const string& textFilename) {
    ifstream inFile(textFilename, ios::in);

    if (!inFile) {
        cerr << "Error: Unable to open file " << textFilename << endl;
        return;
    }
    string fileContent((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    string currentLine;
    for (char c : fileContent) {
        if (c == '\n') {
            add(currentLine);
            currentLine.clear();
        } else {
            currentLine += c;
        }
    }
    if (!currentLine.empty()) {
        add(currentLine);
    }
    cout << "File loaded successfully from " << textFilename << endl;
}

// Сохранение списка в текстовый файл
void LinkedFile::saveToTextFile(const string& textFilename) {
    ofstream textFile(textFilename);
    if (!textFile.is_open()) {
        cerr << "Failed to open text file.\n";
        return;
    }
    streampos currentPos = header.head;
    Node node;
    string str;
    while (currentPos != -1) {
        this->seekg(currentPos, ios::beg);
        this->read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        this->read(reinterpret_cast<char*>(&node.length), sizeof(node.length));
        str.resize(node.length);
        this->read(&str[0], node.length);
        textFile << str << "\n";
        currentPos = node.next;
    }
    cout << "Saved data from binary file to text file.\n";
}

// Сохранение списка в бинарный файл
void LinkedFile::saveToBinaryFile(const string &binaryFilename) {
    ofstream outFile(binaryFilename, ios::binary);
    if (!outFile) {
        cerr << "Error: Unable to open file for writing: " << binaryFilename << endl;
        return;
    }
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    streampos currentPos = header.head;
    while (currentPos != streampos(-1)) {
        Node node;
        this->seekg(currentPos);
        this->read(reinterpret_cast<char*>(&node), sizeof(Node));
        outFile.write(reinterpret_cast<const char*>(&node), sizeof(Node));
        string data(node.length, '\0');
        this->read(&data[0], node.length);
        outFile.write(data.c_str(), node.length);
        currentPos = node.next;
    }
    outFile.close();
    cout << "Linked list successfully saved to binary file: " << binaryFilename << endl;
}

// Загрузка списка из бинарного файла
void LinkedFile::loadFromBinaryFile(const string& binaryFilename) {
    ifstream inFile(binaryFilename, ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open file for reading: " << binaryFilename << endl;
        return;
    }
    clear();
    while (!inFile.eof()) {
        size_t length = 0;
        inFile.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (inFile.eof()) break;
        string data(length, '\0');
        inFile.read(&data[0], length);
        add(data);
    }
    inFile.close();
    cout << "List successfully loaded from binary file: " << binaryFilename << endl;
}
