#include "linked_file.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

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
    newNode.data = str;

    // Переход в конец файла
    this->seekp(0, end);
    streampos currentPos = this->tellp();

    // Запись нового узла
    this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
    this->write(reinterpret_cast<char*>(&newNode.length), sizeof(newNode.length));
    this->write(newNode.data.c_str(), sizeof(newNode.data));

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
    int counter = -1;
    while (currentPos != -1) {
        this->seekg(currentPos, ios::beg);

        this->read(reinterpret_cast<char*>(&node.next), sizeof(node.next));
        this->read(reinterpret_cast<char*>(&node.length), sizeof(node.length));
        str.resize(node.length);
        this->read(&str[0], node.length);
        node.data.resize(node.length);
        node.data = str;
//        cout << "stroke: " << str << endl;
//        cout << "node.next = " << node.next << ", node.length = " << node.length << ", node.data = " << node.data << endl;
        counter++;
        cout << counter << ": " << str << "\n";
        // ------------- костыль -------------
        if (counter > 10) {
            cout << "Infinite loop" << endl;
            break;
        }
        // -----------------------------------
        currentPos = node.next;
    }
}

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
    newNode.data = str;

    // Определение позиции нового узла
    streampos newPos = this->tellp();
    this->seekp(0, ios::end);
    this->write(reinterpret_cast<char*>(&newNode.next), sizeof(newNode.next));
    this->write(reinterpret_cast<char*>(&newNode.length), sizeof(newNode.length));
    this->write(newNode.data.c_str(), newNode.length);
    cout << "Adding value " + str + " to the index " << index << endl;

    if (header.count == 0) {
        // Вставка в пустой список
        header.head = newPos;
        cout << "Inserted first node.\n";
        return;
    }

// Определение временного файла, куда будет подгружаться список
    string tempFilename = filename + ".tmp";
    fstream tempFile(tempFilename, ios::out | ios::binary);
    if (!tempFile.is_open()) {
        cerr << "Error: Unable to create temporary file.\n";
        return;
    }

    // Read the header
    this->seekg(0, ios::beg);
    this->read(reinterpret_cast<char*>(&header), sizeof(header));

    // Записываем в файл новый header c обновлёнными ссылками и счётчиком
    int newCount = header.count + 1;
    tempFile.write(reinterpret_cast<char*>(&header.head), sizeof(header.head));
    tempFile.write(reinterpret_cast<char*>(&newCount), sizeof(newCount));
    cout << "New header" << endl;

    streampos currentPos = newPos;
    Node currentNode;
    int currentListIndex = 0;
    this->seekp(currentPos, ios::beg);
    cout << "Moved to 0" << endl;

    while (currentPos != -1) {
        streampos newWritePos;
        streampos nextReadPos;

        if (index == currentListIndex) {
            cout << "index == currentListIndex" << endl;
            // Сначала вставляем новую ноду
            newWritePos = tempFile.tellp();
            newWritePos += sizeof(newNode);
            newNode.next = newWritePos;
            cout << "Inserted node" << endl;

            tempFile.write(reinterpret_cast<char *>(&newNode), sizeof(newNode));
            this->display();

            // А потом вставляем то значение, которое там уже было
            this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
            newWritePos = tempFile.tellp();
            newWritePos += sizeof(currentNode);
            cout << "Setting nextReadPos 187 to " << currentNode.next << endl;
            nextReadPos = currentNode.next;
            currentNode.next = newWritePos;

            tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
            this->display();
        } else {
            cout << "index != currentListIndex" << endl;
            this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
            newWritePos = tempFile.tellp();
            newWritePos += sizeof(currentNode);
            cout << "Setting nextReadPos 202 to " << currentNode.next << endl;
            nextReadPos = currentNode.next;
            currentNode.next = newWritePos;

            tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
            this->display();
        }
        this->seekg(nextReadPos, ios::beg);
        currentPos = nextReadPos;
        currentListIndex++;
    }
    this->close();
    tempFile.close();
    cout << "renaming " << tempFilename << " -> " << filename << endl;
    try {
        if (std::remove(filename.c_str()) != 0) {
            std::perror("Error deleting file");
        }
        std::filesystem::rename(tempFilename, filename);
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    cout << "Node inserted at index " << index << endl;
}

void LinkedFile::deleteNode(int index) {
    if (index < 0 || index >= header.count) {
        std::cerr << "Invalid index" << std::endl;
        return;
    }

    string tempFilename = filename + ".tmp";
    fstream tempFile(tempFilename, ios::out | ios::binary);
    if (!tempFile.is_open()) {
        cerr << "Error: Unable to create temporary file.\n";
        return;
    }

    // Read the header
    this->seekg(0, ios::beg);
    this->read(reinterpret_cast<char*>(&header), sizeof(header));

    // Записываем в файл новый header c обновлёнными ссылками и счётчиком
    int newCount = header.count - 1;
    tempFile.write(reinterpret_cast<char*>(&header.head), sizeof(header.head));
    tempFile.write(reinterpret_cast<char*>(&newCount), sizeof(newCount));


    if (newCount == 0) {
        // Header добавлен, а записей нет
        tempFile.close();
        return;
    }

    if (index == 0) {
        // Пропускаем первую ноду, записываем все остальные
        this->seekg(header.head, ios::beg);
        Node currentNode;
        this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));

        streampos currentPos = currentNode.next;

        while (currentPos != -1) {
            this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
            currentPos = currentNode.next;

            streampos newPos = tempFile.tellp();
            newPos += sizeof(currentNode);
            currentNode.next = newPos;
            tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
//            cout << "Calculated offset: " << newPos << ", actual offset: " << tempFile.tellp() << endl;
//            if (newPos != tempFile.tellp()) {
//                throw std::runtime_error("Different offsets, please recalculate them");
//            }
        }
        return;
    }

    Node currentNode;
    streampos currentReadPos;
    int currentListIndex = 0;

    currentReadPos = header.head;
