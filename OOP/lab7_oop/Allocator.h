#pragma once
#include "MemPool.h"
#include <cstddef>
#include <utility>

template <typename T>
class Allocator {
public:
    using value_type = T;

    Allocator() = default;

    // copy constructor for different type U
    template <typename U>
    Allocator(const Allocator<U>&) noexcept {}

    // rebind allocator to type U
    template <typename U>
    struct rebind { using other = Allocator<U>; };

    // allocate memory for n objects of type T
    T* allocate(size_t n) {
        return static_cast<T*>(MemPool::instance().allocate(n * sizeof(T)));
    }

    // deallocate memory previously allocated by allocate()
    void deallocate(T* p, size_t n) noexcept {
        MemPool::instance().deallocate(p, n * sizeof(T));
    }

    // construct an object of type U at p with given args
    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        ::new(p) U(std::forward<Args>(args)...);
    }

    // destroy the object at p
    template <typename U>
    void destroy(U* p) noexcept { p->~U(); }
};

// Allocators are stateless, so all instances are equal
template <typename T, typename U>
bool operator==(const Allocator<T>&, const Allocator<U>&) noexcept { return true; }

template <typename T, typename U>
bool operator!=(const Allocator<T>&, const Allocator<U>&) noexcept { return false; }