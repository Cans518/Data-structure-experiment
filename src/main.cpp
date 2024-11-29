#include <iostream>
#include "LinkedList.hpp"  // 确保包含正确的头文件路径
#include "DoublyLinkedList.hpp"
#include "Polynomial.hpp"

int main() {
    // ****************** 单向链表测试 ******************
    std::cout << "********** Singly Linked List Test **********" << std::endl;
    LinkedList<int> list;

    // 插入一些元素
    list.insert(0, 10);
    list.insert(1, 20);
    list.insert(2, 30);
    list.insert(3, 20);
    list.insert(4, 40);

    // 测试定位函数
    auto node = list.locate(2); // 寻找索引为2的节点
    if (node) {
        std::cout << "Node at index 2: " << node->data << " Node location: " << node << std::endl;
    } else {
        std::cout << "Node at index 2 not found." << std::endl;
    }

    node = list.locate(5); // 寻找不存在的索引
    if (node) {
        std::cout << "Node at index 5: " << node->data << " Node location: " << node << std::endl;
    } else {
        std::cout << "Node at index 5 not found." << std::endl; // 应输出: Node at index 5 not found.
    }

    // 测试统计函数
    size_t count = list.count(20); // 统计值为20的元素个数
    std::cout << "Count of 20: " << count << std::endl; // 应输出: 2

    count = list.count(50); // 统计不存在的值
    std::cout << "Count of 50: " << count << std::endl; // 应输出: 0

    // ****************** 双向链表测试 ******************
    std::cout << "\n**********  Doubly Linked List Test **********" << std::endl;
    DoublyLinkedList<int> dlist;

    // 打印空链表
    std::cout << "Initial empty list: ";
    dlist.print();

    // 插入元素
    dlist.insert(0, 10);
    dlist.insert(1, 20);
    dlist.insert(2, 30);
    dlist.insert(1, 15); // 在索引1处插入15

    // 打印插入后的链表
    std::cout << "List after insertions: ";
    dlist.print();

    // 查找元素
    int index = dlist.find(20);
    if (index != -1) {
        std::cout << "Element 20 found at index: " << index << std::endl;
    } else {
        std::cout << "Element 20 not found." << std::endl;
    }

    // 删除元素
    dlist.remove(1); // 删除索引1处的元素

    // 打印删除后的链表
    std::cout << "List after deletion: ";
    dlist.print();

    // 尝试查找已删除的元素
    index = dlist.find(15);
    if (index != -1) {
        std::cout << "Element 15 found at index: " << index << std::endl;
    } else {
        std::cout << "Element 15 not found." << std::endl;
    }

    // ****************** 多项式测试 ******************
    std::cout << "\n**********  Polynomial Test **********" << std::endl;
    Polynomial p1 = {3, 0, 2}; // 3 + 0*x + 2*x^2
    Polynomial p2 = {1, 4, 0, 5}; // 1 + 4*x + 0*x^2 + 5*x^3

    double value1 = p1.Calc(2.0);
    double value2 = p2.Calc(2.0);

    std::cout << "p1 evaluated at x = 2: " << value1 << std::endl; 
    std::cout << "p2 evaluated at x = 2: " << value2 << std::endl; 

    Polynomial p3 = p1 + p2;

    std::cout << "p1 + p2: ";
    p3.print(); 
    double value3 = p3.Calc(2.0);
    std::cout << "p3 evaluated at x = 2: " << value3 << std::endl;

    return 0;
}
