#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void insert(size_t index, const T& value);
    void remove(size_t index);
    int find(const T& value) const;
    T get(size_t index) const;
    void set(size_t index, const T& value);
    size_t size() const;
    void print() const;
    void assignFromArray(const T* array, size_t array_size);

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t length;

    Node* getNode(size_t index) const;
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), length(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

/**
 * @brief 在指定位置插入元素
 * 
 * @param index 插入位置
 * @param value 插入的元素
 */
template <typename T>
void LinkedList<T>::insert(size_t index, const T& value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    Node* newNode = new Node(value);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prev = getNode(index - 1);
        newNode->next = prev->next;
        prev->next = newNode;
    }
    ++length;
}

/**
 * @brief 移除指定位置的元素
 * 
 * @param index 要移除的元素位置
 */
template <typename T>
void LinkedList<T>::remove(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    Node* toDelete;
    if (index == 0) {
        toDelete = head;
        head = head->next;
    } else {
        Node* prev = getNode(index - 1);
        toDelete = prev->next;
        prev->next = toDelete->next;
    }
    delete toDelete;
    --length;
}

/**
 * @brief 查找元素，返回索引
 * 
 * @param value 要查找的元素
 * @return int 元素的索引，找不到返回-1
 */
template <typename T>
int LinkedList<T>::find(const T& value) const {
    Node* current = head;
    size_t index = 0;
    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        ++index;
    }
    return -1;
}

/**
 * @brief 获取指定位置的元素
 * 
 * @param index 元素位置
 * @return T 元素值
 */
template <typename T>
T LinkedList<T>::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return getNode(index)->data;
}

/**
 * @brief 设置指定位置的元素
 * 
 * @param index 元素位置
 * @param value 新的元素值
 */
template <typename T>
void LinkedList<T>::set(size_t index, const T& value) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    getNode(index)->data = value;
}

/**
 * @brief 返回当前元素数量
 * 
 * @return size_t 元素数量
 */
template <typename T>
size_t LinkedList<T>::size() const {
    return length;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void LinkedList<T>::print() const {
    Node* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

/**
 * @brief 从数组赋值
 * 
 * @param array 源数组
 * @param array_size 数组大小
 */
template <typename T>
void LinkedList<T>::assignFromArray(const T* array, size_t array_size) {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    length = 0;

    for (size_t i = 0; i < array_size; ++i) {
        insert(length, array[i]);
    }
}

/**
 * @brief 获取指定索引的节点
 * 
 * @param index 节点索引
 * @return Node* 节点指针
 */
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNode(size_t index) const {
    Node* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

#endif // LINKEDLIST_HPP
