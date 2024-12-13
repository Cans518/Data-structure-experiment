#include <iostream>
#include "ackermann.hpp"

int main() {
    try {
        int m = 2, n = 1;

        std::cout << "Calculating ACK(" << m << ", " << n << ") non-recursively with debug enabled:" << std::endl;
        std::cout << "Result: " << Ackermann::calculate(m, n, false, true) << std::endl;

        std::cout << "Calculating ACK(" << m << ", " << n << ") recursively with debug enabled:" << std::endl;
        std::cout << "Result: " << Ackermann::calculate(m, n, true, true) << std::endl;

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
