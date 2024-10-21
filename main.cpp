#include <chrono>
#include <iostream>
#include "test_structure.h"
#include "pointer_tests.h"

int main() {

    std::cout << startUniquePointerTests();
    std::cout << startStdUniquePointerTests();
    std::cout << startLinkedListUniquePointerTests();
    std::cout << startSharedPointerTests();
    std::cout << startStdSharedPointerTests();
    std::cout << startLinkedListSharedPointerTests();

    return 0;
}
