#include "progress_bar.h"
#include <iostream>

void printProgressBar(int current, int total) {
    int width = 50;
    float progress = (float)current / total;
    int pos = width * progress;
    std::cout << "[";
    for (int i = 0; i < width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}