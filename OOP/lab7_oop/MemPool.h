#pragma once
#include <cstddef>
#include <new>

// size classes: 8 16 32 ... 262144 bytes (18 levels)
// requests larger than 262144 bytes fall back to new/delete
static const size_t NUM_CLASSES     = 18;
static const size_t MIN_SLOT        = 8;
static const size_t MAX_SMALL       = MIN_SLOT << (NUM_CLASSES - 1);
static const size_t SLOTS_PER_ARENA = 256;

class MemPool {
public:
    static MemPool& instance() {
        static MemPool pool;
        return pool;
    }

    // non-copyable
    MemPool(const MemPool&) = delete;
    MemPool& operator=(const MemPool&) = delete;

    // allocate memory of at least 'bytes' size
    void* allocate(size_t bytes) {
        if (bytes == 0) bytes = 1;
        if (bytes > MAX_SMALL)
            return ::operator new(bytes);

        // find the appropriate size class
        size_t cls = 0, s = MIN_SLOT;
        while (s < bytes && cls < NUM_CLASSES - 1) { s <<= 1; cls++; }

        // if the free list is empty, allocate a new arena and populate the free list
        if (!freelist[cls]) {
            size_t slot = MIN_SLOT << cls;
            void* raw = ::operator new(sizeof(Arena) + slot * SLOTS_PER_ARENA);
            Arena* a = static_cast<Arena*>(raw);
            a->next = arenas[cls];
            arenas[cls] = a;
            char* p = reinterpret_cast<char*>(a) + sizeof(Arena);
            for (size_t i = 0; i < SLOTS_PER_ARENA; i++) {
                Node* node = reinterpret_cast<Node*>(p);
                node->next = freelist[cls];
                freelist[cls] = node;
                p += slot;
            }
        }
        // pop a node from the free list
        Node* p = freelist[cls];
        freelist[cls] = p->next;
        return p;
    }

    // deallocate memory previously allocated by allocate()
    void deallocate(void* p, size_t bytes) noexcept {
        if (!p) return;
        if (bytes == 0) bytes = 1;
        if (bytes > MAX_SMALL) {
            ::operator delete(p);
            return;
        }

        // find the appropriate size class
        size_t cls = 0, s = MIN_SLOT;
        while (s < bytes && cls < NUM_CLASSES - 1){
            s <<= 1; cls++;
        }
        // push the node back to the free list
        Node* node = static_cast<Node*>(p);
        node->next = freelist[cls];
        freelist[cls] = node;
    }

private:
    struct Node  { Node* next; };
    struct Arena { Arena* next; };

    Node*  freelist[NUM_CLASSES] = {};
    Arena* arenas[NUM_CLASSES]   = {};

    MemPool() = default;

    // clean up all arenas on destruction
    ~MemPool() {
        for (size_t i = 0; i < NUM_CLASSES; i++) {
            Arena* a = arenas[i];
            while (a) {
                Arena* nx = a->next;
                ::operator delete(a);
                a = nx;
            }
        }
    }
};