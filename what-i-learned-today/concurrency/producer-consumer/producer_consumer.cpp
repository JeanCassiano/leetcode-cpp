/**
 * @file producer_consumer.cpp
 * @brief Demonstration of the classic Producer-Consumer problem using C++ threads.
 * 
 * This program demonstrates a basic producer-consumer scenario using multiple 
 * threads. One producer thread generates random numbers and places them into 
 * a shared queue, while multiple consumer threads retrieve and process these 
 * numbers. The shared queue is protected using a mutex and coordinated using 
 * a condition variable to avoid race conditions and ensure proper synchronization.
 *
 * Key Concepts:
 *  - std::thread: creating and running concurrent threads
 *  - std::mutex: mutual exclusion to protect access to shared data
 *  - std::condition_variable: coordinating producer and consumer threads
 *  - std::queue: acting as a shared buffer between producers and consumers
 *
 * Changes in this version:
 *  - Added multiple consumer threads to process items concurrently.
 *  - Each consumer prints its unique thread ID for clarity.
 *  - Used cv.notify_all() to wake all waiting consumers when new items are available.
 *
 */

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstdlib>
#include <chrono>

// Shared queue (buffer) between producer and consumers
std::queue<int> stock;

// Mutex to protect access to the shared queue
std::mutex mtx;

// Condition variable to notify consumers when new items are available
std::condition_variable cv;

// Flag indicating whether the producer has finished producing
bool done = false;

/**
 * @brief Producer thread function
 * 
 * Generates random numbers between 1 and 10, pushes them into the shared queue, 
 * and notifies all waiting consumers. After producing all items, sets the 'done' 
 * flag to true and notifies all consumers one final time.
 */
void producer() {
    for (int i = 0; i < 100; i++) {
        {
            std::unique_lock<std::mutex> lock(mtx);  // Lock the mutex to protect the queue
            int j = std::rand() % 10 + 1;            // Generate a random number 1..10
            std::cout << "Produced: " << j << std::endl;
            stock.push(j);                            // Add the number to the queue
            cv.notify_all();                          // Wake up all waiting consumers
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    }

    // Signal that production is done
    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();  // Wake up any consumers still waiting
    }
}

/**
 * @brief Consumer thread function
 * 
 * Continuously waits for items in the shared queue and processes them.
 * If the queue is empty and the producer has finished, the consumer exits.
 * Each consumer prints its unique thread ID to identify which thread consumed which item.
 */
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        // Wait until there is an item to consume or the producer is done
        cv.wait(lock, [] { return !stock.empty() || done; });

        // If queue is empty and producer is done, exit the loop
        if (stock.empty() && done) return;

        // Consume an item from the queue
        std::cout << "Thread " << std::this_thread::get_id() 
                  << " Consumed: " << stock.front() << std::endl;
        stock.pop();
    }
}

/**
 * @brief Main function
 * 
 * Launches one producer thread and multiple consumer threads, then waits for all 
 * threads to finish. This demonstrates concurrent consumption of a shared queue.
 */
int main() {
    std::thread p(producer);   // Launch producer thread
    std::thread c1(consumer);  // Launch first consumer thread
    std::thread c2(consumer);  // Launch second consumer thread

    // Wait for all threads to finish
    p.join();
    c1.join();
    c2.join();

    return 0;
}