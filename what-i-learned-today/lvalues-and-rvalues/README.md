# lvalues & rvalues — Move Semantics in Practice

## Core Concept

Every expression in C++ is either an **lvalue** or an **rvalue**.

| | lvalue | rvalue |
|---|---|---|
| Has a name | ✅ | ❌ |
| Has an address | ✅ | ❌ |
| Persists after expression | ✅ | ❌ |
| Example | `int x = 27` → `x` | `int x = 27` → `27` |

**Quick test:** can you take its address with `&`?
```cpp
int x = 27;
int* p1 = &x;   // ✅ x is an lvalue
int* p2 = &27;  // ❌ 27 is an rvalue — no address
```

---

## Why It Matters — The Cost of Copying

A `std::vector` internally holds a pointer to a heap-allocated block:

```
std::vector<int> v = {1, 2, 3, ..., 10M};

Memory:
v → [ ptr | size | capacity ]
       ↓
  [ 1, 2, 3, ..., 10M ]  ← heap block
```

**Copy:** allocates a new block, copies every element. Expensive.

**Move:** transfers ownership of the pointer. The original becomes empty. Cheap.

```cpp
// COPY — allocates + copies 10M ints
void process_copy(std::vector<int> v) { }
process_copy(v);  // expensive

// MOVE — transfers the internal pointer, v becomes empty
void process_move(std::vector<int>&& v) { }
process_move(std::move(v));  // cheap
```

---

## References

| Syntax | Name | Accepts |
|---|---|---|
| `T&` | lvalue reference | lvalues only |
| `T&&` | rvalue reference | rvalues only |
| `T&&` (in template) | universal reference | both |

```cpp
void f(std::vector<int>& v)   // lvalue ref  — accepts lvalues
void g(std::vector<int>&& v)  // rvalue ref  — accepts rvalues only
template<typename T>
void h(T&& v)                 // universal   — accepts both
```

---

## std::move and std::forward

```cpp
std::move(x)       // casts lvalue → rvalue
                   // "I don't need x anymore, you can steal it"

std::forward<T>(x) // preserves the original value category
                   // if T was lvalue ref → forwards as lvalue
                   // if T was rvalue ref → forwards as rvalue
```

**Perfect forwarding pattern:**
```cpp
template<typename T>
void wrapper(T&& v) {
    target(std::forward<T>(v)); // forwards exactly as received
}
```

---

## Benchmark Results

Vector with 10 million integers:

| Operation | Time |
|---|---|
| Copy | 56620µs |
| Move | 26209µs |

Move is faster because it only transfers a pointer — no heap allocation, no element copying.

After `std::move(v)`, `v.size() == 0`. The data was stolen.

---

## Key Takeaways

- `lvalue` → has a name, has an address, persists
- `rvalue` → temporary, dies at end of expression
- `std::move` → converts lvalue to rvalue ("you can steal this")
- `std::forward` → preserves value category (used in templates)
- `&&` in a regular function → rvalue reference, only accepts rvalues
- `T&&` in a template → universal reference, accepts everything
- Move semantics exist to **avoid unnecessary copies** of expensive resources

---

## Related Reading

- *Effective Modern C++* — Items 1, 2, 5, 6 (Scott Meyers)
- [cppreference — value categories](https://en.cppreference.com/w/cpp/language/value_category)
- [cppreference — std::move](https://en.cppreference.com/w/cpp/utility/move)
- [cppreference — std::forward](https://en.cppreference.com/w/cpp/utility/forward)