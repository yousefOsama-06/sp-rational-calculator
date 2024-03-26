/// File: CS112_A2_T3_2_20230591_20231235_20230359.cpp
/// Section 1/2
/// Yousef Osama Mamdouh Ahmed - 20230591   Operator Overloading Functions
/// Sara Shaban Ahmed Ali      - 20231235   Simplify/Input/Output Functions
/// Mohamed Hisham Gaber Fahmy - 20230359   Main function and exception handling

#include "bits/stdc++.h"

using namespace std;

struct num {
    long long numerator = 0, denominator = 1;

    num operator+(num x) const {
        num ans;
        ans.numerator = numerator * x.denominator + denominator * x.numerator;
        ans.denominator = denominator * x.denominator;
        ans.simplify();
        return ans;
    }

    num operator-() {
        num ans = *this;
        ans.numerator *= -1;
        return ans;
    }

    num operator-(num x) const {
        return *this + (-x);
    }

    num operator*(num x) const {
        num ans;
        ans.numerator = numerator * x.numerator;
        ans.denominator = denominator * x.denominator;
        ans.simplify();
        return ans;
    }

    num operator/(num x) const {
        num ans;
        ans.numerator = numerator * x.denominator;
        ans.denominator = denominator * x.numerator;
        ans.simplify();
        return ans;
    }

    // simplify both numerator and denominator by dividing them with the greatest common divisor of them
    void simplify() {
        // x = greatest common divisor
        long long x = __gcd(abs(numerator), abs(denominator));
        numerator /= x;
        denominator /= x;
        if (denominator < 0)
            numerator *= -1, denominator *= -1;
    }

    void input(const string &s) {
        string x, y;
        bool slash = false;
        for (char c: s) {
            if (c == '/') {
                if (slash)
                    throw exception();
                slash = true;
                continue;
            }
            if (!slash)
                x += c;
            else
                y += c;
        }
        for (int i = 0; i < x.size(); i++) {
            bool valid = isdigit(x[i]) || (x[i] == '-' || x[i] == '+' && i == 0);
            if (!valid)
                throw exception();
        }

        for (int i = 0; i < y.size(); i++) {
            bool valid = isdigit(y[i]) || (y[i] == '-' || y[i] == '+' && i == 0);
            if (!valid)
                throw exception();
        }
        if (x.empty())
            throw exception();

        numerator = stoll(x);
        if (!slash)
            denominator = 1;
        else {
            if (y.empty())
                throw exception();
            denominator = stoll(y);
        }
        if (denominator == 0)
            throw exception();
    }

    void output() const {
        if (numerator == 0) {
            cout << 0;
        } else {
            if (numerator < 0)
                cout << '-';
            if (abs(numerator) / denominator != 0)
                cout << abs(numerator) / denominator << ' ';
            if (abs(numerator) % denominator != 0)
                cout << abs(numerator) % denominator << '/' << denominator;
        }
    }
};

int main() {
    cout << "Please follow these instructions:\n\n"
            "Enter two rational numbers and an operator in the middle such that:\n"
            "A rational number may contain only a numerator or both a numerator and a denominator.\n"
            "A denominator may not be zero.\n"
            "No spaces between the slash(/) and the numerator or denominator.\n"
            "A numerator or a denominator may be negative but don't add space after the negative sign.\n"
            "There's a space before and after the operator.\n"
            "The operator is one of [+, -, *, /]\n"
            "eg. 1/2 / -3/2\n\n\n";
    while (true) {
        try {
            cout << "What do you want to do?\n"
                    "1. Continue\n"
                    "2. Exit\n";
            int choice;
            if (!(cin >> choice))
                throw exception();
            if (choice == 2)
                break;
            if (choice != 1)
                throw exception();
            num x, y;
            string s;
            cin.ignore();
            getline(cin, s);
            string a, op, b;
            int state = 0;
            for (char c: s) {
                if (c == ' ') {
                    state++;
                    continue;
                }
                if (state == 0)
                    a += c;
                else if (state == 1)
                    op += c;
                else if (state == 2)
                    b += c;
                else
                    throw exception();
            }
            x.input(a);
            y.input(b);
            if (op == "+") {
                num z = x + y;
                z.output();
            } else if (op == "-") {
                num z = x - y;
                z.output();
            } else if (op == "*") {
                num z = x * y;
                z.output();
            } else if (op == "/") {
                num z = x / y;
                z.output();
            } else {
                throw exception();
            }
            cout << "\n\n";
        } catch (...) {
            cout << "Invalid Input!\n\n";
        }
    }
}