#include "load_tests.h"
#include "shared_pointer.h"
#include "unique_pointer.h"
//#include "progress_bar.h"
#include "test_structure.h"

#include <chrono>
#include <iostream>

void loadUniquePointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<UniquePointer<int>> pointers;

        for (int i = 0; i < testSize; ++i) {
            pointers.push_back(UniquePointer<int>(new int(i)));

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}

void loadSharedPointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<SharedPointer<int>> pointers;

        for (int i = 0; i < testSize; ++i) {
            int *p = new int(i);
            pointers.push_back(SharedPointer<int>(p));

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}

void loadLinkedListUniquePointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        LinkedListUniquePointer<int> list;

        for (int i = 0; i < testSize; ++i) {
            list.push_front(i);

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms, Size: " << list.size() << "\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}

void loadLinkedListSharedPointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        LinkedListSharedPointer<int> list;

        for (int i = 0; i < testSize; ++i) {
            list.push_front(i);

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms, Size: " << list.size() << "\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}

void loadStdUniquePointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::unique_ptr<int>> pointers;

        for (int i = 0; i < testSize; ++i) {
            pointers.push_back(std::unique_ptr<int>(new int(i)));

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}

void loadStdSharedPointerTests(int testSize){
    try {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::shared_ptr<int>> pointers;

        for (int i = 0; i < testSize; ++i) {
            pointers.push_back(std::make_shared<int>(i));

            /*if (i % (testSize / 100) == 0) {
                printProgressBar(i + 1, testSize);
            }*/
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Time: " << duration << " ms\n";
    } catch (const std::exception &e) {
        std::cout << "Failed with exception: " << e.what() << "\n";
    } catch (...) {
        std::cout << "Failed with unknown exception\n";
    }
}