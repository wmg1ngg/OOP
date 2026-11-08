#pragma once
#include <string>
#include <iostream>

class fraction {
public:
    // Constructors
    fraction();
    fraction(int n, int d);
    fraction(const fraction& f);
    explicit fraction(std::string s); // construct from a finite decimal string

    // Arithmetic operators
    const fraction operator+(const fraction& f) const;
    const fraction operator-(const fraction& f) const;
    const fraction operator*(const fraction& f) const;
    const fraction operator/(const fraction& f) const;

    // Relational operators
    bool operator>(const fraction& f) const;
    bool operator>=(const fraction& f) const;
    bool operator==(const fraction& f) const;
    bool operator<(const fraction& f) const;
    bool operator<=(const fraction& f) const;
    bool operator!=(const fraction& f) const;

    // Type conversions
    operator double() const;
    operator std::string() const;

    // Stream operators
    friend std::ostream& operator<<(std::ostream& os, const fraction& f);
    friend std::istream& operator>>(std::istream& is, fraction& f);

    // Helper: return a NaN fraction
    static fraction nan();

private:
    int numer;  // numerator
    int denom;  // denominator
    bool isNaN; // marks an invalid fraction

    void simplify(); // reduce and normalize sign
};