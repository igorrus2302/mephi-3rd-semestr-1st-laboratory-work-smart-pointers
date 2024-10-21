#include "pointer_tests.h"
#include "shared_pointer.h"
#include "unique_pointer.h"
#include "test_structure.h"
#include "progress_bar.h"

#include <chrono>
#include <iostream>
#include <sstream>
#include "memory"
#include "cassert"

std::string startUniquePointerTests() {

    std::ostringstream result;
    result << "Unique pointer tests:\n\n";

    result << "  Functional test 1 (element addition): ";
    {
        try {
            UniquePointer<int> p1(new int(10));
            assert(*p1 == 10);
            result << "Passed" << '\n';
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (release test): ";
    {
        try {
            UniquePointer<int> p1(new int(20));
            int *rawPtr = p1.release();
            assert(*rawPtr == 20);
            result << "Passed" << '\n';
            delete rawPtr;
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<UniquePointer<int>> pointers;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(UniquePointer<int>(new int(i)));

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<UniquePointer<int>> pointers;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(UniquePointer<int>(new int(i)));

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<UniquePointer<int>> pointers;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(UniquePointer<int>(new int(i)));

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}


std::string startSharedPointerTests() {
    std::ostringstream result;
    result << "Shared pointer tests:\n\n";

    result << "  Functional test 1 (shared pointer initialization): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (shared pointer release): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 3 (shared pointer(other shared)): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            SharedPointer<int> p2(p1);
            result << (*p2 == 10 && *p2 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<SharedPointer<int>> pointers;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                int *p = new int(i);
                pointers.push_back(SharedPointer<int>(p));

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<SharedPointer<int>> pointers;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                int *p = new int(i);
                pointers.push_back(SharedPointer<int>(p));

                if (i % (testSize / 100) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<SharedPointer<int>> pointers;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                int *p = new int(i);
                pointers.push_back(SharedPointer<int>(p));

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}


std::string startLinkedListUniquePointerTests() {
    std::ostringstream result;
    result << "Linked list unique pointer tests:\n\n";

    result << "  Functional test 1 (pushing elements): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            result << (list.size() == 1 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (push, pop elements and size()): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            list.pop_front();
            result << (list.size() == 0 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 3 (null() function): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            result << (list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 4 (clear() function): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            list.push_front(20);
            list.clear();
            result << (list.size() == 0 && list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListUniquePointer<int> list;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListUniquePointer<int> list;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 100) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListUniquePointer<int> list;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}


std::string startLinkedListSharedPointerTests() {
    std::ostringstream result;
    result << "Linked list shared pointer tests:\n\n";

    result << "  Functional test 1 (pushing elements): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            result << (list.size() == 1 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (push, pop elements and size()): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            list.pop_front();
            result << (list.size() == 0 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 3 (null() function): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            result << (list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 4 (clear() function): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            list.push_front(20);
            list.clear();
            result << (list.size() == 0 && list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListSharedPointer<int> list;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListSharedPointer<int> list;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 100) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            LinkedListSharedPointer<int> list;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                list.push_front(i);

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms, Size: " << list.size() << "\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}


std::string startStdUniquePointerTests() {
    std::ostringstream result;
    result << "Std unique pointer tests:\n\n";

    result << "  Functional test 1 (initialization): ";
    {
        try {
            std::unique_ptr<int> p1(new int(10));
            result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (release): ";
    {
        try {
            std::unique_ptr<int> p1(new int(20));
            int *rawPtr = p1.release();
            result << (*rawPtr == 20 ? "Passed" : "Failed") << "\n";
            delete rawPtr;
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::unique_ptr<int>> pointers;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::unique_ptr<int>(new int(i)));

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::unique_ptr<int>> pointers;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::unique_ptr<int>(new int(i)));

                if (i % (testSize / 100) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::unique_ptr<int>> pointers;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::unique_ptr<int>(new int(i)));

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}

std::string startStdSharedPointerTests() {
    std::ostringstream result;
    result << "Std shared pointer tests:\n\n";

    result << "  Functional test 1(make shared pointer): ";
    {
        try {
            std::shared_ptr<int> p1 = std::make_shared<int>(10);
            result << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Functional test 2 (initialization and copying): ";
    {
        try {
            std::shared_ptr<int> p1 = std::make_shared<int>(20);
            std::shared_ptr<int> p2 = p1;
            result << (*p2 == 20 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 1 (small): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::shared_ptr<int>> pointers;

            int testSize = 1000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::make_shared<int>(i));

                if (i % (testSize / 10) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 2 (medium): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::shared_ptr<int>> pointers;

            int testSize = 100000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::make_shared<int>(i));

                if (i % (testSize / 100) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            result << "Failed with unknown exception\n";
        }
    }

    result << "  Load test 3 (big): ";
    {
        try {
            auto start = std::chrono::high_resolution_clock::now();
            std::vector<std::shared_ptr<int>> pointers;

            int testSize = 10000000;

            for (int i = 0; i < testSize; ++i) {
                pointers.push_back(std::make_shared<int>(i));

                if (i % (testSize / 1000) == 0) {
                    printProgressBar(i + 1, testSize);
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            result << "Time: " << duration << " ms\n\n";
        } catch (const std::exception &e) {
            result << "Failed with exception: " << e.what() << "\n\n";
        } catch (...) {
            result << "Failed with unknown exception\n\n";
        }
    }

    return result.str();
}
