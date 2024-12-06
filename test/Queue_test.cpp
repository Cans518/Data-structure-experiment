#include <iostream>
#include "CircularQueue.hpp"

int main() {
    try {
        CircularQueue<int> queue(3);

        // 测试入队操作
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);

        // 尝试添加多于容量的元素
        try {
            queue.enqueue(4);
        } catch (const std::overflow_error& e) {
            std::cout << "Expected overflow error: " << e.what() << std::endl;
        }

        // 测试队列状态
        std::cout << "Front element: " << queue.frontElement() << std::endl; // 应输出 1
        std::cout << "Back element: " << queue.backElement() << std::endl;   // 应输出 3
        std::cout << "Queue size: " << queue.size() << std::endl;            // 应输出 3

        // 测试出队操作
        queue.dequeue();
        std::cout << "Front element after dequeue: " << queue.frontElement() << std::endl; // 应输出 2

        queue.enqueue(4);
        std::cout << "Back element after enqueue: " << queue.backElement() << std::endl;   // 应输出 4

        // 清空队列
        queue.clear();
        std::cout << "Queue size after clear: " << queue.size() << std::endl; // 应输出 0

        // 尝试从空队列中出队
        try {
            queue.dequeue();
        } catch (const std::underflow_error& e) {
            std::cout << "Expected underflow error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }

    return 0;
}
