#include "Polynomial.hpp"
#include <iostream>

int main() {

    Polynomial p1 = {3, 0, 2}; // 3 + 0*x + 2*x^2
    Polynomial p2 = {1, 4, 0, 5}; // 1 + 4*x + 0*x^2 + 5*x^3

    double value1 = p1.Calc(2.0);
    double value2 = p2.Calc(2.0);

    std::cout << "p1 evaluated at x = 2: " << value1 << std::endl; 
    std::cout << "p2 evaluated at x = 2: " << value2 << std::endl; 

    Polynomial p3 = p1 + p2;

    std::cout << "p1 + p2: ";
    p3.print(); 
    double value3 = p3.Calc(2.0);
    std::cout << "p3 evaluated at x = 2: " << value3 << std::endl;
    return 0;
}