#pragma once

#include <cstddef>
#include <utility>
#include <type_traits>

template<typename T>
class UniquePointer {

private:

    T *pointer;

public:

    explicit UniquePointer(T *p = nullptr) : pointer(p) {}
    ~UniquePointer() {
        delete pointer;
    }

    UniquePointer(const UniquePointer &) = delete;
    UniquePointer &operator=(const UniquePointer &) = delete;

    UniquePointer(UniquePointer &&other) noexcept : pointer(other.pointer) {
        other.pointer = nullptr;
    }

    UniquePointer &operator=(UniquePointer &&other) noexcept {
        if (this != &other) {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }

        return *this;
    }

    template<typename U>
    UniquePointer(UniquePointer<U> &&other) noexcept
    requires std::is_convertible_v<U*, T*>
            : pointer(static_cast<T*>(other.release())) {}

    template<typename U>
    UniquePointer &operator=(UniquePointer<U> &&other) noexcept
    requires std::is_convertible_v<U*, T*> {
        if (this != reinterpret_cast<UniquePointer*>(&other)) {
            delete pointer;
            pointer = static_cast<T*>(other.release());
        }
        return *this;
    }

    T &operator*() const {
        return *pointer;
    }

    T *operator->() const {
        return pointer;
    }

    T &operator[](std::size_t index) const {
        return (*pointer)[index];
    }

    void reset(T *p = nullptr) {
        delete pointer;
        pointer = p;
    }

    T *release() {
        T *tmp = pointer;
        pointer = nullptr;
        return tmp;
    }

    bool null() const {
        return pointer == nullptr;
    }

    T* get() const {
        return pointer;
    }
};

template<typename T>
class UniquePointer<T[]> {

private:

    T *pointer;

public:

    explicit UniquePointer(T *p = nullptr) : pointer(p) {}
    ~UniquePointer() {
        delete[] pointer;
    }

    UniquePointer(const UniquePointer &) = delete;
    UniquePointer &operator=(const UniquePointer &) = delete;

    UniquePointer(UniquePointer &&other) noexcept : pointer(other.pointer) {
        other.pointer = nullptr;
    }

    UniquePointer &operator=(UniquePointer &&other) noexcept {
        if (this != &other) {
            delete[] pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }

        return *this;
    }

    template<typename U>
    UniquePointer(UniquePointer<U[]> &&other) noexcept
    requires std::is_convertible_v<U*, T*>
            : pointer(static_cast<T*>(other.release())) {}

    template<typename U>
    UniquePointer &operator=(UniquePointer<U[]> &&other) noexcept
    requires std::is_convertible_v<U*, T*> {
        if (this != reinterpret_cast<UniquePointer*>(&other)) {
            delete[] pointer;
            pointer = static_cast<T*>(other.release());
        }
        return *this;
    }

    T &operator*() const {
        return *pointer;
    }

    T *operator->() const {
        return pointer;
    }

    T &operator[](std::size_t index) const {
        return pointer[index];
    }

    void reset(T *p = nullptr) {
        delete[] pointer;
        pointer = p;
    }

    T *release() {
        T *tmp = pointer;
        pointer = nullptr;
        return tmp;
    }

    bool null() const {
        return pointer == nullptr;
    }

    T* get() const {
        return pointer;
    }
};
