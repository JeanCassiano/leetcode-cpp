#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <chrono>

// ============================================================================
// 1. STACK: Fast, Automatic, Scope-Limited
// ============================================================================

void demo_stack_basics() {
    std::cout << "\n=== 1. STACK BASICS ===\n";
    std::cout << "Declaring local variables — they go on the STACK:\n\n";

    int x = 42;              // 4 bytes on stack
    double y = 3.14;         // 8 bytes on stack
    char c = 'A';            // 1 byte on stack
    bool flag = true;        // 1 byte on stack

    std::cout << "  int x = 42;       → allocated 4 bytes on stack\n";
    std::cout << "  double y = 3.14;  → allocated 8 bytes on stack\n";
    std::cout << "  char c = 'A';     → allocated 1 byte on stack\n";
    std::cout << "  bool flag = true; → allocated 1 byte on stack\n";
    std::cout << "  Total: 14 bytes allocated instantly (just move pointer)\n";

    std::cout << "\nAddresses (stack grows upward):\n";
    std::cout << "  &x    = " << (void*)&x << "\n";
    std::cout << "  &y    = " << (void*)&y << "\n";
    std::cout << "  &c    = " << (void*)&c << "\n";
    std::cout << "  &flag = " << (void*)&flag << "\n";

    std::cout << "\nWhen this function exits, all 14 bytes are freed instantly.\n";
}

// ============================================================================
// 2. HEAP: Flexible, Manual (or Smart Ptr), Lifetime-Independent
// ============================================================================

void demo_heap_basics() {
    std::cout << "\n=== 2. HEAP BASICS ===\n";
    std::cout << "Using 'new' to allocate on HEAP:\n\n";

    int* p1 = new int(42);           // allocate int on heap, get pointer
    double* p2 = new double(3.14);   // allocate double on heap

    std::cout << "  int* p1 = new int(42);      → pointer on stack, int on heap\n";
    std::cout << "  double* p2 = new double(3.14);\n\n";

    std::cout << "Pointer values (stack addresses):\n";
    std::cout << "  p1 = " << (void*)p1 << " (address of int on heap)\n";
    std::cout << "  p2 = " << (void*)p2 << " (address of double on heap)\n";
    std::cout << "  &p1 = " << (void*)&p1 << " (address of p1 itself on stack)\n\n";

    std::cout << "Dereferencing:\n";
    std::cout << "  *p1 = " << *p1 << "\n";
    std::cout << "  *p2 = " << *p2 << "\n\n";

    std::cout << "Manual cleanup required:\n";
    delete p1;
    delete p2;
    std::cout << "  delete p1; → heap memory freed\n";
    std::cout << "  delete p2; → heap memory freed\n";
    std::cout << "  ⚠️  If we forgot delete, memory would leak!\n";
}

// ============================================================================
// 3. STRINGS & VECTORS: Metadata on Stack, Data on Heap
// ============================================================================

void demo_container_memory() {
    std::cout << "\n=== 3. CONTAINERS: Hybrid Stack-Heap ===\n";

    std::string s = "Hello, World!";
    std::vector<int> v = {1, 2, 3, 4, 5};

    std::cout << "  std::string s = \"Hello, World!\";\n";
    std::cout << "  std::vector<int> v = {1, 2, 3, 4, 5};\n\n";

    std::cout << "String metadata (on STACK):\n";
    std::cout << "  address of s       = " << (void*)&s << "\n";
    std::cout << "  s.size()           = " << s.size() << "\n";
    std::cout << "  s.capacity()       = " << s.capacity() << "\n";
    std::cout << "  data pointer       = " << (void*)s.data() << "\n\n";

    std::cout << "String data (on HEAP at " << (void*)s.data() << "):\n";
    std::cout << "  \"" << s << "\"\n\n";

    std::cout << "Vector metadata (on STACK):\n";
    std::cout << "  address of v       = " << (void*)&v << "\n";
    std::cout << "  v.size()           = " << v.size() << "\n";
    std::cout << "  v.capacity()       = " << v.capacity() << "\n";
    std::cout << "  data pointer       = " << (void*)v.data() << "\n\n";

    std::cout << "Vector data (on HEAP at " << (void*)v.data() << "):\n";
    std::cout << "  [";
    for (int x : v) std::cout << x << " ";
    std::cout << "]\n\n";

    std::cout << "When s and v go out of scope:\n";
    std::cout << "  ✅ Destructors run automatically\n";
    std::cout << "  ✅ Heap memory is freed\n";
    std::cout << "  ✅ No memory leak\n";
}

// ============================================================================
// 4. MEMORY LAYOUT: Function Call Stack
// ============================================================================

void inner(int n) {
    int local = n * 2;
    std::cout << "  inner(): local = " << local << " (stack)\n";
    std::cout << "           &local = " << (void*)&local << "\n";
}

