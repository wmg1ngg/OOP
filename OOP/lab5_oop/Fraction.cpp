#include "fraction.h"
#include <cmath>
#include <string>

// Euclidean algorithm for greatest common divisor
static int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Reduce the fraction and keep the denominator positive
void fraction::simplify() {
    if (isNaN) return;
    if (denom == 0) {
        isNaN = true;
        return;
    }
    // Sign is carried by the numerator
    if (denom < 0) {
        numer = -numer;
        denom = -denom;
    }
    int g = gcd(abs(numer), denom);
    if (g > 0) {
        numer /= g;
        denom /= g;
    }
}

// Default: 0/1
fraction::fraction() : numer(0), denom(1), isNaN(false) {}

// Construct from numerator and denominator
fraction::fraction(int n, int d) : numer(n), denom(d), isNaN(false) {
    simplify();
}

// Copy constructor
fraction::fraction(const fraction& f)
    : numer(f.numer), denom(f.denom), isNaN(f.isNaN) {}

// Construct from a finite decimal string like "1.5" -> 3/2
fraction::fraction(std::string s) : numer(0), denom(1), isNaN(false) {
    double val = stod(s);

    // Count decimal places to determine the scale factor
    size_t dot = s.find('.');
    int decimals = 0;
    if (dot != std::string::npos)
        decimals = (int)(s.size() - dot - 1);

    int scale = 1;
    for (int i = 0; i < decimals; i++) scale *= 10;

    // Round to avoid floating-point noise
    numer = (int)round(val * scale);
    denom = scale;
    simplify();
}

// Arithmetic operators
const fraction fraction::operator+(const fraction& f) const {
    if (isNaN || f.isNaN) return fraction::nan();
    return fraction(numer * f.denom + f.numer * denom, denom * f.denom);
}

const fraction fraction::operator-(const fraction& f) const {
    if (isNaN || f.isNaN) return fraction::nan();
    return fraction(numer * f.denom - f.numer * denom, denom * f.denom);
}

const fraction fraction::operator*(const fraction& f) const {
    if (isNaN || f.isNaN) return fraction::nan();
    return fraction(numer * f.numer, denom * f.denom);
}

const fraction fraction::operator/(const fraction& f) const {
    if (isNaN || f.isNaN || f.numer == 0) return fraction::nan();
    return fraction(numer * f.denom, denom * f.numer);
}

// Relational operators: implement >, >=, == and derive the rest
bool fraction::operator>(const fraction& f) const {
    if (isNaN || f.isNaN) return false;
    return numer * f.denom > f.numer * denom;
}

bool fraction::operator>=(const fraction& f) const {
    if (isNaN || f.isNaN) return false;
    return numer * f.denom >= f.numer * denom;
}

bool fraction::operator==(const fraction& f) const {
    if (isNaN || f.isNaN) return false;
    return numer * f.denom == f.numer * denom;
}

bool fraction::operator<(const fraction& f) const  { return !(*this >= f); }
bool fraction::operator<=(const fraction& f) const { return !(*this > f);  }
bool fraction::operator!=(const fraction& f) const { return !(*this == f); }

// Cast to double
fraction::operator double() const {
    if (isNaN) return NAN;
    return (double)numer / denom;
}

// Cast to string, format: a/b
fraction::operator std::string() const {
    if (isNaN) return "NaN";
    return std::to_string(numer) + "/" + std::to_string(denom);
}

// Stream operators
std::ostream& operator<<(std::ostream& os, const fraction& f) {
    os << (std::string)f;
    return os;
}

// Input format: a/b
std::istream& operator>>(std::istream& is, fraction& f) {
    int a, b;
    char c;
    is >> a >> c >> b;
    f = fraction(a, b);
    return is;
}

// Helper: return a NaN fraction
fraction fraction::nan() {
    fraction f;
    f.isNaN = true;
    return f;
}