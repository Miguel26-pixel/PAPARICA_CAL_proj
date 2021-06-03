#include <chrono>
#include "headers/Timing.h"

std::chrono::high_resolution_clock::time_point start;

void initTime() {
    start = std::chrono::high_resolution_clock::now();
}

long calculatePerformance() {
    auto finish = std::chrono::high_resolution_clock::now();
    long micro = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

    return micro;
}