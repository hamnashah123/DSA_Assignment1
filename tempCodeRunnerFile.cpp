#include "polynomial.h"
#include <map>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>



static std::map<const Polynomial*, std::map<int, int, std::greater<int>>> storage;



// Insert a term into the polynomial
void Polynomial::insertTerm(int coefficient, int exponent) {
    if (exponent < 0) return;              // Non-negative exponents only
    if (coefficient == 0) return;          // Skip zero coefficients

    storage[this][exponent] += coefficient; // Combine like terms

    // Remove if coefficient becomes 0
    if (storage[this][exponent] == 0) {
        storage[this].erase(exponent);
    }
}

// Return polynomial as a human-readable string
std::string Polynomial::toString() const {
    std::ostringstream oss;
    bool first = true;

    const auto &terms = storage[this];

    if (terms.empty()) return "0";

    for (auto &term : terms) {
        int exponent = term.first;
        int coefficient = term.second;

        if (!first) {
            if (coefficient > 0) oss << " + ";
            else oss << " - ";
        } else if (coefficient < 0) {
            oss << "-";
        }

        int absCoeff = std::abs(coefficient);

        if (exponent == 0) {
            oss << absCoeff;
        } else if (exponent == 1) {
            if (absCoeff != 1) oss << absCoeff;
            oss << "x";
        } else {
            if (absCoeff != 1) oss << absCoeff;
            oss << "x^" << exponent;
        }

        first = false;
    }

    return oss.str();
}

// Return a new polynomial that is the sum of this and other
Polynomial Polynomial::add(const Polynomial &other) const {
    Polynomial result;

    // Copy terms from *this
    for (auto &term : storage[this]) {
        result.insertTerm(term.second, term.first);
    }

    // Add terms from other
    for (auto &term : storage[&other]) {
        result.insertTerm(term.second, term.first);
    }

    return result;
}

// Return a new polynomial that is the product of this and other
Polynomial Polynomial::multiply(const Polynomial &other) const {
    Polynomial result;

    for (auto &a : storage[this]) {
        for (auto &b : storage[&other]) {
            int coeff = a.second * b.second;
            int exp = a.first + b.first;
            result.insertTerm(coeff, exp);
        }
    }

    return result;
}

// Return a new polynomial that is the derivative of this polynomial
Polynomial Polynomial::derivative() const {
    Polynomial result;

    for (auto &term : storage[this]) {
        int exp = term.first;
        int coeff = term.second;
        if (exp > 0) {
            result.insertTerm(coeff * exp, exp - 1);
        }
    }

    return result;
}


// #include <iostream>
// using namespace std;

// int main() {
//     Polynomial p1;
//     p1.insertTerm(3, 4);
//     p1.insertTerm(2, 2);
//     p1.insertTerm(-1, 1);
//     p1.insertTerm(5, 0);

//     Polynomial p2;
//     p2.insertTerm(1, 4);
//     p2.insertTerm(1, 0);

//     Polynomial sum = p1.add(p2);
//     Polynomial p3;
//     p3.insertTerm(2, 1);

//     Polynomial prod = sum.multiply(p3);
//     Polynomial deriv = p1.derivative();

//     cout << "p1.toString(): " << p1.toString() << endl;
//     cout << "sum.toString(): " << sum.toString() << endl;
//     cout << "prod.toString(): " << prod.toString() << endl;
//     cout << "deriv.toString(): " << deriv.toString() << endl;

//     return 0;
// }
