#pragma once
#include <new>
#include <utility>

namespace sjtu {

template <typename _Tp>
class unique_ptr {
  private:
    _Tp* ptr;

  public:
    // Construct an empty pointer (nullptr)
    unique_ptr() : ptr(nullptr) {}

    // Same pointer cannot be pointed to by multiple unique_ptrs
    unique_ptr(const unique_ptr &) = delete;

    // Move constructor. Transfer ownership.
    unique_ptr(unique_ptr &&other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // Destructor. Release memory. delete nullptr is safe.
    ~unique_ptr() {
        delete ptr;
    }

    // Same pointer cannot be pointed to by multiple unique_ptrs
    unique_ptr &operator=(const unique_ptr &) = delete;

    // Move assignment. Transfer ownership.
    unique_ptr &operator=(unique_ptr &&other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Take ownership of a raw pointer
    explicit unique_ptr(_Tp *p) : ptr(p) {}

    // Reset to null pointer. Release memory if not null.
    void reset() {
        delete ptr;
        ptr = nullptr;
    }

    // Transfer ownership, return the address of the object.
    // Then set self to null.
    _Tp *release() {
        _Tp *tmp = ptr;
        ptr = nullptr;
        return tmp;
    }

    // Return the address of the object. Ownership does not transfer.
    _Tp *get() const {
        return ptr;
    }

    // Overload * operator (dereference), return reference to the object.
    _Tp &operator*() {
        return *ptr;
    }

    // Overload -> operator (member access), return address of the object.
    _Tp *operator->() {
        return ptr;
    }
};

// Create a unique_ptr pointing to a new _Tp object allocated with new
template <typename _Tp>
unique_ptr<_Tp> make_unique(const _Tp &val) {
    return unique_ptr<_Tp>(new _Tp(val));
}

} // namespace sjtu
