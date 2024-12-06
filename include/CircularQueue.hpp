// CircularQueue.hpp

#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP

#include <vector>
#include <stdexcept>
#include <utility>

template<typename T>
class CircularQueue {
public:
    explicit CircularQueue(size_t capacity);

    void enqueue(const T& value);
    void enqueue(T&& value);
    void dequeue();
    T frontElement() const;
    T backElement() const;
    bool isEmpty() const;
    bool isFull() const;
    size_t size() const;
    void clear();

private:
    std::vector<T> data; // 存储队列元素的数组
    size_t front;        // 队头位置
    size_t length;       // 队列中元素的个数
    size_t capacity;     // 队列的最大容量
};

/**
 * @brief 构造函数，初始化队列的最大容量。
 * @param capacity 队列的最大容量
 */
template<typename T>
CircularQueue<T>::CircularQueue(size_t capacity)
    : data(capacity), front(0), length(0), capacity(capacity) {}

/**
 * @brief 入队操作，将元素添加到队列末尾。(静态)
 * @param value 要添加的元素
 * @throws std::overflow_error 如果队列已满
 */
template<typename T>
void CircularQueue<T>::enqueue(const T& value) {
    if (isFull()) {
        throw std::overflow_error("队列已满，无法入队元素。");
    }
    size_t rear = (front + length) % capacity;
    data[rear] = value;
    ++length;
}

/**
 * @brief 入队操作，使用移动语义将元素添加到队列末尾。
 * @param value 要添加的元素
 * @throws std::overflow_error 如果队列已满
 */
template<typename T>
void CircularQueue<T>::enqueue(T&& value) {
    if (isFull()) {
        throw std::overflow_error("队列已满，无法入队元素。");
    }
    size_t rear = (front + length) % capacity;
    data[rear] = std::move(value);
    ++length;
}

/**
 * @brief 出队操作，移除队列头部的元素。
 * @throws std::underflow_error 如果队列为空
 */
template<typename T>
void CircularQueue<T>::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("队列为空，无法出队元素。");
    }
    front = (front + 1) % capacity;
    --length;
}

/**
 * @brief 获取队列头部的元素。
 * @return 队头元素
 * @throws std::underflow_error 如果队列为空
 */
template<typename T>
T CircularQueue<T>::frontElement() const {
    if (isEmpty()) {
        throw std::underflow_error("队列为空，无法获取队头元素。");
    }
    return data[front];
}

/**
 * @brief 获取队列尾部的元素。
 * @return 队尾元素
 * @throws std::underflow_error 如果队列为空
 */
template<typename T>
T CircularQueue<T>::backElement() const {
    if (isEmpty()) {
        throw std::underflow_error("队列为空，无法获取队尾元素。");
    }
    size_t rear = (front + length - 1) % capacity;
    return data[rear];
}

/**
 * @brief 检查队列是否为空。
 * @return 如果队列为空返回 true，否则返回 false
 */
template<typename T>
bool CircularQueue<T>::isEmpty() const {
    return length == 0;
}

/**
 * @brief 检查队列是否已满。
 * @return 如果队列已满返回 true，否则返回 false
 */
template<typename T>
bool CircularQueue<T>::isFull() const {
    return length == capacity;
}

/**
 * @brief 获取队列中元素的个数。
 * @return 队列中的元素个数
 */
template<typename T>
size_t CircularQueue<T>::size() const {
    return length;
}

/**
 * @brief 清空队列。
 */
template<typename T>
void CircularQueue<T>::clear() {
    front = 0;
    length = 0;
}

#endif // CIRCULARQUEUE_HPP
