#include <iostream>
#include <vector>
#include <string>
#include "ExpressionEvaluator.hpp"

void runTests() {
    ExpressionEvaluator evaluator;
    std::vector<std::pair<std::string, double>> tests = {
        {"3 + 5 * ( 2 - (8 + 2) ) + 12 / 4 - 6 + 7 * (8 - (3 + 2))", -19},
        {"10 + 2 * 6", 22},
        {"100 * 2 + 12", 212},
        {"100 * ( 2 + 12 )", 1400},
        {"100 * ( 2 + 12 ) / 14", 100},
        {"3.5 + 2.1 * (4 - 2) / 2",5.6}
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

int main() {
    runTests();
    return 0;
}
