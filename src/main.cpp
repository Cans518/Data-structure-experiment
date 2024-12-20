#include "BinaryTree.hpp"
#include <cassert>

int main() {
    BinaryTree<int> tree;

    // 插入节点
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(18);

    // 测试先序遍历
    std::cout << "PerOrder: ";
    tree.preOrder(); // 输出: 10 5 3 7 15 12 18

    // 测试中序遍历
    std::cout << "InOrder: ";
    tree.inOrder(); // 输出: 3 5 7 10 12 15 18

    // 测试后序遍历
    std::cout << "PostOrder: ";
    tree.postOrder(); // 输出: 3 7 5 12 18 15 10

    return 0;
}
