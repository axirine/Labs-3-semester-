#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H

#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

template <typename T>
class CustomStack {
private:
    vector<T> stack;
public:
    CustomStack() = default;
    // Добавление элемента
    void push(const T& elem) {
        stack.push_back(elem);
    }

    // Удаление элемента
    void pop() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    // Получение верхнего элемента
    T top() const {
        if (!stack.empty()) {
            return stack.back();
        }
        throw runtime_error("Stack is empty");
    }

    // Проверка на пустоту
    bool empty() const {
        return stack.empty();
    }

    // Размер стека
    size_t size() const {
        return stack.size();
    }

    // Замер времени заполнения стека
    void measureFillTime(const vector<T>& elements) {
        auto start = high_resolution_clock::now();
        for (const T& elem : elements) {
            push(elem);
        }
        auto end = high_resolution_clock::now();
        cout << "Time to fill CustomStack: "
             << duration_cast<microseconds>(end - start).count() << " mcs" << endl;
    }

    // Замер времени добавления одного элемента
    void measurePushTime(const T& element) {
        auto start = high_resolution_clock::now();
        push(element);
        auto end = high_resolution_clock::now();
        cout << "Time to add element to CustomStack: "
             << duration_cast<microseconds>(end - start).count() << " mcs" << endl;
    }

    // Замер времени удаления элемента
    void measurePopTime() {
        auto start = high_resolution_clock::now();
        pop();
        auto end = high_resolution_clock::now();
        cout << "Time to remove an element from CustomStack: "
             << duration_cast<microseconds>(end - start).count() << " mcs" << endl;
    }
};

#endif // CUSTOM_STACK_H
