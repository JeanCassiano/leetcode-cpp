# Thread Pool — From Scratch in C++

A thread pool implemented from scratch using only C++ concurrency primitives.
Built by understanding Producer-Consumer and Token Ring patterns first, then
combining them into a reusable thread pool.

---

## What is a Thread Pool?

Creating and destroying threads is expensive. A thread pool solves this by
keeping a fixed set of worker threads alive, ready to execute tasks on demand.

```
Without pool:                    With pool:
create thread → run → destroy    thread already alive → run → sleep
create thread → run → destroy    thread already alive → run → sleep
create thread → run → destroy    thread already alive → run → sleep
    expensive × N                    cheap × N
```

---

## Architecture

```
caller          enqueue(task)
                     ↓
              [ task queue ]   ← protected by mutex
                     ↓
         ┌───────────┴───────────┐
      worker 0               worker 1  ...  worker N
      worker_loop()          worker_loop()
```

The queue is the bridge between the caller and the workers.
The caller is the **producer**. The workers are the **consumers**.
This is the Producer-Consumer pattern applied to function execution.

---

## Core Components

### The Task Queue

```cpp
std::queue<std::function<void()>> tasks;
std::mutex                        mtx;
std::condition_variable           cv;
bool                              stop = false;
```

Same structure as Producer-Consumer — the only difference is that
`int` becomes `std::function<void()>`.

### Constructor — Spawning Workers

```cpp
ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; i++) {
        workers.emplace_back(&ThreadPool::worker_loop, this);
    }
}
```

`emplace_back` constructs the thread in-place. `push_back` would try to
copy the thread — which is not allowed (`std::thread` is move-only).

### enqueue() — Submitting Tasks

```cpp
template<typename F>
auto enqueue(F&& f) -> std::future<std::invoke_result_t<F>> {
    using return_type = std::invoke_result_t<F>;

    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::forward<F>(f)
    );

    std::future<return_type> future = task->get_future();
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push([task]() { (*task)(); });
    }
    cv.notify_one();
    return future;
}
```

Three new concepts here:

| Concept | Role |
|---|---|
| `std::packaged_task` | Wraps a callable so its return value can be retrieved later |
| `std::future` | The "receipt" — call `.get()` to block and retrieve the result |
| `shared_ptr` | `packaged_task` is not copyable; `shared_ptr` is — the lambda captures the ptr |

`std::invoke_result_t<F>` deduces the return type of `F` at compile time.
`std::forward<F>(f)` preserves whether `f` was an lvalue or rvalue — perfect forwarding.

### worker_loop() — The Consumer

```cpp
void ThreadPool::worker_loop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [&] { return !tasks.empty() || stop; });
            if (stop && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task(); // execute outside the lock
    }
}
```

Why execute outside the lock? So other workers can pick up tasks concurrently.
If `task()` ran inside the lock, only one worker could execute at a time —
defeating the purpose of a thread pool.

### Destructor — Clean Shutdown

```cpp
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all(); // wake all sleeping workers
    for (std::thread& worker : workers)
        if (worker.joinable()) worker.join();
}
```

The shutdown sequence matters:
1. `stop = true` inside the lock — workers read `stop` under the same mutex
2. `notify_all` — workers sleeping in `cv.wait` wake up and see `stop`
3. `join` — main thread waits for every worker to finish cleanly

If you called `notify_all` before setting `stop`, workers could go back
to sleep before seeing the flag — and the program would hang.

---

## Usage

### Fire and Forget (void tasks)

```cpp
ThreadPool pool(4);

pool.enqueue([]() {
    std::cout << "running on " << std::this_thread::get_id() << "\n";
});
```

### Tasks with Return Values

```cpp
std::vector<std::future<int>> futures;

for (int i = 0; i < 10; i++) {
    futures.push_back(pool.enqueue([i]() { return i * 2; }));
}

for (auto& f : futures) {
    std::cout << f.get() << "\n"; // blocks until result is ready
}
```

---

## How This Connects to What Came Before

```
Producer-Consumer          Thread Pool
──────────────────         ──────────────────────
producer()          →      enqueue()
consumer()          →      worker_loop()
stock (queue<int>)  →      tasks (queue<function>)
done flag           →      stop flag
notify_one          →      notify_one (new task)
notify_all          →      notify_all (shutdown)
```

The thread pool is Producer-Consumer where the "item" is a callable
instead of a number.

---

## Key Takeaways

- **Thread pool** — reuse threads instead of creating/destroying them per task
- **enqueue()** is the producer; **worker_loop()** is the consumer
- **packaged_task** wraps a callable with a return value
- **future** is the receipt — `.get()` blocks until the result is ready
- **shared_ptr** solves the non-copyable problem of packaged_task
- **invoke_result_t** deduces return type at compile time
- **Execute outside the lock** — so multiple workers run concurrently
- **Shutdown order matters** — set flag → notify → join

---

## Further Reading

- *C++ Concurrency in Action* — Anthony Williams (Chapter 9: Advanced thread management)
- *Effective Modern C++* — Items 36–40 (futures, async, condition_variable)
- [cppreference — std::packaged_task](https://en.cppreference.com/w/cpp/thread/packaged_task)
- [cppreference — std::future](https://en.cppreference.com/w/cpp/thread/future)
- [cppreference — std::invoke_result](https://en.cppreference.com/w/cpp/types/result_of)