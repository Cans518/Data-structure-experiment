#include <iostream>
#include "LinkedList.hpp" // 确保包含正确的头文件路径

int main() {
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
        std::cout << "Node at index 2: " << node->data << "Node at index 2 loaction: " << node << std::endl;
    } else {
        std::cout << "Node at index 2 not found." << std::endl;
    }

    node = list.locate(5); // 寻找不存在的索引
    if (node) {
        std::cout << "Node at index 5: " << node->data << "Node at index 5 loaction: " << node << std::endl;
    } else {
        std::cout << "Node at index 5 not found." << std::endl; // 应输出: Node at index 5 not found.
    }

    // 测试统计函数
    size_t count = list.count(20); // 统计值为20的元素个数
    std::cout << "Count of 20: " << count << std::endl; // 应输出: 2

    count = list.count(50); // 统计不存在的值
    std::cout << "Count of 50: " << count << std::endl; // 应输出: 0

    return 0;
}
