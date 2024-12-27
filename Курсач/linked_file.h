#ifndef LINKED_FILE_H
#define LINKED_FILE_H

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class LinkedFile : public std::fstream {
private:
    struct Header {
        streampos head; // Указатель на начало первого элемента
        int count;           // Количество элементов
    };

    struct Node {
        streampos next; // Указатель на следующий элемент
        size_t length;       // Длина строки
        // Далее записывается сама строка (переменной длины)
    };

    Header header;
    std::string filename;

    void writeHeader();
    void readHeader();

public:
    LinkedFile(const std::string& filename);

    void add(const std::string& str);
    void display();
    void insertAt(int index, const std::string& str); // Вставка по индексу
    void shellSort(); // Сортировка Шелла
    void deleteNode(int index);
    void getStringAt(int index);
    void clear();

};

#endif
