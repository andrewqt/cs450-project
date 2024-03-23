#include <chrono>

template<typename T>
struct Timer {
    Timer(T callable) {
        auto start = std::chrono::high_resolution_clock::now();
    }
    ~Timer() {
        
    }
};
