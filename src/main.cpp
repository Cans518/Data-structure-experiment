#include "ArrayList.hpp"
#include "LinkedList.hpp"
#include <iostream>

void printError(const std::string& message) {
    // ANSI escape code for red text
    std::cout << "\033[31m" << "Error: " << message << "\033[0m" << std::endl;
}

void testArrayList() {
    std::cout << "===== Testing ArrayList =====" << std::endl;
    ArrayList<int> arrayList;

    // 测试越界访问
    try {
        std::cout << "Trying to access element at index 0 (out of bounds)..." << std::endl;
        arrayList.get(0);
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试插入
    try {
        std::cout << "Inserting elements 10, 20, 30..." << std::endl;
        arrayList.insert(0, 10);
        arrayList.insert(1, 20);
        arrayList.insert(2, 30);
        arrayList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试删除
    try {
        std::cout << "Removing element at index 1..." << std::endl;
        arrayList.remove(1);
        arrayList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试查找
    try {
        std::cout << "Finding index of element 30..." << std::endl;
        int index = arrayList.find(30);
        std::cout << "Index of 30: " << index << std::endl;
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试获取和设置
    try {
        std::cout << "Getting element at index 1: " << arrayList.get(1) << std::endl;
        std::cout << "Setting element at index 1 to 99..." << std::endl;
        arrayList.set(1, 99);
        arrayList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试从数组赋值
    try {
        int array[] = {1, 2, 3, 4, 5};
        std::cout << "Assigning from array {1, 2, 3, 4, 5}..." << std::endl;
        arrayList.assignFromArray(array, 5);
        arrayList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

void testLinkedList() {
    std::cout << "\n===== Testing LinkedList =====" << std::endl;
    LinkedList<int> linkedList;

    // 测试越界访问
    try {
        std::cout << "Trying to access element at index 0 (out of bounds)..." << std::endl;
        linkedList.get(0);
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试插入
    try {
        std::cout << "Inserting elements 10, 20, 30..." << std::endl;
        linkedList.insert(0, 10);
        linkedList.insert(1, 20);
        linkedList.insert(2, 30);
        linkedList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试删除
    try {
        std::cout << "Removing element at index 1..." << std::endl;
        linkedList.remove(1);
        linkedList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试查找
    try {
        std::cout << "Finding index of element 30..." << std::endl;
        int index = linkedList.find(30);
        std::cout << "Index of 30: " << index << std::endl;
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试获取和设置
    try {
        std::cout << "Getting element at index 1: " << linkedList.get(1) << std::endl;
        std::cout << "Setting element at index 1 to 99..." << std::endl;
        linkedList.set(1, 99);
        linkedList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }

    // 测试从数组赋值
    try {
        int array[] = {1, 2, 3, 4, 5};
        std::cout << "Assigning from array {1, 2, 3, 4, 5}..." << std::endl;
        linkedList.assignFromArray(array, 5);
        linkedList.print();
    } catch (const std::exception& e) {
        printError(e.what());
    }
}

int main() {
    // 测试 ArrayList
    testArrayList();

    // 测试 LinkedList
    testLinkedList();

    return 0;
}
