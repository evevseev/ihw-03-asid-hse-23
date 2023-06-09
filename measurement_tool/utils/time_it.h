#ifndef MEASUREMENT_TOOL_TIME_IT_H
#define MEASUREMENT_TOOL_TIME_IT_H

#include <chrono>

// Function that measures time of execution of func and returns it in microseconds
template<typename Func>
size_t time(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

#endif
