#include "LinkedList.hpp"
#include "ArrayList.hpp"
#include <iostream>

// 比较函数用于 ArrayList 排序
bool ascendingComparator(const int& a, const int& b) {
    return a < b;
}

bool descendingComparator(const int& a, const int& b) {
    return a > b;
}

/**
 * @brief 测试 LinkedList 的功能
 */
void testLinkedList() {
    LinkedList<int> list;

    // 测试插入功能
    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(1, 15);
    list.print(); // 输出: 10 15 20

    // 测试删除功能
    list.remove(1);
    list.print(); // 输出: 10 20

    // 测试查找功能
    std::cout << "Index of 20: " << list.find(20) << std::endl; // 输出: 1
    std::cout << "Index of 15: " << list.find(15) << std::endl; // 输出: -1

    // 测试获取和设置功能
    std::cout << "Element at index 0: " << list.get(0) << std::endl; // 输出: 10
    list.set(0, 5);
    std::cout << "Element at index 0 after set: " << list.get(0) << std::endl; // 输出: 5

    // 测试反转功能
    list.reverse();
    list.print(); // 输出: 20 5

    // 测试从数组赋值功能
    int array[] = {1, 2, 3, 4, 5};
    list.assignFromArray(array, 5);
    list.print(); // 输出: 1 2 3 4 5

    // 测试排序功能
    list.insert(0, 10);
    list.sort();
    list.print(); // 输出: 1 2 3 4 5 10

    // 测试合并功能
    LinkedList<int> otherList;
    otherList.insert(0, 100);
    otherList.insert(1, 200);
    list.merge(otherList);
    list.print(); // 输出: 1 2 3 4 5 10 100 200

    // 测试清空功能
    list.clear();
    list.print(); // 输出: (空行)

    // 测试迭代器功能
    list.assignFromArray(array, 5);
    for (auto& item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl; // 输出: 1 2 3 4 5
}

/**
 * @brief 测试 ArrayList 的功能
 */
void testArrayList() {
    // 创建并初始化 ArrayList
    ArrayList<int> list = {5, 2, 9, 1, 5, 6};

    std::cout << "Initial list: ";
    list.print();

    // 测试插入功能
    list.insert(2, 10);
    std::cout << "After inserting 10 at index 2: ";
    list.print();

    // 测试删除功能
    list.remove(4);
    std::cout << "After removing element at index 4: ";
    list.print();

    // 测试查找功能
    int index = list.find(9);
    std::cout << "Index of element 9: " << index << std::endl;

    // 测试获取功能
    int value = list.get(3);
    std::cout << "Element at index 3: " << value << std::endl;

    // 测试设置功能
    list.set(3, 15);
    std::cout << "After setting index 3 to 15: ";
    list.print();

    // 测试大小和容量
    std::cout << "Size: " << list.size() << ", Capacity: " << list.capacity() << std::endl;

    // 测试排序（升序）
    list.sort(ascendingComparator);
    std::cout << "Sorted in ascending order: ";
    list.print();

    // 测试排序（降序）
    list.sort(descendingComparator);
    std::cout << "Sorted in descending order: ";
    list.print();

    // 测试反转功能
    list.reverse();
    std::cout << "After reversing: ";
    list.print();

    // 测试清空功能
    list.clear();
    std::cout << "After clearing: ";
    list.print();
    std::cout << "Size after clearing: " << list.size() << std::endl;

    // 测试从数组赋值功能
    int array[] = {3, 8, 7, 5};
    list.assignFromArray(array, 4);
    std::cout << "After assigning from array: ";
    list.print();

    // 测试缩减容量功能
    list.shrinkToFit();
    std::cout << "After shrinkToFit: Capacity: " << list.capacity() << std::endl;

    // 测试预留容量功能
    list.reserve(10);
    std::cout << "After reserving capacity 10: Capacity: " << list.capacity() << std::endl;
}

int main() {
    std::cout << "Testing LinkedList:" << std::endl;
    testLinkedList();

    std::cout << "\nTesting ArrayList:" << std::endl;
    testArrayList();

    return 0;
}