void outer(int x) {
    int y = x + 1;
    std::cout << "  outer(): y = " << y << " (stack)\n";
    std::cout << "           &y = " << (void*)&y << "\n";
    inner(y);
}

void demo_call_stack() {
    std::cout << "\n=== 4. CALL STACK: Function Frames ===\n";
    std::cout << "Observing stack growth during function calls:\n\n";

    int main_var = 100;
    std::cout << "main():  main_var = " << main_var << " (stack)\n";
    std::cout << "         &main_var = " << (void*)&main_var << "\n";

    outer(main_var);

    std::cout << "\nWhen inner() returns, its stack frame is popped.\n";
    std::cout << "When outer() returns, its stack frame is popped.\n";
    std::cout << "main_var is still on the stack.\n";
}

// ============================================================================
// 5. POINTERS: Dereferencing and Null Checks
// ============================================================================

void demo_pointers() {
    std::cout << "\n=== 5. POINTERS: Navigate Stack and Heap ===\n";

    // Stack variable
    int stack_var = 42;
    int* ptr_to_stack = &stack_var;

    std::cout << "Stack variable:\n";
    std::cout << "  int stack_var = 42;\n";
    std::cout << "  int* ptr_to_stack = &stack_var;\n";
    std::cout << "  *ptr_to_stack = " << *ptr_to_stack << "\n";
    std::cout << "  ptr_to_stack = " << (void*)ptr_to_stack << "\n\n";

    // Heap variable
    int* ptr_to_heap = new int(99);

    std::cout << "Heap variable:\n";
    std::cout << "  int* ptr_to_heap = new int(99);\n";
    std::cout << "  *ptr_to_heap = " << *ptr_to_heap << "\n";
    std::cout << "  ptr_to_heap = " << (void*)ptr_to_heap << "\n\n";

    // Pointer arithmetic
    std::cout << "Pointer arithmetic:\n";
    int arr[] = {10, 20, 30, 40, 50};
    int* p = arr;
    std::cout << "  int arr[] = {10, 20, 30, 40, 50};\n";
    std::cout << "  int* p = arr;  // p points to arr[0]\n";
    std::cout << "  *(p+0) = " << *(p+0) << "\n";
    std::cout << "  *(p+1) = " << *(p+1) << "\n";
    std::cout << "  *(p+2) = " << *(p+2) << "\n";
    std::cout << "  p[0] = " << p[0] << ",  p[1] = " << p[1] << ",  p[2] = " << p[2] << "\n\n";

    delete ptr_to_heap;
    std::cout << "delete ptr_to_heap;  // cleanup\n";
}

// ============================================================================
// 6. REFERENCES: Aliases (Safer than Pointers)
// ============================================================================

void demo_references() {
    std::cout << "\n=== 6. REFERENCES: Aliases Without Pointers ===\n";

    int x = 42;
    int& ref = x;

    std::cout << "  int x = 42;\n";
    std::cout << "  int& ref = x;  // ref is an alias for x\n\n";

    std::cout << "  ref = " << ref << "\n";
    std::cout << "  x = " << x << "\n";
    std::cout << "  &ref = " << (void*)&ref << "\n";
    std::cout << "  &x = " << (void*)&x << "\n\n";

    std::cout << "Modifying through reference:\n";
    ref = 100;
    std::cout << "  ref = 100;\n";
    std::cout << "  x is now " << x << " (changed!)\n\n";

    std::cout << "References vs Pointers:\n";
    std::cout << "  ✅ References cannot be null\n";
    std::cout << "  ✅ References cannot be reassigned\n";
    std::cout << "  ✅ No dereferencing syntax needed\n";
    std::cout << "  ❌ Slightly less flexible than pointers\n";
}

// ============================================================================
// 7. MEMORY LEAKS: Forgetting to Delete
// ============================================================================

void demo_memory_leak() {
    std::cout << "\n=== 7. MEMORY LEAKS: Allocate but Never Delete ===\n";

    std::cout << "BAD CODE:\n";
    std::cout << "  void bad_function() {\n";
    std::cout << "      int* p = new int(42);\n";
    std::cout << "      std::cout << *p;\n";
    std::cout << "      // ❌ forgot delete — memory leaked!\n";
    std::cout << "  }\n\n";

    std::cout << "Consequences:\n";
    std::cout << "  • If called 1,000 times: 4,000 bytes leaked\n";
    std::cout << "  • If called 1,000,000 times: 4MB leaked\n";
    std::cout << "  • Heap fills up, program crashes\n\n";

    std::cout << "GOOD CODE:\n";
    std::cout << "  void good_function() {\n";
    std::cout << "      auto p = std::make_unique<int>(42);\n";
    std::cout << "      std::cout << *p;\n";
    std::cout << "      // ✅ destructor runs, memory freed\n";
    std::cout << "  }\n";
}

