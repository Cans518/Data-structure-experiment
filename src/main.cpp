#include <iostream>
#include <vector>
#include <string>
#include <io.h>
#include <fcntl.h>
#include "ExpressionEvaluator.hpp"
#include "CircularQueue.hpp"

void runExpressionEvaluatorTests() {
    ExpressionEvaluator evaluator;
    std::vector<std::pair<std::string, double>> tests = {
        {"3 + 5 * ( 2 - (8 + 2) ) + 12 / 4 - 6 + 7 * (8 - (3 + 2))", -19},
        {"10 + 2 * 6", 22},
        {"100 * 2 + 12", 212},
        {"100 * ( 2 + 12 )", 1400},
        {"100 * ( 2 + 12 ) / 14", 100},
        {"3.5 + 2.1 * (4 - 2) / 2", 5.6}
    };

    for (const auto& test : tests) {
        try {
            double result = evaluator.evaluate(test.first);
            if (result == test.second) {
                std::cout << "Test passed for expression: " << test.first << std::endl;
            } else {
                std::cout << "Test failed for expression: " << test.first 
                          << ". Expected: " << test.second 
                          << ", Got: " << result << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error evaluating expression: " << test.first 
                      << ". Error: " << e.what() << std::endl;
        }
    }
}

void runCircularQueueTests() {
    try {
        CircularQueue<int> queue(3);

        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);

        try {
            queue.enqueue(4);
        } catch (const std::overflow_error& e) {
            std::cout << "Expected overflow error: " << e.what() << std::endl;
        }

        std::cout << "Front element: " << queue.frontElement() << std::endl;
        std::cout << "Back element: " << queue.backElement() << std::endl;
        std::cout << "Queue size: " << queue.size() << std::endl;

        queue.dequeue();
        std::cout << "Front element after dequeue: " << queue.frontElement() << std::endl;

        queue.enqueue(4);
        std::cout << "Back element after enqueue: " << queue.backElement() << std::endl;

        queue.clear();
        std::cout << "Queue size after clear: " << queue.size() << std::endl;

        try {
            queue.dequeue();
        } catch (const std::underflow_error& e) {
            std::cout << "Expected underflow error: " << e.what() << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
    }
}

int main() {

    std::wcout << L"Running Expression Evaluator Tests:\n";
    runExpressionEvaluatorTests();

    std::wcout << L"\n-----------------------------\n";

    std::wcout << L"Running Circular Queue Tests:\n";
    runCircularQueueTests();

    return 0;
}
