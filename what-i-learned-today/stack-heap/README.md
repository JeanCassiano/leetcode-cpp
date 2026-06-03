# Stack & Heap — Memory Management in C++

Every variable in C++ lives in one of two places: the **stack** or the **heap**.
Understanding where your data lives is crucial for writing fast, safe code.

---

## Quick Comparison

| Property | Stack | Heap |
|---|---|---|
| **What goes here** | Primitives, function params, local objects | Dynamic allocations, large objects |
| **Allocation** | Automatic (compile-time known size) | Manual (dynamic `new` / smart ptrs) |
| **Deallocation** | Automatic (when scope ends) | Manual (must `delete`) |
| **Speed** | Super fast (pointer increment) | Slower (involves allocator) |
| **Size limit** | ~8MB typical | Limited by RAM |
| **Lifetime** | Scope duration | Until `delete` / ptr destroyed |
| **Thread-local** | Yes (each thread has its own) | Shared (all threads see same heap) |

---

## The Memory Layout

When your program starts, memory is divided:

```
┌─────────────────────────────────────┐
│      Code (read-only)               │  ← your program instructions
├─────────────────────────────────────┤
│      Static / Global Data           │  ← global variables, constants
├─────────────────────────────────────┤
│                                     │
│         HEAP  ↓  ↓  ↓              │  ← grows downward (on x86)
│     [ allocated objects ]           │
│                                     │
├─────────────────────────────────────┤
│                                     │
│     ↑  ↑  ↑  STACK                 │  ← grows upward (on x86)
│  [ local vars, call frames ]        │
└─────────────────────────────────────┘
     Low Addresses      High Addresses
```

The stack and heap grow **toward each other**. If they collide, you've run out of memory.

---

## Stack: The Fast Path

The stack is a **LIFO** (Last In, First Out) structure. When you declare a variable:

```cpp
void example() {
    int x = 42;        // push: stack += 4 bytes
    double y = 3.14;   // push: stack += 8 bytes
    char z = 'A';      // push: stack += 1 byte
}                      // pop: stack -= 13 bytes (automatic)
```

**Stack state during execution:**

```
Function call: example()
┌──────────┐
│ z (1 B)  │ ← top of stack (address: highest)
├──────────┤
│ y (8 B)  │
├──────────┤
│ x (4 B)  │ ← allocated first
├──────────┤  
│ return   │ ← where to return to
│ address  │
└──────────┘
```

**Why fast?**
- Allocation is just moving a pointer (`stack_pointer += 13`).
- Deallocation is just moving the pointer back.
- **No allocator overhead.** No fragmentation.

**When does it happen?**
- **Allocation:** function enter, variable declaration
- **Deallocation:** function exit, scope ends

---

## Heap: The Flexible Path

The heap is unstructured. You manually ask for memory:

```cpp
void example() {
    int* p = new int(42);           // allocate on heap, get pointer
    std::vector<int> v = {1,2,3};   // heap allocation inside vector
    
    delete p;                        // manual deallocation
}   // v's destructor runs, heap memory freed
```

**Heap state:**

```
Heap memory (addresses are arbitrary):

┌──────────────────────┐
│ ? ? ? ? ? ? ? ? ? ?  │ ← unused (fragmented)
├──────────────────────┤
│ allocated (p points) │ ← int(42)
├──────────────────────┤
│ ? ? ? ? ? ? ? ? ? ?  │ ← unused
├──────────────────────┤
│ allocated (in v)     │ ← [1, 2, 3]
├──────────────────────┤
│ ? ? ? ? ? ? ? ? ? ?  │ ← unused
└──────────────────────┘
```

**Why slower?**
- Allocator must find a free block → fragmentation issues
- Allocator overhead (metadata, tracking)
- **Pointer indirection** — to access data, dereference the pointer

**When does it happen?**
- **Allocation:** `new`, `std::vector::push_back()`, `std::make_unique()`
- **Deallocation:** `delete`, destructor, `unique_ptr` goes out of scope

---

## Where Does Each Variable Live?

### Primitives and Automatic Objects

```cpp
int x = 42;              // STACK (4 bytes)
double y = 3.14;        // STACK (8 bytes)
char c = 'A';           // STACK (1 byte)
bool flag = true;       // STACK (1 byte)

std::string s = "hi";   // stack contains std::string object (small overhead)
                        // but HEAP contains the character buffer "hi"
```

**Visualization:**