// ============================================================================
// 8. DANGLING POINTER: Use After Delete
// ============================================================================

void demo_dangling_pointer() {
    std::cout << "\n=== 8. DANGLING POINTER: Use After Delete ===\n";

    std::cout << "BAD CODE (returning address of stack variable):\n";
    std::cout << "  int* bad_function() {\n";
    std::cout << "      int x = 42;\n";
    std::cout << "      return &x;  // ❌ x dies when function exits!\n";
    std::cout << "  }\n\n";

    std::cout << "Consequences:\n";
    std::cout << "  int* p = bad_function();\n";
    std::cout << "  std::cout << *p;  // ❌ undefined behavior!\n";
    std::cout << "  p points to freed stack memory.\n\n";

    std::cout << "GOOD CODE:\n";
    std::cout << "  std::unique_ptr<int> good_function() {\n";
    std::cout << "      return std::make_unique<int>(42);\n";
    std::cout << "  }\n\n";

    std::cout << "Now it's safe:\n";
    std::cout << "  auto p = good_function();\n";
    std::cout << "  std::cout << *p;  // ✅ safe!\n";
}

// ============================================================================
// 9. SMART POINTERS: Automatic Cleanup
// ============================================================================

void demo_smart_pointers() {
    std::cout << "\n=== 9. SMART POINTERS: RAII in Action ===\n";

    std::cout << "unique_ptr: Exclusive Ownership\n";
    {
        auto p = std::make_unique<int>(42);
        std::cout << "  auto p = std::make_unique<int>(42);\n";
        std::cout << "  *p = " << *p << "\n";
        std::cout << "  (scope ending...)\n";
    }
    std::cout << "  ✅ ~unique_ptr() called, memory freed\n\n";

    std::cout << "shared_ptr: Shared Ownership (Reference Counted)\n";
    {
        auto p1 = std::make_shared<int>(99);
        {
            auto p2 = p1;  // p2 shares ownership
            std::cout << "  auto p2 = p1;\n";
            std::cout << "  reference count: " << p1.use_count() << "\n";
        }
        std::cout << "  p2 destroyed, reference count: " << p1.use_count() << "\n";
        std::cout << "  (p1 scope ending...)\n";
    }
    std::cout << "  ✅ ~shared_ptr() called, memory freed\n\n";

    std::cout << "Comparison:\n";
    std::cout << "  unique_ptr  → one owner, fast, move semantics\n";
    std::cout << "  shared_ptr  → multiple owners, slight overhead (ref count)\n";
    std::cout << "  raw pointer → manual, error-prone, don't use for ownership\n";
}

// ============================================================================
// 10. STACK OVERFLOW: Allocating Too Much
// ============================================================================

void demo_stack_limit() {
    std::cout << "\n=== 10. STACK OVERFLOW: Limits ===\n";

    std::cout << "Stack is typically ~8MB on modern systems.\n\n";

    std::cout << "DON'T do this:\n";
    std::cout << "  int huge_array[10000000];  // 40MB on stack!\n";
    std::cout << "  // ❌ stack overflow — program crashes\n\n";

    std::cout << "DO this instead:\n";
    std::cout << "  auto huge_array = std::make_unique<int[]>(10000000);\n";
    std::cout << "  // ✅ 40MB on heap — safe\n\n";

    std::cout << "Test: allocate 1MB on stack safely\n";
    int arr[262144];  // 1MB
    arr[0] = 1;
    std::cout << "  int arr[262144];  // 1MB on stack\n";
    std::cout << "  arr[0] = " << arr[0] << " (still alive)\n";
}

// ============================================================================
// 11. PRACTICAL: When to Use Stack vs Heap
// ============================================================================

struct Point {
    double x, y;
};

void demo_practical_guidelines() {
    std::cout << "\n=== 11. PRACTICAL: Stack vs Heap ===\n";

    std::cout << "USE STACK FOR:\n";
    std::cout << "  • Small, fixed-size data\n";
    std::cout << "  • Primitives (int, double, char, bool)\n";
    std::cout << "  • Small structs (Point, Color, Vec3)\n";
    std::cout << "  • Local variables with known lifetime\n\n";

    Point p1 = {1.0, 2.0};  // Stack
    std::cout << "  Point p1 = {1.0, 2.0};  // ✅ on stack\n";
    std::cout << "  p1.x = " << p1.x << ", p1.y = " << p1.y << "\n\n";

    std::cout << "USE HEAP FOR:\n";
    std::cout << "  • Large data (vectors, strings, maps)\n";
    std::cout << "  • Data with unknown size at compile-time\n";
    std::cout << "  • Data that must outlive a function\n";
    std::cout << "  • Polymorphic objects (base class pointers)\n\n";

    auto large_vector = std::make_unique<std::vector<int>>();
    for (int i = 0; i < 100; ++i) {
        large_vector->push_back(i);
    }
    std::cout << "  auto v = std::make_unique<std::vector<int>>();\n";
    std::cout << "  (filled with 100 integers on heap)\n";
    std::cout << "  v->size() = " << large_vector->size() << "\n";
}

