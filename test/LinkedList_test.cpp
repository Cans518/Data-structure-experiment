#include "LinkedList.hpp"
#include <iostream>

int main() {
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

    return 0;
}
