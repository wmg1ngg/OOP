#include <iostream>
#include <string>
#include "fraction.h"

int main() {
    // Default constructor
    fraction d;
    std::cout << "default ctor: " << d << " = " << (double)d << std::endl;

    // Numerator/denominator constructor (also tests simplification)
    fraction a(3, 6);  // should simplify to 1/2
    std::cout << "3/6 simplified: " << a << std::endl;

    // Copy constructor
    fraction b(a);
    std::cout << "copy of a: " << b << std::endl;

    // Decimal string constructor
    fraction c(std::string("1.5"));
    std::cout << "\"1.5\" -> " << c << std::endl;

    fraction c2(std::string("0.333"));
    std::cout << "\"0.333\" -> " << c2 << std::endl;

    // Stream input: format is numerator/denominator
    fraction x, y;
    std::cout << "\nEnter two fractions (e.g. 2/3), one per line:" << std::endl;
    std::cin >> x >> y;
    std::cout << "x = " << x << "  y = " << y << std::endl;

    // Arithmetic
    std::cout << "\n--- Arithmetic ---" << std::endl;
    std::cout << x << " + " << y << " = " << (x + y) << " = " << (double)(x + y) << std::endl;
    std::cout << x << " - " << y << " = " << (x - y) << " = " << (double)(x - y) << std::endl;
    std::cout << x << " * " << y << " = " << (x * y) << " = " << (double)(x * y) << std::endl;
    std::cout << x << " / " << y << " = " << (x / y) << " = " << (double)(x / y) << std::endl;

    // Relational operators
    std::cout << "\n--- Comparison ---" << std::endl;
    std::cout << x << " >  " << y << " : " << (x >  y) << std::endl;
    std::cout << x << " >= " << y << " : " << (x >= y) << std::endl;
    std::cout << x << " == " << y << " : " << (x == y) << std::endl;
    std::cout << x << " != " << y << " : " << (x != y) << std::endl;
    std::cout << x << " <  " << y << " : " << (x <  y) << std::endl;
    std::cout << x << " <= " << y << " : " << (x <= y) << std::endl;

    // Copy-construct from an expression result
    fraction e(x + y);
    std::cout << "\ncopy ctor from x+y: " << e << std::endl;

    // Another default-constructed instance
    fraction d2;
    std::cout << "default ctor d2: " << d2 << std::endl;

    // Division by zero -> NaN
    fraction zero(0, 1);
    fraction nanResult = x / zero;
    std::cout << "\n" << x << " / 0 = " << nanResult << std::endl;
    std::cout << "NaN + " << y << " = " << (nanResult + y) << std::endl;

    // Cast to string
    std::string s = (std::string)x;
    std::cout << "\nx as std::string: " << s << std::endl;

    return 0;
}