// ============================================================================
// 12. PERFORMANCE: Stack vs Heap
// ============================================================================

void demo_performance() {
    std::cout << "\n=== 12. PERFORMANCE: Allocation Speed ===\n";

    const int iterations = 1'000'000;

    // Stack allocation (implicit, just declare)
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        int x = 42;
        int y = 99;
        int z = x + y;
        (void)z;
    }
    auto stack_time = std::chrono::high_resolution_clock::now() - start;

    // Heap allocation (explicit new/delete)
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        int* p = new int(42);
        delete p;
    }
    auto heap_raw_time = std::chrono::high_resolution_clock::now() - start;

    // Smart pointer allocation
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        auto p = std::make_unique<int>(42);
    }
    auto heap_smart_time = std::chrono::high_resolution_clock::now() - start;

    std::cout << "Allocating and deallocating " << iterations << " times:\n\n";
    std::cout << "Stack (declare local):           "
              << std::chrono::duration_cast<std::chrono::milliseconds>(stack_time).count()
              << " ms\n";
    std::cout << "Heap (new/delete):               "
              << std::chrono::duration_cast<std::chrono::milliseconds>(heap_raw_time).count()
              << " ms\n";
    std::cout << "Heap (unique_ptr):               "
              << std::chrono::duration_cast<std::chrono::milliseconds>(heap_smart_time).count()
              << " ms\n\n";

    std::cout << "Stack is ~"
              << heap_raw_time.count() / static_cast<double>(stack_time.count())
              << "x faster (no allocator overhead)\n";
}

// ============================================================================
// 13. ARRAY DECAY: Arrays → Pointers
// ============================================================================

void process_array(int* arr, int size) {
    std::cout << "  Inside function: arr = " << (void*)arr << "\n";
    std::cout << "  Inside function: size = " << size << "\n";
    std::cout << "  arr[0] = " << arr[0] << "\n";
}

void demo_array_decay() {
    std::cout << "\n=== 13. ARRAY DECAY: Arrays Become Pointers ===\n";

    int arr[5] = {1, 2, 3, 4, 5};

    std::cout << "Arrays decay to pointers when passed to functions:\n\n";
    std::cout << "  int arr[5] = {1, 2, 3, 4, 5};\n";
    std::cout << "  arr = " << (void*)arr << "\n";
    std::cout << "  sizeof(arr) = " << sizeof(arr) << " bytes (full array)\n\n";

    std::cout << "  process_array(arr, 5);\n";
    process_array(arr, 5);
    std::cout << "\n  ⚠️  Inside function, arr is a pointer!\n";
    std::cout << "  ⚠️  Size information is lost!\n";
    std::cout << "  ⚠️  Must pass size separately or use std::vector\n";
}

// ============================================================================
// 14. CONST REFERENCE: The Sweet Spot
// ============================================================================

void expensive_operation(const std::vector<int>& v) {
    std::cout << "  Function received vector with " << v.size() << " elements\n";
    std::cout << "  No copy was made (passed by const reference)\n";
}

void demo_const_reference() {
    std::cout << "\n=== 14. CONST REFERENCE: Avoid Copies ===\n";

    std::vector<int> large_vector;
    for (int i = 0; i < 1'000'000; ++i) {
        large_vector.push_back(i);
    }

    std::cout << "Created vector with 1,000,000 elements\n\n";

    std::cout << "Passing by const reference:\n";
    std::cout << "  void process(const std::vector<int>& v) { }\n";
    expensive_operation(large_vector);
    std::cout << "  ✅ Fast (no allocation, no copying)\n\n";

    std::cout << "Passing by value would:\n";
    std::cout << "  • Allocate new memory on heap: ~4MB\n";
    std::cout << "  • Copy 1M integers\n";
    std::cout << "  • Be much slower\n";
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "STACK & HEAP: Complete Demonstration\n";
    std::cout << std::string(70, '=') << "\n";

    demo_stack_basics();
    demo_heap_basics();
    demo_container_memory();
    demo_call_stack();
    demo_pointers();
    demo_references();
    demo_memory_leak();
    demo_dangling_pointer();
    demo_smart_pointers();
    demo_stack_limit();
    demo_practical_guidelines();
    demo_performance();
    demo_array_decay();
    demo_const_reference();

    std::cout << "\n" << std::string(70, '=') << "\n";
    std::cout << "All demonstrations completed successfully!\n";
    std::cout << std::string(70, '=') << "\n\n";

    return 0;
}
