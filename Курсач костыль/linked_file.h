#ifndef LINKED_FILE_H
#define LINKED_FILE_H

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class LinkedFile : public std::fstream {
private:
    struct Header {
        streampos head;
        int count;
    };
    struct Node {
        streampos next;
        size_t length;
        string data;
    };
    Header header;
    string filename;
    void writeHeader();
    void readHeader();
public:
    LinkedFile(const std::string& filename);
    void add(const std::string& str);
    void display();
    void insertAt(int index, const std::string& str);
    void shellSort();
    void deleteNode(int index);
    void getStringAt(int index);
    void clear();
    void loadFromTextFile(const string &textFilename);
    void saveToTextFile(const string &textFilename);
    void saveToBinaryFile(const string &binaryFilename);
    void loadFromBinaryFile(const string &binaryFilename);
};

#endif
