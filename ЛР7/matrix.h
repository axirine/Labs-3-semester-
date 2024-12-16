
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Matrix {
public:
    Matrix();
    Matrix(int size);
    Matrix(const Matrix&);
    ~Matrix();

    void input();
    void output() const;
    Matrix add(const Matrix&) const;
    Matrix subtract(const Matrix&) const;
    Matrix multiply(const Matrix&) const;
    Matrix transpose() const;
    int determinant() const;

    Matrix& operator=(const Matrix&);

    friend ostream& operator<<(ostream& os, const Matrix& matrix);

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Matrix& matrix) {
        cout << "Enter elements for " << matrix.size << "x" << matrix.size << " matrix:" << endl;
        for (int i = 0; i < matrix.size; i++) {
            for (int j = 0; j < matrix.size; j++) {
                is >> matrix.data[i][j];
            }
        }
        return is;
    }

    // Метод для отладки: вывод матрицы
    friend ostream& operator<<(ostream& os, const Matrix& matrix) {
        for (int i = 0; i < matrix.size; i++) {
            for (int j = 0; j < matrix.size; j++) {
                os << matrix.data[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }

    int size;
    int** data;
private:
    void freeMemory();
};

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;

    Node(const T& newData = T()) : data(newData), next(this), prev(this) {}
};

template<typename T>
class List {
private:
    Node<T>* head;
    int size;
public:
    List() : head(nullptr), size(0) {}
    ~List() {
        deleteList();
    }

    void append(List<T>& list, const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (list.isEmpty()) {
            list.head = newNode;
        } else {
            Node<T>* tail = list.head->prev;
            tail->next = newNode;
            newNode->prev = tail;
            newNode->next = list.head;
            list.head->prev = newNode;
        }
        list.size++;
    }
    
    void deleteList() {
        if (!isEmpty()) {
            Node<T>* current = head;
            do {
                Node<T>* temp = current;
                current = current->next;
                delete temp;
            } while (current != head);
        }
        head = nullptr;
        size = 0;
    }

    void display(const List<T>& list) {
        if (list.isEmpty()) {
            cout << "List is empty \n";
            return;
        }
        Node<T>* current = list.head;
        int counter = 1;
        do {
            cout << counter << ") " << endl;
            cout << current->data << endl;
            current = current->next;
            counter++;
        } while (current != list.head);
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    Node<T>* findNode(const List<T>& list, int index) {
        if (index < 0 || index >= list.size) {
            cout << "Out of bounds \n";
            return nullptr;
        }
        Node<T>* current = list.head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current;
    }

    void insertNode(List<T>& list, int index, const T& newValue) {
        if (index < 0 || index > list.size) {
            cout << "Out of bounds\n";
            return;
        }
        Node<T>* newNode = new Node<T>(newValue);

        if (list.size == 0) {
            list.head = newNode;
            newNode->next = newNode->prev = newNode;
            cout << "Inserted first node. Head data: " << newNode->data << endl;
        } else if (index == 0) {
            Node<T>* tail = list.head->prev;
            newNode->next = list.head;
            newNode->prev = tail;
            tail->next = newNode;
            list.head->prev = newNode;
            list.head = newNode;
            cout << "Inserted node at the beginning: " << newNode->data << endl;
        } else if (index == list.size) {
            append(list, newValue);
            return;
        } else {
            Node<T>* current = findNode(list, index);
            Node<T>* previous = current->prev;
            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            current->prev = newNode;
            cout << "Inserted node in the middle. Data: " << newNode->data << endl;
        }

        list.size++;
        cout << "List size after insertion: " << list.size << endl;
    }

    void deleteNode(List<T>& list, int index) {
        if (index < 0 || index >= list.size) {
            cout << "Out of bounds \n";
            return;
        }
        Node<T>* removeNode = findNode(list, index);
        if (list.size == 1) {
            delete removeNode;
            list.head = nullptr;
            cout << "Node deleted \n";
        }
        else {
            Node<T>* prevNode = removeNode->prev;
            Node<T>* nextNode = removeNode->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            if (removeNode == list.head) {
                list.head = nextNode;
            }
            delete removeNode;
            cout << "Node deleted \n";
        }
        list.size--;
    }
};


#endif

