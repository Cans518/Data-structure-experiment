#ifndef ACKERMANN_HPP
#define ACKERMANN_HPP

#include <iostream>
#include <stack>
#include <utility>
#include <stdexcept>

namespace Ackermann {
/**
 * @brief 计算 Ackermann 函数。
 * 
 * @param m 非负整数参数 m。
 * @param n 非负整数参数 n。
 * @param useRecursive 如果为 true，则使用递归实现；否则使用非递归实现。
 * @param debug 如果为 true，则输出每一步的运算过程。
 * @return int Ackermann 函数的结果。
 * @throws std::invalid_argument 如果 m 或 n 为负。
 */
int calculate(int m, int n, bool useRecursive = false, bool debug = false) {
    if (m < 0 || n < 0) {
        throw std::invalid_argument("Arguments m and n must be non-negative integers.");
    }

    if (useRecursive) {
        // Recursive implementation
        if (debug) {
            std::cout << "ackermann(" << m << ", " << n << ")" << std::endl;
        }
        if (m == 0) {
            return n + 1;
        } else if (m > 0 && n == 0) {
            return calculate(m - 1, 1, true, debug);
        } else {
            return calculate(m - 1, calculate(m, n - 1, true, debug), true, debug);
        }
    } else {
        // Non-recursive implementation
        struct Ack {
            int m_, n_;
            Ack(int m, int n) : m_(m), n_(n) {}
        };

        std::stack<Ack> s;
        s.push(Ack(m, n));

        int ret = -1;

        while (!s.empty()) {
            Ack Node = s.top();
            s.pop();

            if (debug) {
                std::cout << "ackermann(" << Node.m_ << ", " << Node.n_ << ")" << std::endl;
            }

            if (Node.m_ == 0) {
                ret = Node.n_ + 1;
                if (s.empty()) {
                    break;
                }
                Node = s.top();
                s.pop();
                Node.n_ = ret;
                s.push(Node);
            } else if (Node.n_ == 0) {
                s.push(Ack(Node.m_ - 1, 1));
            } else {
                s.push(Ack(Node.m_ - 1, -1));
                s.push(Ack(Node.m_, Node.n_ - 1));
            }
        }
        return ret;
    }
}

}

#endif // ACKERMANN_HPP