//    this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
//    tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
//
////    prevPos = currentReadPos;
////    prevNode = currentNode;

    while (currentReadPos != -1) {
        this->read(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
        currentReadPos = currentNode.next;

        streampos newWritePos = tempFile.tellp();
        newWritePos += sizeof(currentNode);
        currentNode.next = newWritePos;

        if (currentListIndex != index) {
            tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
//            cout << "Calculated offset: " << newWritePos << ", actual offset: " << tempFile.tellp() << endl;
//            if (newWritePos != tempFile.tellp()) {
//                throw std::runtime_error("Different offsets, please recalculate them");
//            }
        }
        currentListIndex++;
    }

    header.count--;
    writeHeader();
    std::filesystem::rename(tempFilename, filename);
    tempFile.close();
    cout << "Node deleted.\n";
}


//void LinkedFile::deleteNode(int index) {
//    if (index < 0 || index >= header.count) {
//        cout << "Out of bounds.\n";
//        return;
//    }
//
//    streampos currentPos = header.head;
//    streampos prevPos = -1;
//    Node prevNode;
//
//    string tempFilename = filename + ".tmp";
//
//    fstream tempFile(tempFilename, ios::out | ios::binary);
//    if (!tempFile.is_open()) {
//        cerr << "Error: Unable to create temporary file.\n";
//        return;
//    }
//
//    this->seekg(header.head, ios::beg);
//
//    // header для файла с удалённой нодой
//    tempFile.seekp(0, ios::beg);
//    tempFile.write(reinterpret_cast<char*>(&header.head), sizeof(header.head));
//    int new_count = header.count - 1;
//    tempFile.write(reinterpret_cast<char*>(&new_count), sizeof(new_count));
//
//
//    currentPos = header.head;
//    Node currentNode;
//    int nodeIndex = 0;
//
//    while (currentPos != -1) {
//        this -> seekg(currentPos, ios::beg);
//        this -> read(reinterpret_cast<char*>(&currentNode), sizeof(Node));
//
//        if (nodeIndex != index) {
//            streampos newPos = tempFile.tellp();
//            tempFile.write(reinterpret_cast<char *>(&currentNode), sizeof(currentNode));
//        }
//    }

//    cout << "currentPos 199 = " << currentPos << endl;
//    cout << "count = " << header.count << endl;
//
//    for (int i = 0; i < header.count; ++i) {
//        this->seekg(currentPos, ios::cur);
//        cout << "delete from pos = " << currentPos << endl;
//        this->read(reinterpret_cast<char *>(&currentNode.next), sizeof(currentNode.next));
//        this->read(reinterpret_cast<char *>(&currentNode.length), sizeof(currentNode.length));
//
//        cout << "next = " << reinterpret_cast<char *>(&currentNode.next) << endl;
//        cout << "length = " << reinterpret_cast<char *>(&currentNode.length) << endl << endl;
//
//        if (index != currentPos) {
//            tempFile.write(reinterpret_cast<char *>(&currentNode.next), sizeof(currentNode.next));
//            tempFile.write(reinterpret_cast<char *>(&currentNode.length), sizeof(currentNode.length));
//        }
//        if (currentPos == header.count) {
//            break;
//        }
//        currentPos = currentNode.next;
//    }

//    header.count--;
//    writeHeader();
//    std::filesystem::rename(tempFilename, filename);
//    tempFile.close();
//    cout << "Node deleted.\n";
//}

/*





    for (int i = 0; i <= header.count; i++) {
        this->seekg(currentPos, ios::beg);
        this->read(reinterpret_cast<char*>(&currentNode.next), sizeof(currentNode.next));
        this->read(reinterpret_cast<char*>(&currentNode.length), sizeof(currentNode.length));

        if (i == index) {
            // Заполняем prevNode
            this->seekg(prevPos, ios::end);
            this->read(reinterpret_cast<char*>(&prevNode.next), sizeof(prevNode.next));
            this->read(reinterpret_cast<char*>(&prevNode.length), sizeof(prevNode.length));

            this->seekg(currentPos, ios::beg);

            // Для списка из 1 элемента
            if (prevPos == currentPos) {
                this->write(reinterpret_cast<char*>(NULL), sizeof(currentNode.next));
                this->write(reinterpret_cast<char*>(NULL), sizeof(currentNode.next));
            }



            if (prevPos == -1) {
                header.head = currentNode.next;
            } else {
                this->seekp(prevPos, ios::beg);
                this->write(reinterpret_cast<char*>(&currentNode.next), sizeof(currentNode.next));
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
}*/

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
                node.data = str;
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
