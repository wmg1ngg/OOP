#include <iostream>
#include <string>
#include "vector.h"

using namespace std;

int main() {
    Vector<int> v1;
    // Check whether the vector is empty
    cout << "v1 empty: " << v1.empty() << endl;

    // Add some elements to the vector
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    cout << "v1: " << v1 << ", size=" << v1.size() << endl;

    // Modify an element using []
    v1[1] = 99;
    cout << "v1[1]=99: " << v1 << endl;

    // Access element safely using at()
    cout << "v1.at(0) = " << v1.at(0) << endl;

    // Test out-of-range exception
    try {
        v1.at(100);
    } catch (const out_of_range& e) {
        cout << "at(100) exception: " << e.what() << endl;
    }

    // Create a vector with initial size 5
    Vector<int> v2(5);
    cout << "v2(5): " << v2 << endl;

    // Create another vector and insert numbers 0~9
    Vector<int> v3;
    for (int i = 0; i < 10; i++)
        v3.push_back(i);
    cout << "v3: " << v3 << endl;

    // Use copy constructor to create v4 from v3
    Vector<int> v4(v3);
    v4[0] = 777; // Modify v4 and verify v3 is unchanged
    cout << "v3: " << v3 << endl;
    cout << "v4: " << v4 << endl;

    // Clear all elements in v4
    v4.clear();

    // Check size and empty status after clear
    cout << "v4 after clear: size=" << v4.size() << " empty=" << v4.empty() << endl;

    // Test Vector with string type
    Vector<string> vs;
    vs.push_back("hello");
    vs.push_back("world");
    cout << "vs: " << vs << endl;

    return 0;
}