# Token Passing & Round-Robin Thread Synchronization

A practical implementation of the Token Ring protocol using C++ threads,
built on top of the Producer-Consumer synchronization primitives.

---

## What is Token Passing?

Token Ring is a classic network protocol where only the node holding the
**token** is allowed to transmit. Applied to threads, it enforces **strict
ordering** — threads execute in a round-robin sequence, one at a time.

```
Thread 0 → Thread 1 → Thread 2 → Thread 0 → ...
  holds      waits      waits
  token
```

This is useful when tasks must run in a specific order, or when you want
to avoid starvation — every thread is guaranteed a turn.

---

## How It Works

### The Token

A single shared integer acts as the token:

```cpp
int token = 0;
```

Each thread waits until the token "belongs" to it:

```cpp
cv.wait(lock, [&]{ return token % NUM_THREADS == id; });
```

After executing, it increments the token and wakes everyone up:

```cpp
token++;
cv.notify_all();
```

The next thread in line sees `token % NUM_THREADS == its_id` and proceeds.
All others go back to sleep.

### Round-Robin with Modulo

```
NUM_THREADS = 3

token=0  → 0 % 3 = 0 → Thread 0's turn
token=1  → 1 % 3 = 1 → Thread 1's turn
token=2  → 2 % 3 = 2 → Thread 2's turn
token=3  → 3 % 3 = 0 → Thread 0's turn again
token=4  → 4 % 3 = 1 → Thread 1's turn again
...
```

Modulo maps an ever-increasing counter to a circular sequence.
No resets needed — it works for any number of rounds.

---

## notify_one vs notify_all — When to Use Each

This is one of the most common decisions in concurrent design:

```cpp
cv.notify_one();  // wake exactly one waiting thread
cv.notify_all();  // wake all waiting threads
```

### notify_one — use when any waiter can do the job

```cpp
// Producer-Consumer with multiple consumers:
// Any consumer can process the next item
// Waking one is enough — cheaper
cv.notify_one();
```

### notify_all — use when only a specific thread should proceed

```cpp
// Token Ring:
// Only Thread N can proceed — the others must check and go back to sleep
// If you used notify_one, you might wake the wrong thread
// That thread checks its condition, fails, goes back to sleep
// The right thread never wakes up — DEADLOCK
cv.notify_all();
```

**Rule of thumb:**

| Situation | Use |
|---|---|
| Any waiter can handle the event | `notify_one` |
| Only a specific waiter should proceed | `notify_all` |
| You're not sure | `notify_all` (safer, slightly more expensive) |

---

## Condition Variable — Deeper Look

### The Predicate Guards Against Two Things

```cpp
cv.wait(lock, [&]{ return token % NUM_THREADS == id; });
```

**1. Spurious wakeups** — the OS can wake a thread with no notify call.
Without the predicate, the thread would execute out of turn.

**2. Wrong notify** — in Token Ring, all threads wake on `notify_all`.
The predicate filters out threads that shouldn't run yet.

Both cases are handled by the same mechanism: if the condition is false,
the thread goes back to sleep automatically.

### The Wait Loop (What the compiler generates)

```cpp
// cv.wait(lock, predicate) expands to:
while (!predicate()) {
    cv.wait(lock);  // release mutex, sleep, reacquire mutex on wake
}
```

Every wakeup re-evaluates the condition. No shortcuts.

---

## Deadlock — What It Is and How to Avoid It

A deadlock occurs when threads are waiting for each other indefinitely:

```
Thread A holds mutex_1, waiting for mutex_2
Thread B holds mutex_2, waiting for mutex_1
→ both wait forever
```

In Token Ring, a deadlock would happen if:

```cpp
// Using notify_one in Token Ring:
token = 1  → Thread 1's turn
notify_one → wakes Thread 2 (wrong thread)
Thread 2:  1 % 3 == 2? false → goes back to sleep
Thread 1:  never woken → waits forever → DEADLOCK
```

`notify_all` prevents this — every thread gets a chance to check.

---

## Starvation vs Fairness

**Starvation** — a thread never gets CPU time because others keep running.

```
// Without token passing:
Thread 0 runs 100 times
Thread 1 runs 3 times      ← starving
Thread 2 runs 0 times      ← completely starved
```

**Token Ring guarantees fairness** — every thread gets exactly the same
number of turns, in strict order. No thread can run twice before others run once.

```
Round 1: Thread 0 → Thread 1 → Thread 2
Round 2: Thread 0 → Thread 1 → Thread 2
Round 3: Thread 0 → Thread 1 → Thread 2
```

---

## Comparison: Producer-Consumer vs Token Ring

| | Producer-Consumer | Token Ring |
|---|---|---|
| **Purpose** | Decouple work generation from processing | Enforce strict execution order |
| **Who runs next** | Any available consumer | Specific thread by ID |
| **notify** | `notify_one` (any consumer works) | `notify_all` (only one is correct) |
| **Token** | `bool done` flag | `int token` with modulo |
| **Fairness** | Not guaranteed | Strictly guaranteed |
| **Use case** | Task queues, pipelines | Protocols, ordered processing |

---


## Key Takeaways

- **Token passing** enforces strict round-robin order between threads
- **Modulo arithmetic** maps a linear counter to a circular sequence
- **notify_all** is required when only a specific thread should proceed
- **notify_one** is sufficient when any waiter can handle the event
- **Deadlock** happens when threads wait for each other indefinitely
- **Starvation** happens when a thread never gets CPU time — token passing prevents it
- **Spurious wakeups** are real — always use a predicate with `cv.wait`

---

## Further Reading

- *C++ Concurrency in Action* — Anthony Williams (Chapter 4: Synchronizing concurrent operations)
- *The Art of Multiprocessor Programming* — Herlihy & Shavit
- [cppreference — std::condition_variable](https://en.cppreference.com/w/cpp/thread/condition_variable)
- [Wikipedia — Token Ring](https://en.wikipedia.org/wiki/Token_ring)