```
Stack:                          Heap:
┌──────────┐                   ┌───────────────┐
│ x: 42    │                   │ (unused)      │
├──────────┤                   └───────────────┘
│ y: 3.14  │
├──────────┤
│ c: 'A'   │
├──────────┤
│ flag: 1  │
├──────────┤
│ s: {ptr──┼──────────────────→ "hi\0"
│    size:2│                   
│    cap:2}│
└──────────┘
```

The string **object** lives on the stack, but the **data** lives on the heap.

### Dynamic Allocation

```cpp
int* p = new int(42);           // p (pointer) on STACK
                                // int(42) on HEAP

std::vector<int> v = {1,2,3};   // v (vector object) on STACK
                                // [1,2,3] (data) on HEAP
```

**Visualization:**

```
Stack:                          Heap:
┌──────────┐                   ┌──────┐
│ p: 0x... │────────────────→  │ 42   │
├──────────┤                   └──────┘
│ v: {ptr──┼──────┐            ┌──────┐
│    size:3│      └──────────→ │ 1    │
│    cap:3}│                   │ 2    │
└──────────┘                   │ 3    │
                               └──────┘
```

---

## Pointers & References

### Pointer: A Variable That Holds an Address

```cpp
int x = 42;
int* p = &x;          // p stores the address of x

std::cout << p;       // prints address (e.g., 0x7fff5fbff8ac)
std::cout << *p;      // dereference: prints 42

*p = 100;             // modify x through the pointer
std::cout << x;       // prints 100
```

**When to use:**
- You need dynamic allocation (`new`)
- You need to pass ownership around
- Array indexing (arrays are pointers)

### Reference: An Alias (Cannot Be Null, Cannot Reassign)

```cpp
int x = 42;
int& ref = x;         // ref is an alias for x

std::cout << ref;     // prints 42
ref = 100;            // modifies x

// int& ref2 = y;     // ❌ Cannot reassign reference
```

**When to use:**
- Function parameters (avoid copying)
- Return values (avoid dangling pointers)
- Can't use for arrays or containers

```cpp
// ✅ Good: avoid copying large vector
void process(const std::vector<int>& v) { }

// ❌ Bad: copies entire vector
void process(std::vector<int> v) { }
```

---

## Memory Leaks & Dangling Pointers

### Leak: You Allocated but Never Deallocated

```cpp
void bad() {
    int* p = new int(42);
    std::cout << *p;
    // ❌ forgot delete — memory leaked!
}
```

**Consequence:** The 4 bytes on the heap are now unreachable. As you repeat this,
heap fills up → program crashes with "out of memory."

**How to prevent:**
```cpp
void good() {
    std::unique_ptr<int> p = std::make_unique<int>(42);
    std::cout << *p;
    // ✅ destructor runs, memory freed automatically
}
```

### Dangling Pointer: You Deallocated but Still Use the Pointer

```cpp
int* create_number() {
    int x = 42;
    return &x;  // ❌ dangerous! x dies when function exits
}

int main() {
    int* p = create_number();
    std::cout << *p;  // ❌ undefined behavior — p points to freed stack!
}
```

**How to prevent:**
```cpp
std::unique_ptr<int> create_number() {
    return std::make_unique<int>(42);  // ✅ allocates on heap, lifetime extends
}

int main() {
    auto p = create_number();
    std::cout << *p;  // ✅ safe, p owns the memory
}
```

---

## Stack Overflow & Heap Exhaustion

### Stack Overflow: Too Much Stack Usage

```cpp
void bad_recursion(int n) {
    int large_array[1000000];  // 4MB on stack! 
    if (n > 0) bad_recursion(n - 1);  // infinite recursion
}

int main() {
    bad_recursion(10);  // ❌ stack overflow — too much allocated
}
```

**Stack is typically only ~8MB.** Allocating huge arrays eats it fast.

**Fix:** Use heap for large data:
```cpp
void good_recursion(int n) {
    auto large_array = std::make_unique<int[]>(1000000);  // 4MB on heap
    if (n > 0) good_recursion(n - 1);
}
```

### Heap Exhaustion: Out of RAM

```cpp
while (true) {
    int* p = new int[1000000];  // 4MB per iteration
}  // ❌ eventually: out of heap memory, crash
```

**Fix:** Track allocations, limit growth, or fail gracefully:
```cpp
std::vector<int> v;
try {
    v.reserve(100'000'000);  // might throw std::bad_alloc
} catch (const std::bad_alloc&) {
    std::cerr << "not enough memory\n";
}
```

---

## Smart Pointers: Why Manual `delete` Is Dangerous

**Raw pointers require you to match `new` ↔ `delete`:**

