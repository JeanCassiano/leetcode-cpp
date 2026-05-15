#include <iostream>
#include <string>
#include <vector>
#include <chrono>

// ============================================================
// Goal: see in practice the cost of copying vs moving
// ============================================================

// Receives by value (forces a copy of the entire vector)
void process_copy(std::vector<int> v) {
    v.push_back(0);
}

// Receives by rvalue reference (move — no copy)
void process_move(std::vector<int>&& v) {
    std::vector<int> internal = std::move(v); // "steals" the data
    internal.push_back(0);
}

// ============================================================
// Perfect forwarding — accepts lvalue OR rvalue and forwards
// correctly to process_move using universal reference + std::forward
// ============================================================
template<typename T>
void send(T&& v) {
    process_move(std::forward<T>(v));
}

// ============================================================
// QUESTIONS:
//
//    std::vector<int> v = {1, 2, 3};
//
//    a) process_copy(v)            — copy or move?
//    b) process_copy(std::move(v)) — copy or move?
//    c) process_move(v)             — does it compile? why?
//    d) process_move(std::move(v))  — copy or move?
//
// ANSWERS:
//    a) copy   — lvalue passed to a by-value parameter: copy constructor
//    b) move   — rvalue passed to a by-value parameter: move constructor (cheaper than copy, but not the same as &&)
//    c) NO     — process_move only accepts rvalue (&&). v is an lvalue.
//    d) move   — std::move converts v to rvalue, && accepts it, no copy at all. v becomes empty after.
// ============================================================

int main() {
    const int SIZE = 10'000'000;
    std::vector<int> v(SIZE, 42);

    // Benchmark copy
    auto start = std::chrono::high_resolution_clock::now();
    process_copy(v);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "copy: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "µs\n";

    // Benchmark move
    start = std::chrono::high_resolution_clock::now();
    process_move(std::move(v));
    end = std::chrono::high_resolution_clock::now();
    std::cout << "move: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "µs\n";

    // Why is v empty here after the move?
    // Answer: std::move transferred ownership of v's internal pointer.
    //         v no longer points to any data — it was "stolen" by process_move.
    std::cout << "size of v after move: " << v.size() << "\n";

    return 0;
}