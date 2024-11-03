#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class SharedPointer {

private:

    T* pointer;
    size_t* referenceCount;

    void clean() {
        if (referenceCount && --(*referenceCount) == 0) {
            delete pointer;
            delete referenceCount;
        }
    }

public:

    explicit SharedPointer(T* p = nullptr) : pointer(p), referenceCount(new size_t(1)) {}

    SharedPointer(const SharedPointer& other)
            : pointer(other.pointer), referenceCount(other.referenceCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }

    SharedPointer& operator=(const SharedPointer& other) {
        if (this != &other) {
            clean();
            pointer = other.pointer;
            referenceCount = other.referenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        }
        return *this;
    }

    ~SharedPointer() {
        clean();
    }

    T* get() const {
        return pointer;
    }

    size_t* use_count_ptr() const {
        return referenceCount;
    }

    T& operator*() const {
        return *pointer;
    }

    T* operator->() const {
        return pointer;
    }

    size_t use_count() const {
        return referenceCount ? *referenceCount : 0;
    }

    void reset(T* p = nullptr) {
        clean();
        pointer = p;
        referenceCount = new size_t(1);
    }

    bool null() const {
        return pointer == nullptr;
    }

    template<typename U>
    static SharedPointer<T> static_pointer_cast(const SharedPointer<U>& other) {
        return SharedPointer<T>(static_cast<T*>(other.get()), other.use_count_ptr());
    }

private:

    SharedPointer(T* p, size_t* refCount) : pointer(p), referenceCount(refCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }
};


template<typename T>
class SharedPointer<T[]> {

private:

    T* pointer;
    size_t *referenceCount;

    void clean(){
        if (referenceCount && --(*referenceCount) == 0) {
            delete pointer[];
            delete referenceCount;
        }
    }

public:

    explicit SharedPointer(T *p = nullptr) : pointer(p), referenceCount(new size_t(1)) {}

    SharedPointer(const SharedPointer &other)
            : pointer(other.pointer), referenceCount(other.referenceCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }

    SharedPointer &operator=(const SharedPointer &other) {
        if (this != &other) {
            clean();
            pointer = other.pointer;
            referenceCount = other.referenceCount;
            if (referenceCount) {
                ++(*referenceCount);
            }
        }

        return *this;
    }

    ~SharedPointer() {
        clean();
    }

    T &operator*() const {
        return *pointer;
    }

    T *operator->() const {
        return pointer;
    }

    size_t use_count() const { return referenceCount ? *referenceCount : 0; }

    void reset(T *p = nullptr) {
        clean();
        pointer = p;
        referenceCount = new size_t(1);
    }

    bool null() const {
        return pointer == nullptr;
    }

    T* get() const {
        return pointer;
    }

    template<typename U>
    static SharedPointer<T[]> static_pointer_cast(const SharedPointer<U[]>& other) {
        return SharedPointer<T[]>(static_cast<T*>(other.get()), other.use_count_ptr());
    }

private:

    SharedPointer(T* p, size_t* refCount) : pointer(p), referenceCount(refCount) {
        if (referenceCount) {
            ++(*referenceCount);
        }
    }
};