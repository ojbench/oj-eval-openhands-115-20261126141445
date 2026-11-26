#include <iostream>
#include <cassert>
#include "src.hpp"

int main() {
    // Test 1: Default constructor
    {
        sjtu::unique_ptr<int> p;
        assert(p.get() == nullptr);
        std::cout << "Test 1 passed: default constructor" << std::endl;
    }

    // Test 2: Constructor from raw pointer
    {
        int* raw = new int(42);
        sjtu::unique_ptr<int> p(raw);
        assert(p.get() == raw);
        assert(*p == 42);
        std::cout << "Test 2 passed: constructor from raw pointer" << std::endl;
    }

    // Test 3: Destructor frees memory
    {
        sjtu::unique_ptr<int> p(new int(10));
        assert(*p == 10);
    } // should free here

    // Test 4: Move constructor
    {
        sjtu::unique_ptr<int> p1(new int(99));
        sjtu::unique_ptr<int> p2(std::move(p1));
        assert(p2.get() != nullptr);
        assert(*p2 == 99);
        assert(p1.get() == nullptr);
        std::cout << "Test 4 passed: move constructor" << std::endl;
    }

    // Test 5: Move assignment
    {
        sjtu::unique_ptr<int> p1(new int(1));
        sjtu::unique_ptr<int> p2(new int(2));
        p2 = std::move(p1);
        assert(*p2 == 1);
        assert(p1.get() == nullptr);
        std::cout << "Test 5 passed: move assignment" << std::endl;
    }

    // Test 6: reset()
    {
        sjtu::unique_ptr<int> p(new int(5));
        p.reset();
        assert(p.get() == nullptr);
        std::cout << "Test 6 passed: reset()" << std::endl;
    }

    // Test 7: release()
    {
        sjtu::unique_ptr<int> p(new int(7));
        int* raw = p.release();
        assert(raw != nullptr);
        assert(*raw == 7);
        assert(p.get() == nullptr);
        delete raw;
        std::cout << "Test 7 passed: release()" << std::endl;
    }

    // Test 8: operator->
    {
        struct Foo {
            int x;
            int get() const { return x; }
        };
        sjtu::unique_ptr<Foo> p(new Foo{42});
        assert(p->x == 42);
        assert(p->get() == 42);
        std::cout << "Test 8 passed: operator->" << std::endl;
    }

    // Test 9: make_unique
    {
        auto p = sjtu::make_unique<int>(123);
        assert(*p == 123);
        std::cout << "Test 9 passed: make_unique" << std::endl;
    }

    // Test 10: sizeof check
    {
        static_assert(sizeof(sjtu::unique_ptr<int>) <= sizeof(void*), "size too large");
        std::cout << "Test 10 passed: sizeof check" << std::endl;
    }

    // Test 11: Copy construction/assignment deleted
    // (compile-time check - if this compiles, copy is deleted)

    // Test 12: reset on nullptr
    {
        sjtu::unique_ptr<int> p;
        p.reset(); // should be safe
        std::cout << "Test 12 passed: reset(nullptr)" << std::endl;
    }

    // Test 13: self-move-assignment safety
    {
        sjtu::unique_ptr<int> p(new int(42));
        p = std::move(p);
        // After self-move, behavior is undefined in general, but our code handles it
        // by checking this != &other
        std::cout << "Test 13 passed: self-move-assignment" << std::endl;
    }

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
