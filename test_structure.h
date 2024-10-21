#include "shared_pointer.h"
#include "unique_pointer.h"


template<typename T>
struct NodeUniquePointer {

    T data;
    UniquePointer<NodeUniquePointer<T>> next;

    explicit NodeUniquePointer(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedListUniquePointer {

private:

    UniquePointer<NodeUniquePointer<T>> head;
    size_t length;

public:

    LinkedListUniquePointer() : head(nullptr), length(0) {}

    void push_front(const T& value) {
        UniquePointer<NodeUniquePointer<T>> newNode = UniquePointer<NodeUniquePointer<T>>(new NodeUniquePointer<T>(value));
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++length;
    }

    bool null(){
        return head.null();
    }

    void pop_front() {
        if (!head.null()) {
            UniquePointer<NodeUniquePointer<T>> oldHead = std::move(head);
            head = std::move(oldHead->next);
            --length;
        }
    }

    size_t size() const {
        return length;
    }

    void clear() {
        while (!head.null()) {
            pop_front();
        }
    }

    ~LinkedListUniquePointer(){
        clear();
    }

    T& get_front() const {
        if(!head.null()){
            return head->data;
        }
    }

};


template<typename T>
struct NodeSharedPointer {

    T data;
    SharedPointer<NodeSharedPointer<T>> next;

    explicit NodeSharedPointer(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedListSharedPointer {

private:

    SharedPointer<NodeSharedPointer<T>> head;
    size_t length;

public:

    LinkedListSharedPointer() : head(nullptr), length(0) {}

    void push_front(const T& value) {
        SharedPointer<NodeSharedPointer<T>> newNode = SharedPointer<NodeSharedPointer<T>>(new NodeSharedPointer<T>(value));
        newNode->next = std::move(head);
        head = std::move(newNode);
        ++length;
    }

    bool null(){
        return head.null();
    }

    void pop_front() {
        if (!head.null()) {
            SharedPointer<NodeSharedPointer<T>> oldHead = std::move(head);
            head = std::move(oldHead->next);
            --length;
        }
    }

    size_t size() const {
        return length;
    }

    void clear() {
        while (!head.null()) {
            pop_front();
        }
    }

    ~LinkedListSharedPointer(){
        clear();
    }

    T& get_front() const {
        if(!head.null()){
            return head->data;
        }
    }

};