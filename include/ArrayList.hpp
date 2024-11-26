#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>
#include <stdexcept>
#include <functional> 
#include <initializer_list>

template <typename T>
class ArrayList {
public:
    ArrayList(size_t initial_capacity = 10);
    ArrayList(std::initializer_list<T> init);
    ~ArrayList();

    ArrayList(const ArrayList& other);
    ArrayList& operator=(const ArrayList& other);

    ArrayList(ArrayList&& other) noexcept;
    ArrayList& operator=(ArrayList&& other) noexcept;

    void insert(size_t index, const T& value);
    void remove(size_t index);
    int find(const T& value) const;
    T get(size_t index) const;
    void set(size_t index, const T& value);
    size_t size() const;
    size_t capacity() const;
    void print() const;
    void assignFromArray(const T* array, size_t array_size);
    void clear();
    void shrinkToFit();
    void reserve(size_t new_capacity);
    void reverse();
    void sort(const std::function<bool(const T&, const T&)>& comparator);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;

private:
    T* data;
    size_t current_capacity;
    size_t length;

    void ensure_capacity(size_t min_capacity);
    void copy_from(const ArrayList& other);
};

template <typename T>
ArrayList<T>::ArrayList(size_t initial_capacity)
    : current_capacity(initial_capacity), length(0) {
    data = new T[current_capacity];
}

/**
 * @brief 使用初始化列表进行初始化
 * @param init 初始化列表
 */
template <typename T>
ArrayList<T>::ArrayList(std::initializer_list<T> init)
    : current_capacity(init.size()), length(init.size()) {
    data = new T[current_capacity];
    size_t i = 0;
    for (const T& item : init) {
        data[i++] = item;
    }
}

/**
 * @brief 析构函数：释放动态分配的内存
 */
template <typename T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

/**
 * @brief 拷贝构造函数
 * @param other 另一个ArrayList对象
 */
template <typename T>
ArrayList<T>::ArrayList(const ArrayList& other) {
    copy_from(other);
}

/**
 * @brief 拷贝赋值运算符
 * @param other 另一个ArrayList对象
 * @return 当前对象的引用
 */
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
    if (this != &other) {
        delete[] data;
        copy_from(other);
    }
    return *this;
}

/**
 * @brief 移动构造函数
 * @param other 另一个ArrayList对象
 */
template <typename T>
ArrayList<T>::ArrayList(ArrayList&& other) noexcept
    : data(other.data), current_capacity(other.current_capacity), length(other.length) {
    other.data = nullptr;
    other.length = 0;
    other.current_capacity = 0;
}

/**
 * @brief 移动赋值运算符
 * @param other 另一个ArrayList对象
 * @return 当前对象的引用
 */
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        current_capacity = other.current_capacity;
        length = other.length;
        other.data = nullptr;
        other.length = 0;
        other.current_capacity = 0;
    }
    return *this;
}

/**
 * @brief 从另一个ArrayList复制数据
 * @param other 另一个ArrayList对象
 */
template <typename T>
void ArrayList<T>::copy_from(const ArrayList& other) {
    current_capacity = other.current_capacity;
    length = other.length;
    data = new T[current_capacity];
    for (size_t i = 0; i < length; ++i) {
        data[i] = other.data[i];
    }
}

/**
 * @brief 确保容量足够
 * @param min_capacity 最小需要的容量
 */
template <typename T>
void ArrayList<T>::ensure_capacity(size_t min_capacity) {
    if (min_capacity > current_capacity) {
        reserve(min_capacity);
    }
}

/**
 * @brief 预留指定容量的空间
 * @param new_capacity 新的容量
 */
template <typename T>
void ArrayList<T>::reserve(size_t new_capacity) {
    if (new_capacity > current_capacity) {
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
 * @param value 要查找的元素
 * @return 元素的索引，找不到返回-1
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
 * @param index 元素位置
 * @return 元素值
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
 * @return 元素数量
 */
template <typename T>
size_t ArrayList<T>::size() const {
    return length;
}

/**
 * @brief 返回当前容量
 * @return 容量大小
 */
template <typename T>
size_t ArrayList<T>::capacity() const {
    return current_capacity;
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

/**
 * @brief 清空列表
 */
template <typename T>
void ArrayList<T>::clear() {
    length = 0;
}

/**
 * @brief 缩小容量以适应当前大小
 */
template <typename T>
void ArrayList<T>::shrinkToFit() {
    if (length < current_capacity) {
        T* new_data = new T[length];
        for (size_t i = 0; i < length; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        current_capacity = length;
    }
}

/**
 * @brief 反转列表中的元素
 */
template <typename T>
void ArrayList<T>::reverse() {
    for (size_t i = 0; i < length / 2; ++i) {
        std::swap(data[i], data[length - 1 - i]);
    }
}

/**
 * @brief 重载[]运算符用于元素访问
 * @param index 元素位置
 * @return 元素引用
 */
template <typename T>
T& ArrayList<T>::operator[](size_t index) {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

/**
 * @brief 重载[]运算符用于元素访问（常量版本）
 * @param index 元素位置
 * @return 元素常量引用
 */
template <typename T>
const T& ArrayList<T>::operator[](size_t index) const {
    if (index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

/**
 * @brief 迭代器支持
 * @return 指向第一个元素的迭代器
 */
template <typename T>
T* ArrayList<T>::begin() {
    return data;
}

/**
 * @brief 迭代器支持
 * @return 指向超尾元素的迭代器
 */
template <typename T>
T* ArrayList<T>::end() {
    return data + length;
}

/**
 * @brief 迭代器支持（常量版本）
 * @return 指向第一个元素的常量迭代器
 */
template <typename T>
const T* ArrayList<T>::begin() const {
    return data;
}

/**
 * @brief 迭代器支持（常量版本）
 * @return 指向超尾元素的常量迭代器
 */
template <typename T>
const T* ArrayList<T>::end() const {
    return data + length;
}

/**
 * @brief 使用自定义比较器对列表进行排序
 * @param comparator 比较两个元素的函数对象
 */
template <typename T>
void ArrayList<T>::sort(const std::function<bool(const T&, const T&)>& comparator) {
    for (size_t i = 0; i < length - 1; ++i) {
        for (size_t j = 0; j < length - i - 1; ++j) {
            if (comparator(data[j + 1], data[j])) {
                std::swap(data[j], data[j + 1]);
            }
        }
    }
}

#endif // ARRAYLIST_HPP