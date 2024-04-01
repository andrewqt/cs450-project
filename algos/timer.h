#include <chrono>
#include <string>
#include <iostream>

struct Timer {
    Timer(std::string name) : name(name), done(false) {
        start = std::chrono::high_resolution_clock::now();
    }
    void stop() {
        if (!done) {
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> elapsed = end - start;
            std::cout << name + " Time: " << elapsed.count() << " ms" << std::endl;
            done = true;
        }
    }
    ~Timer() {
        stop();
    }
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    bool done;
};
