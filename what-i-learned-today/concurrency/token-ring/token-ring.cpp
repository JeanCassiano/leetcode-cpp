/**
 * @file token_passing.cpp
 * @brief Demonstration of token passing between threads using C++ mutex and condition_variable.
 * 
 * This program demonstrates a simple synchronization pattern where multiple threads
 * take turns executing in a round-robin fashion. A shared "token" variable determines
 * which thread is allowed to proceed at a given time. Threads wait for their turn using
 * a condition variable and a mutex to ensure proper synchronization.
 *
 * Key Concepts:
 *  - std::thread: creating concurrent threads
 *  - std::mutex: protecting shared data (the token)
 *  - std::condition_variable: coordinating threads in a round-robin manner
 *  - Token passing: ensures threads execute in a strict order
 *
 * Author: Your Name
 * Date: 2026-05-16
 */

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>

// Total number of threads
int NUM_THREADS = 3;

// Mutex to protect the shared token
std::mutex mtx;

// Condition variable to coordinate threads
std::condition_variable cv;

// Shared token that determines which thread can proceed
int token = 0;

// Number of times each thread should perform its action
int ROUNDS = 3;

/**
 * @brief Worker thread function
 * 
 * Each thread waits until the shared token matches its ID (modulo NUM_THREADS),
 * prints a message indicating it received the token, increments the token,
 * and then notifies all other threads to check if it's their turn.
 * 
 * @param id Thread ID (0-based index)
 */
void worker(int id) {
    for (int i = 0; i < ROUNDS; i++) {
        {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's this thread's turn
            cv.wait(lock, [&]{ return token % NUM_THREADS == id; });

            // Print current state and increment token
            std::cout << "Thread " << id 
                      << " received token = " << token 
                      << ". Incremented. Token = " << token++ 
                      << " Round: " << i << std::endl;

            // Notify all threads that token has changed
            cv.notify_all();
        }
    }
}

/**
 * @brief Main function
 * 
 * Launches NUM_THREADS worker threads and waits for them to finish.
 * Demonstrates strict round-robin execution using a shared token.
 */
int main() {
    std::vector<std::thread> threads;

    // Launch worker threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(worker, i);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}