#include <iostream>
#include "DoublyLinkedList.hpp"

int main() {
    // 创建一个空的双向链表
    DoublyLinkedList<int> list;

    // 打印空链表
    std::cout << "Initial empty list: ";
    list.print();

    // 插入元素
    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);
    list.insert(1, 15); // 在索引1处插入15

    // 打印插入后的链表
    std::cout << "List after insertions: ";
    list.print();

    // 查找元素
    int index = list.find(20);
    if (index != -1) {
        std::cout << "Element 20 found at index: " << index << std::endl;
    } else {
        std::cout << "Element 20 not found." << std::endl;
    }

    // 删除元素
    list.remove(1); // 删除索引1处的元素

    // 打印删除后的链表
    std::cout << "List after deletion: ";
    list.print();

    // 尝试查找已删除的元素
    index = list.find(15);
    if (index != -1) {
        std::cout << "Element 15 found at index: " << index << std::endl;
    } else {
        std::cout << "Element 15 not found." << std::endl;
    }

    return 0;
}
