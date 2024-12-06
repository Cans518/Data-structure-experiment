#ifndef EXPRESSIONEVALUATOR_HPP
#define EXPRESSIONEVALUATOR_HPP

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include "CircularQueue.hpp"

class ExpressionEvaluator {
public:
    ExpressionEvaluator(bool debug = false) : debug(debug) {}
    double evaluate(const std::string& infix);
    bool debug;

private:
    int precedence(char op);
    double applyOp(double a, double b, char op);
    bool isOperator(char c);
    CircularQueue<std::string> infixToPostfix(const std::string& infix);
    double evaluatePostfix(CircularQueue<std::string>& postfix);
};

/**
* @brief 获取运算符的优先级。
* @param op 运算符字符。
* @return 运算符的优先级。
*/
int ExpressionEvaluator::precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/**
* @brief 对两个操作数应用运算符。
* @param a 左操作数。
* @param b 右操作数。
* @param op 要应用的运算符。
* @return 运算结果。
*/
double ExpressionEvaluator::applyOp(double a, double b, char op) {
    if (debug) {
        std::cout << "Applying operation: " << a << " " << op << " " << b << std::endl;
    }
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: throw std::invalid_argument("Invalid operator");
    }
}

/**
* @brief 检查字符是否为运算符。
* @param c 要检查的字符。
* @return 如果是运算符返回 true，否则返回 false。
*/
bool ExpressionEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
* @brief 将中缀表达式转换为后缀表达式。
* @param infix 中缀表达式。
* @return 包含后缀表达式的 CircularQueue。
*/
CircularQueue<std::string> ExpressionEvaluator::infixToPostfix(const std::string& infix) {
    std::stack<char> operators;
    CircularQueue<std::string> postfix(infix.length() * 2);
    
    for (size_t i = 0; i < infix.length(); ++i) {
        char token = infix[i];
        
        if (std::isspace(token)) {
            continue;
        }
        
        if (std::isdigit(token) || token == '.') {
            std::string number;
            number += token;
            while (++i < infix.length() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                number += infix[i];
            }
            postfix.enqueue(number);
            if (debug) {
                std::cout << "Enqueued number: " << number << std::endl;
            }
            --i;
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix.enqueue(std::string(1, operators.top()));
                if (debug) {
                    std::cout << "Enqueued operator: " << operators.top() << std::endl;
                }
                operators.pop();
            }
            if (!operators.empty()) operators.pop();
        } else if (isOperator(token)) {
            // Check for unary minus
            if (token == '-' && (i + 1 < infix.length()) && std::isdigit(infix[i + 1]) && (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1]))) {
                std::string number = "-";
                while (++i < infix.length() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                    number += infix[i];
                }
                postfix.enqueue(number);
                if (debug) {
                    std::cout << "Enqueued number: " << number << std::endl;
                }
                --i;
            } else {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    postfix.enqueue(std::string(1, operators.top()));
                    if (debug) {
                        std::cout << "Enqueued operator: " << operators.top() << std::endl;
                    }
                    operators.pop();
                }
                operators.push(token);
            }
        } else {
            throw std::invalid_argument("Invalid character in expression");
        }
    }
    
    while (!operators.empty()) {
        postfix.enqueue(std::string(1, operators.top()));
        if (debug) {
            std::cout << "Enqueued operator: " << operators.top() << std::endl;
        }
        operators.pop();
    }
    
    return postfix;
}

/**
* @brief 计算后缀表达式。
* @param postfix 包含后缀表达式的 CircularQueue。
* @return 计算结果。
*/
double ExpressionEvaluator::evaluatePostfix(CircularQueue<std::string>& postfix) {
    std::stack<double> operands;
    
    while (!postfix.isEmpty()) {
        std::string token = postfix.frontElement();
        postfix.dequeue();

        try {
            if ((std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1)) && token.find_first_not_of("0123456789.-") == std::string::npos) {
                operands.push(std::stod(token));
                if (debug) {
                    std::cout << "Pushed operand: " << token << std::endl;
                }
            } else if (isOperator(token[0])) {
                if (operands.size() < 2) throw std::runtime_error("Invalid expression");
                double right = operands.top(); operands.pop();
                double left = operands.top(); operands.pop();
                double result = applyOp(left, right, token[0]);
                operands.push(result);
                if (debug) {
                    std::cout << "Pushed result: " << result << std::endl;
                }
            } else {
                throw std::invalid_argument("Invalid token in expression");
            }
        } catch (const std::exception& e) {
            std::cerr << "Error processing token: " << token << " - " << e.what() << std::endl;
            throw;
        }
    }
    
    if (operands.size() != 1) throw std::runtime_error("Invalid expression");
    
    return operands.top();
}

/**
* @brief 计算中缀表达式。
* @param infix 要计算的中缀表达式。
* @return 计算结果。
*/
double ExpressionEvaluator::evaluate(const std::string& infix) {
    CircularQueue<std::string> postfix = infixToPostfix(infix);
    return evaluatePostfix(postfix);
}

#endif // EXPRESSIONEVALUATOR_HPP