```cpp
void process() {
    int* p = new int[100];
    if (error) return;  // ❌ leak: forgot delete[]
    delete[] p;
}
```

**Smart pointers do it automatically:**

```cpp
void process() {
    auto p = std::make_unique<int[]>(100);  // unique ownership
    if (error) return;  // ✅ destructor runs, memory freed
}
```

| Type | Ownership | Copy | Use Case |
|---|---|---|---|
| `unique_ptr` | Exclusive (you own it) | No, move only | When only one owner exists |
| `shared_ptr` | Shared (multiple owners) | Yes, reference-counted | When ownership is ambiguous |
| Raw `int*` | None (manual) | Yes (dangerous!) | Internal use only, not ownership |

**Example:**
```cpp
std::vector<std::unique_ptr<int>> ptrs;

ptrs.push_back(std::make_unique<int>(1));
ptrs.push_back(std::make_unique<int>(2));
// ✅ when ptrs goes out of scope, all integers are deleted automatically

ptrs.clear();  // ✅ deletes all elements immediately
```

---

## Practical: When to Use Stack vs Heap

### Use Stack For:
- Small, fixed-size data (primitives, small structs)
- Objects with known lifetime (local variables)
- Performance-critical code (allocation is free)

```cpp
struct Point {
    double x, y;  // small, predictable size
};

void process_point() {
    Point p = {1.0, 2.0};  // ✅ stack allocation is ideal
    std::cout << p.x;
}
```

### Use Heap For:
- Large data structures (vectors, strings, maps)
- Data with unknown lifetime (return from function)
- Polymorphic objects (base class pointers)
- Data shared between threads

```cpp
std::vector<int> read_file(const std::string& path) {
    auto result = std::make_unique<std::vector<int>>();
    // populate result...
    return result;  // ✅ lifetime extends beyond function
}

std::thread worker([data = std::make_shared<MyObject>()] {
    // ✅ multiple threads share ownership
    process(data);
});
```

---

## Benchmark: Stack vs Heap

Allocating 1 million integers:

```cpp
// Stack: compiler knows size, trivial
int arr[1000000];  // ❌ blows the stack, don't do this

// Heap with raw pointer
int* p = new int[1000000];
// ~200 nanoseconds (allocator overhead)

// Heap with vector
std::vector<int> v(1000000);
// ~200 nanoseconds (same, allocator overhead amortized)

// Heap with unique_ptr
auto p = std::make_unique<int[]>(1000000);
// ~200 nanoseconds (no overhead vs raw new)
```

**Key insight:** Once you're on the heap, the access speed is the same.
The difference is in **allocation overhead** (which happens once) and
**lifetime management** (which is automatic with smart pointers).

---

## The RAII Principle: Resource Acquisition Is Initialization

The core principle behind why C++ memory management works:

```cpp
class FileHandle {
private:
    FILE* file;
public:
    FileHandle(const char* path) {
        file = fopen(path, "r");  // acquire
        if (!file) throw std::runtime_error("open failed");
    }
    
    ~FileHandle() {
        if (file) fclose(file);  // release (automatic)
    }
};

void process() {
    FileHandle f("data.txt");  // acquire
    // use f...
}  // ✅ destructor runs automatically, file closed
```

**RAII means:** *Construction acquires the resource, destruction releases it.*
This is why `unique_ptr` and `vector` are safe — their destructors clean up.

---

## Key Takeaways

- **Stack** — fast, automatic, scope-limited. Use for small, local data.
- **Heap** — flexible, manual (or smart ptr), lifetime-independent. Use for large/dynamic data.
- **Primitives go to stack;** vectors/strings store metadata on stack, data on heap.
- **Pointers are stack variables** that hold heap addresses.
- **`new` allocates on heap, `delete` deallocates** — must match, error-prone.
- **Smart pointers** (`unique_ptr`, `shared_ptr`) automate deallocation via RAII.
- **Dangling pointer** — using memory after `delete` → undefined behavior.
- **Memory leak** — allocating but never deallocating → heap fills, crash.
- **Stack overflow** — allocating too much on stack → crash.
- **References are cheaper than copies** — pass by const-ref for large objects.

---

## Further Reading

- *The C++ Programming Language* — Bjarne Stroustrup (Chapter 11: Storage, Lifetimes, and Scope)
- *Effective C++* — Scott Meyers (Items 15-18: Memory Management)
- [cppreference — dynamic memory management](https://en.cppreference.com/w/cpp/memory)
- [cppreference — unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr)
- [cppreference — shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr)
- [CppCoreGuidelines — Memory Management](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#S-memory)
