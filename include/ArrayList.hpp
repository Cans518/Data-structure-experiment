#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
class ArrayList {
public:
    ArrayList(size_t initial_capacity = 10);
    ~ArrayList();

    void insert(size_t index, const T& value);
    void remove(size_t index);
    int find(const T& value) const;
    T get(size_t index) const;
    void set(size_t index, const T& value);
    size_t size() const;
    void print() const;
    void assignFromArray(const T* array, size_t array_size);

private:
    T* data;
    size_t current_capacity;
    size_t length;

    void ensure_capacity(size_t min_capacity);
};

template <typename T>
ArrayList<T>::ArrayList(size_t initial_capacity)
    : current_capacity(initial_capacity), length(0) {
    data = new T[current_capacity];
}

template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

/**
 * @brief 确保容量足够
 * 
 * @param min_capacity 最小需要的容量
 */
template <typename T>
void ArrayList<T>::ensure_capacity(size_t min_capacity) {
    if (min_capacity > current_capacity) {
        size_t new_capacity = current_capacity * 2;
        if (new_capacity < min_capacity) {
            new_capacity = min_capacity;
        }
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        current_capacity = new_capacity;
    }
}

/**
 * @brief 插入元素到指定位置
 * 
 * @param index 插入位置
 * @param value 插入的元素
 */
template <typename T>
void ArrayList<T>::insert(size_t index, const T& value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    ensure_capacity(length + 1);
    for (size_t i = length; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    ++length;
}

/**
 * @brief 移除指定位置的元素
 * 
 * @param index 要移除的元素位置
 */
template <typename T>
void ArrayList<T>::remove(size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    --length;
}

/**
 * @brief 查找元素，返回索引
 * 
 * @param value 要查找的元素
 * @return int 元素的索引，找不到返回-1
 */
template <typename T>
int ArrayList<T>::find(const T& value) const {
    for (size_t i = 0; i < length; ++i) {
        if (data[i] == value) {
            return i;
        }
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
T ArrayList<T>::get(size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

/**
 * @brief 设置指定位置的元素
 * 
 * @param index 元素位置
 * @param value 新的元素值
 */
template <typename T>
void ArrayList<T>::set(size_t index, const T& value) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

/**
 * @brief 返回当前元素数量
 * 
 * @return size_t 元素数量
 */
template <typename T>
size_t ArrayList<T>::size() const {
    return length;
}

/**
 * @brief 打印所有元素
 */
template <typename T>
void ArrayList<T>::print() const {
    for (size_t i = 0; i < length; ++i) {
        std::cout << data[i] << " ";
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
void ArrayList<T>::assignFromArray(const T* array, size_t array_size) {
    ensure_capacity(array_size);
    for (size_t i = 0; i < array_size; ++i) {
        data[i] = array[i];
    }
    length = array_size;
}

#endif // ARRAYLIST_HPP
