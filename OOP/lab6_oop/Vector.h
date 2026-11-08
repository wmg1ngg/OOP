#pragma once
#include <stdexcept>
#include <iostream>

template <class T>
class Vector {
public:
    Vector();
    Vector(int size);
    Vector(const Vector& r);
    Vector& operator=(const Vector& r);
    ~Vector();

    T& operator[](int index);
    T& at(int index);
    int size() const;
    void push_back(const T& x);
    void clear();
    bool empty() const;

    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& v);

private:
    void inflate();

    T* m_pElements;
    int m_nSize;
    int m_nCapacity;
};


template <class T>
Vector<T>::Vector() {
    m_nSize = 0; 
    m_nCapacity = 4;
    m_pElements = new T[m_nCapacity];
}

template <class T>
Vector<T>::Vector(int size) {
    m_nSize = size;
    m_nCapacity = size * 2 + 4;
    m_pElements = new T[m_nCapacity]();
}

template <class T>
Vector<T>::Vector(const Vector& r) {
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    m_pElements = new T[m_nCapacity];
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r.m_pElements[i];
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& r) {
    if (this == &r) return *this;
    delete[] m_pElements;
    m_nSize = r.m_nSize;
    m_nCapacity = r.m_nCapacity;
    m_pElements = new T[m_nCapacity];
    for (int i = 0; i < m_nSize; i++)
        m_pElements[i] = r.m_pElements[i];
    return *this;
}

template <class T>
Vector<T>::~Vector() {
    delete[] m_pElements;
}

template <class T>
T& Vector<T>::operator[](int index) {
    return m_pElements[index];
}

template <class T>
T& Vector<T>::at(int index) {
    if (index < 0 || index >= m_nSize)
        throw std::out_of_range("index out of range");
    return m_pElements[index];
}

template <class T>
int Vector<T>::size() const {
    return m_nSize;
}

template <class T>
void Vector<T>::push_back(const T& x) {
    if (m_nSize == m_nCapacity)
        inflate();
    m_pElements[m_nSize++] = x;
}

template <class T>
void Vector<T>::clear() {
    m_nSize = 0;
}

template <class T>
bool Vector<T>::empty() const {
    return m_nSize == 0;
}

template <class T>
void Vector<T>::inflate() {
    m_nCapacity *= 2;
    T* tmp = new T[m_nCapacity];
    for (int i = 0; i < m_nSize; i++)
        tmp[i] = m_pElements[i];
    delete[] m_pElements;
    m_pElements = tmp;
}

template <class U>
std::ostream& operator<<(std::ostream& os, const Vector<U>& v) {
    os << "[";
    for (int i = 0; i < v.m_nSize; i++) {
        if (i) os << ", ";
        os << v.m_pElements[i];
    }
    os << "]";
    return os;
}