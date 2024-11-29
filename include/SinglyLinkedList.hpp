#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include <iostream>
#include <stdexcept>
#include <functional> // For std::function

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    size_t length;

    Node* getNode(size_t index) const;
    void copyFrom(const SinglyLinkedList& other);
    void moveFrom(SinglyLinkedList&& other);
    void free();

public:
    SinglyLinkedList();
    ~SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList& other);
    SinglyLinkedList& operator=(const SinglyLinkedList& other);
    SinglyLinkedList(SinglyLinkedList&& other) noexcept;
    SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept;

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

    // Iterator support
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
};

/**
 * @brief 默认构造函数
 */
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), length(0) {}

/**
 * @brief 析构函数
 */
template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    free();
}

/**
 * @brief 拷贝构造函数
 * @param other 要拷贝的链表
 */
template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), length(0) {
    copyFrom(other);
}

/**
 * @brief 拷贝赋值运算符
 * @param other 要拷贝的链表
 * @return SinglyLinkedList& 链表自身引用
 */
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other) {
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
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList&& other) noexcept : head(nullptr), length(0) {
    moveFrom(std::move(other));
}

/**
 * @brief 移动赋值运算符
 * @param other 要移动的链表
 * @return SinglyLinkedList& 链表自身引用
 */
template <typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList&& other) noexcept {
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
void SinglyLinkedList<T>::insert(size_t index, const T& value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    Node* newNode = new Node(value);
    if (index == 0) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prevNode = getNode(index - 1);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
    ++length;
}

/**
 * @brief 移除指定位置的元素
 * @param index 要移除的元素位置
 */
template <typename T>
void SinglyLinkedList<T>::remove(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    Node* toDelete = nullptr;
    if (index == 0) {
        toDelete = head;
        head = head->next;
    } else {
        Node* prevNode = getNode(index - 1);
        toDelete = prevNode->next;
        prevNode->next = toDelete->next;
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
int SinglyLinkedList<T>::find(const T& value) const {
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
T SinglyLinkedList<T>::get(size_t index) const {
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
void SinglyLinkedList<T>::set(size_t index, const T& value) {
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
size_t SinglyLinkedList<T>::size() const {
    return length;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void SinglyLinkedList<T>::print() const {
    Node* current = head;
    if (length == 0) {
        std::cout << "Empty list" << std::endl;
        return;
    }
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
void SinglyLinkedList<T>::assignFromArray(const T* array, size_t array_size) {
    clear();
    for (size_t i = 0; i < array_size; ++i) {
        insert(length, array[i]);
    }
}

/**
 * @brief 反转链表
 */
template <typename T>
void SinglyLinkedList<T>::reverse() {
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
void SinglyLinkedList<T>::clear() {
    free();
    head = nullptr;
    length = 0;
}

/**
 * @brief 排序链表
 * @param comp 比较函数对象
 */
template <typename T>
void SinglyLinkedList<T>::sort(const std::function<bool(const T&, const T&)>& comp) {
    if (length < 2) return;

    for (size_t i = 0; i < length - 1; ++i) {
        Node* current = head;
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (!comp(current->data, current->next->data)) {
                std::swap(current->data, current->next->data);
            }
            current = current->next;
        }
    }
}

// 迭代器支持

/**
 * @brief 迭代器类
 */
template <typename T>
class SinglyLinkedList<T>::Iterator {
    private:
        Node* current;

    public:
        Iterator(Node* node) : current(node) {}

        T& operator*() const {
            return current->data;
        }

        T* operator->() const {
            return &(current->data);
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
};

/**
 * @brief 返回指向链表开头的迭代器
 * @return Iterator 迭代器
 */
template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const {
    return Iterator(head);
}

/**
 * @brief 返回指向链表末尾的迭代器
 * @return Iterator 迭代器
 */
template <typename T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const {
    return Iterator(nullptr);
}

// 私有辅助函数

/**
 * @brief 获取指定索引的节点
 * @param index 节点索引
 * @return Node* 节点指针
 */
template <typename T>
typename SinglyLinkedList<T>::Node* SinglyLinkedList<T>::getNode(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
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
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList& other) {
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
void SinglyLinkedList<T>::moveFrom(SinglyLinkedList&& other) {
    head = other.head;
    length = other.length;
    other.head = nullptr;
    other.length = 0;
}

/**
 * @brief 释放链表内存
 */
template <typename T>
void SinglyLinkedList<T>::free() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

#endif // SINGLYLINKEDLIST_HPP
