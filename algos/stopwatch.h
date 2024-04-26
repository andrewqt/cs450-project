#include <chrono>
#include <string>
#include <iostream>

struct StopWatch {
    StopWatch(std::string name = "") : name(name), done(false), total() {
        start = std::chrono::high_resolution_clock::now();
    }
    void pause() {
        auto end = std::chrono::high_resolution_clock::now();
        total += end - start;
    }
    void resume() {
        start = std::chrono::high_resolution_clock::now();
    }
    ~StopWatch() {
        std::cout << name + " Time: " << total.count() << " ms" << std::endl;
    }
    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::duration<double, std::milli> total;
    bool done;
};
