#include <iostream>
#include <thread>
#include <functional>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>
#include <type_traits>

/**
 * @brief A simple thread pool implementation using C++ concurrency primitives.
 *
 * Manages a fixed number of worker threads that continuously wait for tasks.
 * Tasks are submitted via enqueue() and executed concurrently by the workers.
 * Supports return values via std::future.
 */
class ThreadPool {
public:
    /**
     * @brief Constructs the thread pool and spawns worker threads.
     * @param num_threads Number of worker threads to create.
     */
    ThreadPool(size_t num_threads);

    /**
     * @brief Destructs the thread pool.
     *
     * Sets the stop flag, wakes all workers, and joins every thread
     * before destroying the object.
     */
    ~ThreadPool();

    /**
     * @brief Submits a task to the queue and returns a future for its result.
     *
     * Wraps the callable in a packaged_task so the return value can be
     * retrieved later via the returned std::future.
     *
     * @tparam F Callable type (lambda, function pointer, functor).
     * @param f  The callable to execute.
     * @return   std::future holding the result of f().
     */
    template<typename F>
    auto enqueue(F&& f) -> std::future<std::invoke_result_t<F>> {
        using return_type = std::invoke_result_t<F>;

        // Wrap the callable in a packaged_task so we can extract a future.
        // shared_ptr is required because std::function must be copyable,
        // but packaged_task is not — the ptr is copied, not the task itself.
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::forward<F>(f)
        );

        std::future<return_type> future = task->get_future();

        {
            std::unique_lock<std::mutex> lock(mtx);
            // Push a wrapper lambda that invokes the packaged_task
            tasks.push([task]() { (*task)(); });
        }

        // Wake one sleeping worker
        cv.notify_one();
        return future;
    }

private:
    /**
     * @brief Main loop executed by each worker thread.
     *
     * Sleeps on the condition variable until a task is available or
     * the pool is stopping. Pops and executes one task per iteration.
     */
    void worker_loop();

    std::vector<std::thread>            workers;  // pool of worker threads
    std::queue<std::function<void()>>   tasks;    // pending task queue
    std::mutex                          mtx;      // protects the task queue
    std::condition_variable             cv;       // coordinates workers
    bool                                stop = false; // shutdown signal
};

// ─────────────────────────────────────────────
// Implementation
// ─────────────────────────────────────────────

ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; i++) {
        // Each thread immediately starts running worker_loop
        workers.emplace_back(&ThreadPool::worker_loop, this);
    }
}

void ThreadPool::worker_loop() {
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(mtx);

            // Sleep until there is a task OR the pool is stopping
            cv.wait(lock, [&] { return !tasks.empty() || stop; });

            // If shutting down and no tasks remain, exit the loop
            if (stop && tasks.empty()) return;

            // Claim the next task
            task = std::move(tasks.front());
            tasks.pop();
        }

        // Execute outside the lock so other workers can pick up tasks
        task();
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true; // signal all workers to stop after draining the queue
    }

    cv.notify_all(); // wake every sleeping worker

    for (std::thread& worker : workers) {
        if (worker.joinable()) worker.join();
    }
}

// ─────────────────────────────────────────────
// Demo
// ─────────────────────────────────────────────

std::mutex print_mutex;

int main() {
    ThreadPool pool(4);

    // Fire-and-forget tasks (void return)
    std::vector<std::future<void>> void_futures;
    for (int i = 0; i < 5; i++) {
        void_futures.push_back(pool.enqueue([i]() {
            std::unique_lock<std::mutex> lock(print_mutex);
            std::cout << "Task " << i
                      << " running on thread " << std::this_thread::get_id() << "\n";
        }));
    }
    for (auto& f : void_futures) f.get();
    // Tasks with return values via std::future
    std::vector<std::future<int>> futures;
    for (int i = 0; i < 10; i++) {
        futures.push_back(pool.enqueue([i]() { return i * 2; }));
    }

    std::cout << "\nResults:\n";
    for (auto& f : futures) {
        std::cout << f.get() << "\n";
    }

    return 0;
}