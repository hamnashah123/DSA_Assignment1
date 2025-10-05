#include <iostream>
#include <string>
#include "polynomial.h"
using namespace std;

// Node for each term of polynomial
struct Term {
    int coeff;      // coefficient
    int exp;        // exponent
    Term* next;     // pointer to next term
    Term(int c, int e) : coeff(c), exp(e), next(NULL) {}
};

class Polynomial {
private:
    Term* head;  // pointer to first term

    // Utility: insert term in sorted order by exponent (descending)
    void insertSorted(int coeff, int exp) {
        if (coeff == 0) return;  // skip zero terms

        Term* newTerm = new Term(coeff, exp);

        // Case 1: list empty or new term exponent > head exponent
        if (head == NULL || exp > head->exp) {
            newTerm->next = head;
            head = newTerm;
            return;
        }

        Term* curr = head;
        Term* prev = NULL;

        // Traverse until position found
        while (curr != NULL && curr->exp > exp) {
            prev = curr;
            curr = curr->next;
        }

        // Case 2: same exponent → combine coefficients
        if (curr != NULL && curr->exp == exp) {
            curr->coeff += coeff;
            delete newTerm; // discard new node
            if (curr->coeff == 0) { // remove zero coefficient term
                if (prev == NULL) {
                    head = curr->next;
                } else {
                    prev->next = curr->next;
                }
                delete curr;
            }
            return;
        }

        // Case 3: insert between prev and curr
        newTerm->next = curr;
        if (prev != NULL) prev->next = newTerm;
    }

public:
    // Constructor
    Polynomial() {
        head = NULL;
    }

    // Insert term (user-facing function)
    void insertTerm(int coeff, int exp) {
        insertSorted(coeff, exp);
    }

    // Display polynomial in human-readable format
    string toString() const {
        if (head == NULL) return "0";

        string result = "";
        Term* curr = head;
        bool firstTerm = true;

        while (curr != NULL) {
            // Handle sign
            if (curr->coeff > 0 && !firstTerm) result += " + ";
            else if (curr->coeff < 0) result += " - ";

            // Handle absolute value of coeff
            int absCoeff = (curr->coeff < 0) ? -curr->coeff : curr->coeff;

            // Decide how to print coefficient and exponent
            if (curr->exp == 0) {
                result += to_string(absCoeff); // constant term
            } else if (curr->exp == 1) {
                if (absCoeff != 1) result += to_string(absCoeff) + "x";
                else result += "x";
            } else {
                if (absCoeff != 1) result += to_string(absCoeff) + "x^" + to_string(curr->exp);
                else result += "x^" + to_string(curr->exp);
            }

            curr = curr->next;
            firstTerm = false;
        }

        return result;
    }

    // Addition of two polynomials
    Polynomial add(const Polynomial& other) const {
        Polynomial result;
        Term* p1 = head;
        Term* p2 = other.head;

        while (p1 != NULL || p2 != NULL) {
            if (p2 == NULL || (p1 != NULL && p1->exp > p2->exp)) {
                result.insertTerm(p1->coeff, p1->exp);
                p1 = p1->next;
            } else if (p1 == NULL || p2->exp > p1->exp) {
                result.insertTerm(p2->coeff, p2->exp);
                p2 = p2->next;
            } else { // exponents equal
                result.insertTerm(p1->coeff + p2->coeff, p1->exp);
                p1 = p1->next;
                p2 = p2->next;
            }
        }

        return result;
    }

    // Multiplication of two polynomials
    Polynomial multiply(const Polynomial& other) const {
        Polynomial result;
        for (Term* p1 = head; p1 != NULL; p1 = p1->next) {
            for (Term* p2 = other.head; p2 != NULL; p2 = p2->next) {
                int coeffProd = p1->coeff * p2->coeff;
                int expSum = p1->exp + p2->exp;
                result.insertTerm(coeffProd, expSum);
            }
        }
        return result;
    }

    // Derivative of polynomial
    Polynomial derivative() const {
        Polynomial result;
        for (Term* curr = head; curr != NULL; curr = curr->next) {
            if (curr->exp > 0) {
                result.insertTerm(curr->coeff * curr->exp, curr->exp - 1);
            }
        }
        return result;
    }
};


int main() {
    Polynomial p1;
    p1.insertTerm(3, 4);
    p1.insertTerm(2, 2);
    p1.insertTerm(-1, 1);
    p1.insertTerm(5, 0);

    Polynomial p2;
    p2.insertTerm(1, 4);
    p2.insertTerm(1, 0);

    Polynomial sum = p1.add(p2);

    Polynomial p3;
    p3.insertTerm(2, 1);

    Polynomial prod = sum.multiply(p3);

    Polynomial deriv = p1.derivative();

    cout << "p1: " << p1.toString() << endl;
    cout << "sum: " << sum.toString() << endl;
    cout << "prod: " << prod.toString() << endl;
    cout << "derivative of p1: " << deriv.toString() << endl;

    return 0;
}
