# Concurrency in C++ — Core Concepts

A practical guide built from implementing a Producer-Consumer system from scratch.

---

## The Problem

When multiple threads access shared data at the same time, things break:

```
Thread A reads  x = 0
Thread B reads  x = 0
Thread A writes x = 1
Thread B writes x = 1   ← A's write is lost
```

Both threads read the same value, both increment, and one update disappears.
This is a **race condition** — the result depends on which thread runs first.

The solution is synchronization: making threads take turns.

---

## Mutex — Mutual Exclusion

A mutex is a lock. Only one thread can hold it at a time.

```cpp
std::mutex mtx;

mtx.lock();
// critical section — only one thread here at a time
shared_queue.push(item);
mtx.unlock();
```

**The problem with manual lock/unlock:** if an exception is thrown between
`lock()` and `unlock()`, the mutex stays locked forever — **deadlock**.

---

## unique_lock — RAII Mutex Management

`unique_lock` wraps a mutex and releases it automatically when it goes out of scope,
even if an exception is thrown. This is called **RAII** (Resource Acquisition Is Initialization).

```cpp
{
    std::unique_lock<std::mutex> lock(mtx); // locks here
    shared_queue.push(item);
}   // unlocks here automatically — no matter what happens
```

Think of it as a smart pointer, but for mutexes.

| | `mtx.lock()` | `unique_lock` |
|---|---|---|
| Unlocks automatically | ❌ | ✅ |
| Exception safe | ❌ | ✅ |
| Works with condition_variable | ❌ | ✅ |

---

## condition_variable — Sleeping Instead of Spinning

Without `condition_variable`, a thread that's waiting for data has to keep checking:

```cpp
// BAD — busy waiting, burns CPU
while (queue.empty()) {
    // spinning... spinning... spinning...
}
```

`condition_variable` lets a thread **sleep** until something changes:

```cpp
std::condition_variable cv;

// Consumer — sleeps until condition is true
cv.wait(lock, [] { return !queue.empty() || done; });

// Producer — wakes up sleeping threads
cv.notify_one();   // wake one thread
cv.notify_all();   // wake all threads
```

### What cv.wait does internally

```
1. check condition → if true, continue immediately
2. if false: release the mutex and sleep
3. someone calls notify
4. wake up, reacquire the mutex
5. check condition again → if false, go back to step 2
```

### Why the condition lambda matters — Spurious Wakeups

The OS can wake a thread **without anyone calling notify**. This is called a
**spurious wakeup** and is allowed by the C++ standard.

Without the condition, the thread would process an empty queue and crash.
The lambda acts as a guard — if the wakeup was spurious, the thread goes back to sleep.

```cpp
// cv.wait(lock, condition) expands to:
while (!condition()) {
    cv.wait(lock);
}
```

---

## Producer-Consumer Pattern

A classic concurrency pattern where:
- **Producer** generates data and puts it in a shared queue
- **Consumer** takes data from the queue and processes it
- The queue is the **buffer** between them

```
Producer → [  queue  ] → Consumer
              mutex
               cv
```

### Full Implementation

```cpp
std::queue<int>         stock;   // shared buffer
std::mutex              mtx;     // protects the queue
std::condition_variable cv;      // coordinates producer and consumer
bool                    done = false;

void producer() {
    for (int i = 1; i <= 10; i++) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stock.push(i);
            cv.notify_all();                            // wake consumers
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    {
        std::unique_lock<std::mutex> lock(mtx);
        done = true;
        cv.notify_all();                                // wake consumers one last time
    }                                                   // so they see done = true
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [] { return !stock.empty() || done; });

        if (stock.empty() && done) return;              // nothing left to do

        std::cout << "Consumed: " << stock.front() << "\n";
        stock.pop();
    }
}

int main() {
    std::thread p(producer);
    std::thread c1(consumer);
    std::thread c2(consumer);

    p.join();
    c1.join();
    c2.join();
}
```

### Why notify_all with multiple consumers?

```
notify_one → wakes ONE consumer
             the other might be sleeping with items in the queue

notify_all → wakes ALL consumers
             they compete for the next item — only one wins the mutex
             safe and correct
```

### Why the final notify after done = true?

```
Producer finishes the loop
done = true

Consumer is sleeping in cv.wait
Nobody calls notify
Consumer sleeps forever → DEADLOCK

Solution: notify after setting done = true
Consumer wakes up, sees done = true and empty queue → returns cleanly
```

---

## The Synchronization Triangle

Every concurrent system that shares a queue uses this pattern:

```
┌─────────────────────────────────────────┐
│                                         │
│   mutex     → protects shared data      │
│   cv.wait   → sleep / release mutex     │
│   notify    → signal that state changed │
│                                         │
│   condition → guard against spurious    │
│               wakeups                   │
└─────────────────────────────────────────┘
```

This is the same pattern inside `std::thread_pool`, `std::async`,
message queues, and most concurrent systems at scale.

---

## Key Takeaways

- **Race condition** — threads accessing shared data without synchronization
- **mutex** — only one thread in the critical section at a time
- **unique_lock** — RAII mutex: releases automatically, exception-safe
- **condition_variable** — sleep instead of spin; wake up on signal
- **spurious wakeup** — OS can wake threads randomly; always use a condition lambda
- **notify_one** — wake one waiter; **notify_all** — wake all waiters
- **done flag** — signals consumers to terminate cleanly; always notify after setting it

---

## Further Reading

- *C++ Concurrency in Action* — Anthony Williams
- *Effective Modern C++* — Item 39 (condition_variable)
- [cppreference — std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [cppreference — std::unique_lock](https://en.cppreference.com/w/cpp/thread/unique_lock)