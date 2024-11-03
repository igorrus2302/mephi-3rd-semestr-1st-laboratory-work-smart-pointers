#include "pointer_tests.h"
#include "shared_pointer.h"
#include "unique_pointer.h"
#include "test_structure.h"
#include "load_tests.h"

#include <chrono>
#include <iostream>
#include "memory"
#include "cassert"


void UniquePointerTests() {
    std::cout << "Unique pointer tests:\n\n";

    std::cout << "  Functional test 1 (element addition): ";
    {
        try {
            UniquePointer<int> p1(new int(10));
            assert(*p1 == 10);
            std::cout << "Passed\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (release test): ";
    {
        try {
            UniquePointer<int> p1(new int(20));
            int *rawPtr = p1.release();
            assert(*rawPtr == 20);
            std::cout << "Passed\n";
            delete rawPtr;
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 3 (indexation test): ";
    {
        try {
            UniquePointer<int[]> up(new int[5]);
            for (int i = 0; i < 5; ++i) {
                up[i] = i * 10;
            }
            for (int i = 0; i < 5; ++i) {
                assert(up[i] == i * 10);
            }
            std::cout << "Passed\n";
            } catch (const std::exception &e) {
                std::cout << "Failed with exception: " << e.what() << "\n";
            } catch (...) {
                std::cout << "Failed with unknown exception\n";
            }
    }

    std::cout << "  Functional test 4 (subtipization test): ";
    {
        try {
            class C2 {
            public:
                virtual int getValue() const {
                    return 20;
                }
                virtual ~C2() = default;
            };

            class C1 : public C2 {
            public:
                int getValue() const override {
                    return 30;
                }
            };

            class C3 : public C2 {
            public:
                int getValue() const override {
                    return 40;
                }
            };

            UniquePointer<C1> derivedPtr1(new C1());
            UniquePointer<C2> basePtr1 = std::move(derivedPtr1);

            assert(derivedPtr1.null());
            assert(basePtr1.get()->getValue() == 30);
            assert(basePtr1.get()->getValue() == 30);

            UniquePointer<C3> derivedPtr2(new C3());
            UniquePointer<C2> basePtr2 = std::move(derivedPtr2);

            assert(derivedPtr2.null());
            assert(basePtr2.get()->getValue() == 40);

            std::cout << "Passed\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadUniquePointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadUniquePointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadUniquePointerTests(testSize);
    }
    std::cout << "\n\n";
}

void SharedPointerTests() {
    std::cout << "Shared pointer tests:\n\n";

    std::cout << "  Functional test 1 (shared pointer initialization): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            std::cout << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (shared pointer release): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            std::cout << (*p1 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 3 (shared pointer(other shared)): ";
    {
        try {
            SharedPointer<int> p1(new int(10));
            SharedPointer<int> p2(p1);
            std::cout << (*p2 == 10 && *p2 == 10 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 4 (subtipization test): ";
    {
        try {
            class C1 {
            public:
                virtual int getValue() const {
                    return 10;
                }
                virtual ~C1() = default;
            };

            class C2 : public C1 {
            public:
                int getValue() const override {
                    return 20;
                }
            };

            SharedPointer<C1> derivedPtr1(new C2());
            SharedPointer<C2> basePtr1 = SharedPointer<C2>::static_pointer_cast(derivedPtr1);

            assert(basePtr1.use_count() == 2);

            SharedPointer<C2> basePtr2 = basePtr1;

            assert(basePtr1.use_count() == 3);
            assert(basePtr1->getValue() == 20);

            std::cout << "Passed" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadSharedPointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadSharedPointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadSharedPointerTests(testSize);
    }
    std::cout << "\n\n";
}

void LinkedListUniquePointerTests() {
    std::cout << "Linked list unique pointer tests:\n\n";

    std::cout << "  Functional test 1 (pushing elements): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            std::cout << (list.size() == 1 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (push, pop elements and size()): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            list.pop_front();
            std::cout << (list.size() == 0 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 3 (null() function): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            std::cout << (list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 4 (clear() function): ";
    {
        try {
            LinkedListUniquePointer<int> list;
            list.push_front(10);
            list.push_front(20);
            list.clear();
            std::cout << (list.size() == 0 && list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadLinkedListUniquePointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadLinkedListUniquePointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadLinkedListUniquePointerTests(testSize);
    }
    std::cout << "\n\n";
}

void LinkedListSharedPointerTests() {
    std::cout << "Linked list shared pointer tests:\n\n";

    std::cout << "  Functional test 1 (pushing elements): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            std::cout << (list.size() == 1 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (push, pop elements and size()): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            list.pop_front();
            std::cout << (list.size() == 0 ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 3 (null() function): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            std::cout << (list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 4 (clear() function): ";
    {
        try {
            LinkedListSharedPointer<int> list;
            list.push_front(10);
            list.push_front(20);
            list.clear();
            std::cout << (list.size() == 0 && list.null() ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadLinkedListSharedPointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadLinkedListSharedPointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadLinkedListSharedPointerTests(testSize);
    }
    std::cout << "\n\n";
}

void StdUniquePointerTests() {
    std::cout << "Std unique pointer tests:\n\n";

    std::cout << "  Functional test 1 (initialization): ";
    {
        try {
            std::unique_ptr<int> p1(new int(10));
            std::cout << ((*p1 == 10) ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (release): ";
    {
        try {
            std::unique_ptr<int> p1(new int(20));
            int *rawPtr = p1.release();
            std::cout << ((*rawPtr == 20) ? "Passed" : "Failed") << "\n";
            delete rawPtr;
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadStdUniquePointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadStdUniquePointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadStdUniquePointerTests(testSize);
    }
    std::cout << "\n\n";
}

void StdSharedPointerTests() {
    std::cout << "Std shared pointer tests:\n\n";

    std::cout << "  Functional test 1 (make shared pointer): ";
    {
        try {
            std::shared_ptr<int> p1 = std::make_shared<int>(10);
            std::cout << ((*p1 == 10) ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Functional test 2 (initialization and copying): ";
    {
        try {
            std::shared_ptr<int> p1 = std::make_shared<int>(20);
            std::shared_ptr<int> p2 = p1;
            std::cout << ((*p2 == 20) ? "Passed" : "Failed") << "\n";
        } catch (const std::exception &e) {
            std::cout << "Failed with exception: " << e.what() << "\n";
        } catch (...) {
            std::cout << "Failed with unknown exception\n";
        }
    }

    std::cout << "  Load test 1 (small): ";
    {
        int testSize = 1000;
        loadStdSharedPointerTests(testSize);
    }

    std::cout << "  Load test 2 (medium): ";
    {
        int testSize = 100'000;
        loadStdSharedPointerTests(testSize);
    }

    std::cout << "  Load test 3 (big): ";
    {
        int testSize = 10'000'000;
        loadStdSharedPointerTests(testSize);
    }
    std::cout << "\n\n";
}
