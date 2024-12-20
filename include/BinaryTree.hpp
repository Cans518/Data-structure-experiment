#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <memory>

template <typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        Node(T val);
    };

    std::shared_ptr<Node> root;

    void preOrderTraversal(const std::shared_ptr<Node>& node) const;
    void inOrderTraversal(const std::shared_ptr<Node>& node) const;
    void postOrderTraversal(const std::shared_ptr<Node>& node) const;

public:
    BinaryTree();
    void insert(const T& value);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
};

// Node 构造函数
template <typename T>
BinaryTree<T>::Node::Node(T val) : data(val), left(nullptr), right(nullptr) {}

/**
 * @brief 构造一个空的二叉树
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root(nullptr) {}

/**
 * @brief 插入一个值到二叉树中
 * 
 * @param value 要插入的值
 */
template <typename T>
void BinaryTree<T>::insert(const T& value) {
    if (!root) {
        root = std::make_shared<Node>(value);
    } else {
        auto current = root;
        while (true) {
            if (value < current->data) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = std::make_shared<Node>(value);
                    break;
                }
            } else {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = std::make_shared<Node>(value);
                    break;
                }
            }
        }
    }
}

/**
 * @brief 先序遍历的递归实现
 * 
 * @param node 当前遍历的节点
 */
template <typename T>
void BinaryTree<T>::preOrderTraversal(const std::shared_ptr<Node>& node) const {
    if (!node) return;
    std::cout << node->data << " ";
    preOrderTraversal(node->left);
    preOrderTraversal(node->right);
}

/**
 * @brief 先序遍历二叉树并输出
 */
template <typename T>
void BinaryTree<T>::preOrder() const {
    preOrderTraversal(root);
    std::cout << std::endl;
}

/**
 * @brief 中序遍历的递归实现
 * 
 * @param node 当前遍历的节点
 */
template <typename T>
void BinaryTree<T>::inOrderTraversal(const std::shared_ptr<Node>& node) const {
    if (!node) return;
    inOrderTraversal(node->left);
    std::cout << node->data << " ";
    inOrderTraversal(node->right);
}

/**
 * @brief 中序遍历二叉树并输出
 */
template <typename T>
void BinaryTree<T>::inOrder() const {
    inOrderTraversal(root);
    std::cout << std::endl;
}

/**
 * @brief 后序遍历的递归实现
 * 
 * @param node 当前遍历的节点
 */
template <typename T>
void BinaryTree<T>::postOrderTraversal(const std::shared_ptr<Node>& node) const {
    if (!node) return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    std::cout << node->data << " ";
}

/**
 * @brief 后序遍历二叉树并输出
 */
template <typename T>
void BinaryTree<T>::postOrder() const {
    postOrderTraversal(root);
    std::cout << std::endl;
}

#endif // BINARY_TREE_HPP
