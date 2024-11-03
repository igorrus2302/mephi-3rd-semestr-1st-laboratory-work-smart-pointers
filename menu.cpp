#include "menu.h"
#include "pointer_tests.h"

#include <iostream>


void functions(){
    std::cout << "1. Unique pointer tests\n";
    std::cout << "2. Shared pointer tests\n";
    std::cout << "3. Linked list unique pointer tests\n";
    std::cout << "4. Linked list shared pointer tests\n";
    std::cout << "5. Std unique pointer tests\n";
    std::cout << "6. Std shared pointer tests\n";
    std::cout << "7. Exit\n";
    std::cout << "Input number of function : ";
}

void openMenu(){
    functions();
    int n;
    std::cin >> n;
    std::cout << "\n";
    while (n != 7) {
        if ((n < 1) || (n >7))
        {
            std::cout << "Wrong number input, please try again.\n\n";
            functions();
        }
        else{
            switch (n){
                case(1):
                    UniquePointerTests();
                    functions();
                    break;
                case (2):
                    SharedPointerTests();
                    functions();
                    break;
                case (3):
                    LinkedListUniquePointerTests();
                    functions();
                    break;
                case (4):
                    LinkedListSharedPointerTests();
                    functions();
                    break;
                case (5):
                    StdUniquePointerTests();
                    functions();
                    break;
                case (6):
                    StdSharedPointerTests();
                    functions();
                    break;
                case (7):
                    exit(0);
            }
        }
        std::cin >> n;
        std::cout << "\n";
    }
}