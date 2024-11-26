#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <stdexcept>
#include <utility> // For std::swap
#include <functional> // For std::function

template <typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;

    void insert(size_t index, const T& value);
    void remove(size_t index);
    int find(const T& value) const;
    T get(size_t index) const;
    void set(size_t index, const T& value);
    size_t size() const;
    void print() const;
    void assignFromArray(const T* array, size_t array_size);
    void reverse();
    void clear();
    void sort(const std::function<bool(const T&, const T&)>& comp = std::less<T>());
    void merge(LinkedList& other);

    // Iterator support
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t length;

    Node* getNode(size_t index) const;
    void copyFrom(const LinkedList& other);
    void moveFrom(LinkedList&& other);
    void free();
};

/**
 * @brief 默认构造函数
 */
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), length(0) {}

/**
 * @brief 析构函数
 */
template <typename T>
LinkedList<T>::~LinkedList() {
    free();
}

/**
 * @brief 拷贝构造函数
 * @param other 要拷贝的链表
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), length(0) {
    copyFrom(other);
}

/**
 * @brief 拷贝赋值运算符
 * @param other 要拷贝的链表
 * @return LinkedList& 链表自身引用
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

/**
 * @brief 移动构造函数
 * @param other 要移动的链表
 */
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept : head(nullptr), length(0) {
    moveFrom(std::move(other));
}

/**
 * @brief 移动赋值运算符
 * @param other 要移动的链表
 * @return LinkedList& 链表自身引用
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

/**
 * @brief 在指定位置插入元素
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
 * @param value 要查找的元素
 * @return int 元素的索引，找不到返回-1
 */
template <typename T>
int LinkedList<T>::find(const T& value) const {
    Node* current = head;
    size_t index = 0;
    while (current != nullptr) {
        if (current->data == value) {
            return static_cast<int>(index);
        }
        current = current->next;
        ++index;
    }
    return -1;
}

/**
 * @brief 获取指定位置的元素
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
 * @param array 源数组
 * @param array_size 数组大小
 */
template <typename T>
void LinkedList<T>::assignFromArray(const T* array, size_t array_size) {
    clear();
    for (size_t i = 0; i < array_size; ++i) {
        insert(length, array[i]);
    }
}

/**
 * @brief 反转链表
 */
template <typename T>
void LinkedList<T>::reverse() {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

/**
 * @brief 清空链表
 */
template <typename T>
void LinkedList<T>::clear() {
    free();
    head = nullptr;
    length = 0;
}

/**
 * @brief 排序链表
 * @param comp 比较函数对象
 */
template <typename T>
void LinkedList<T>::sort(const std::function<bool(const T&, const T&)>& comp) {
    if (length < 2) return;

    for (size_t i = 0; i < length - 1; ++i) {
        Node* current = head;
        Node* next = head->next;
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (!comp(current->data, next->data)) {
                std::swap(current->data, next->data);
            }
            current = next;
            next = next->next;
        }
    }
}

/**
 * @brief 合并另一个链表
 * @param other 要合并的链表
 */
template <typename T>
void LinkedList<T>::merge(LinkedList& other) {
    if (this == &other) return;

    if (!head) {
        head = other.head;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = other.head;
    }
    length += other.length;
    other.head = nullptr;
    other.length = 0;
}

// 迭代器支持

/**
 * @brief 迭代器类
 */
template <typename T>
class LinkedList<T>::Iterator {
public:
    Iterator(Node* node) : current(node) {}

    T& operator*() const { return current->data; }
    Iterator& operator++() { 
        current = current->next; 
        return *this; 
    }
    bool operator!=(const Iterator& other) const { return current != other.current; }

private:
    Node* current;
};

/**
 * @brief 返回指向链表开头的迭代器
 * @return Iterator 迭代器
 */
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const {
    return Iterator(head);
}

/**
 * @brief 返回指向链表末尾的迭代器
 * @return Iterator 迭代器
 */
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() const {
    return Iterator(nullptr);
}

// 私有辅助函数

/**
 * @brief 获取指定索引的节点
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

/**
 * @brief 从另一个链表复制数据
 * @param other 源链表
 */
template <typename T>
void LinkedList<T>::copyFrom(const LinkedList& other) {
    Node* current = other.head;
    while (current != nullptr) {
        insert(length, current->data);
        current = current->next;
    }
}

/**
 * @brief 从另一个链表移动数据
 * @param other 源链表
 */
template <typename T>
void LinkedList<T>::moveFrom(LinkedList&& other) {
    head = other.head;
    length = other.length;
    other.head = nullptr;
    other.length = 0;
}

/**
 * @brief 释放链表内存
 */
template <typename T>
void LinkedList<T>::free() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

#endif // LINKEDLIST_HPP
