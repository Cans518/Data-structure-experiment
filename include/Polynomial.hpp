#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "SinglyLinkedList.hpp"
#include <iostream>
#include <initializer_list>
#include <cmath> 

class Polynomial {
private:
    struct Term {
        size_t exponent;
        double coefficient;
        Term(size_t exp, double coeff) : exponent(exp), coefficient(coeff) {}
    };

    SinglyLinkedList<Term> terms;

public:
    Polynomial() = default;
    Polynomial(const std::initializer_list<double>& coeffs);

    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator-=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);
    
    double Calc(double x) const;
    void print() const;
    
};

/**
 * @brief 使用初始化列表构造多项式
 * @param coeffs 系数列表
 */
Polynomial::Polynomial(const std::initializer_list<double>& coeffs) {
    size_t exp = 0;
    for (double coeff : coeffs) {
        if (coeff != 0.0) {
            terms.insert(terms.size(), Term(exp, coeff));
        }
        ++exp;
    }
}

/**
 * @brief 多项式加法
 * @param other 另一个多项式
 * @return Polynomial 相加后的多项式
 */
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result;
    auto it1 = terms.begin();
    auto it2 = other.terms.begin();

    while (it1 != terms.end() || it2 != other.terms.end()) {
        if (it1 != terms.end() && (it2 == other.terms.end() || it1->exponent < it2->exponent)) {
            result.terms.insert(result.terms.size(), *it1);
            ++it1;
        } else if (it2 != other.terms.end() && (it1 == terms.end() || it1->exponent > it2->exponent)) {
            result.terms.insert(result.terms.size(), *it2);
            ++it2;
        } else {
            double newCoeff = it1->coefficient + it2->coefficient;
            if (newCoeff != 0.0) {
                result.terms.insert(result.terms.size(), Term(it1->exponent, newCoeff));
            }
            ++it1;
            ++it2;
        }
    }
    return result;
}

/**
 * @brief 多项式减法
 * @param other 另一个多项式
 * @return Polynomial 相减后的多项式
 */
Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result;
    auto it1 = terms.begin();
    auto it2 = other.terms.begin();

    while (it1 != terms.end() || it2 != other.terms.end()) {
        if (it1 != terms.end() && (it2 == other.terms.end() || it1->exponent < it2->exponent)) {
            result.terms.insert(result.terms.size(), *it1);
            ++it1;
        } else if (it2 != other.terms.end() && (it1 == terms.end() || it1->exponent > it2->exponent)) {
            result.terms.insert(result.terms.size(), Term(it2->exponent, -it2->coefficient));
            ++it2;
        } else {
            double newCoeff = it1->coefficient - it2->coefficient;
            if (newCoeff != 0.0) {
                result.terms.insert(result.terms.size(), Term(it1->exponent, newCoeff));
            }
            ++it1;
            ++it2;
        }
    }
    return result;
}

/**
 * @brief 多项式乘法
 * @param other 另一个多项式
 * @return Polynomial 相乘后的多项式
 */
Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;

    for (auto it1 = terms.begin(); it1 != terms.end(); ++it1) {
        Polynomial temp;
        for (auto it2 = other.terms.begin(); it2 != other.terms.end(); ++it2) {
            size_t newExp = it1->exponent + it2->exponent;
            double newCoeff = it1->coefficient * it2->coefficient;
            temp.terms.insert(temp.terms.size(), Term(newExp, newCoeff));
        }
        result += temp;
    }
    return result;
}

/**
 * @brief 多项式加法赋值
 * @param other 另一个多项式
 * @return Polynomial& 自身引用
 */
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    *this = *this + other;
    return *this;
}

/**
 * @brief 多项式减法赋值
 * @param other 另一个多项式
 * @return Polynomial& 自身引用
 */
Polynomial& Polynomial::operator-=(const Polynomial& other) {
    *this = *this - other;
    return *this;
}

/**
 * @brief 多项式乘法赋值
 * @param other 另一个多项式
 * @return Polynomial& 自身引用
 */
Polynomial& Polynomial::operator*=(const Polynomial& other) {
    *this = *this * other;
    return *this;
}

/**
 * @brief 计算多项式在x处的值
 * @param x 自变量值
 * @return double 多项式的计算结果
 */
double Polynomial::Calc(double x) const {
    double result = 0.0;
    for (auto it = terms.begin(); it != terms.end(); ++it) {
        result += it->coefficient * std::pow(x, it->exponent);
    }
    return result;
}

/**
 * @brief 打印多项式
 */
void Polynomial::print() const {
    for (auto it = terms.begin(); it != terms.end(); ++it) {
        if (it->coefficient != 0) {
            if (it != terms.begin() && it->coefficient > 0) std::cout << "+";
            std::cout << it->coefficient;
            if (it->exponent > 0) std::cout << "x^" << it->exponent;
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

#endif // POLYNOMIAL_HPP
