# Hash Table — Chaining with DJB2

A hash table maps **string keys to integer values** in O(1) average time.
It handles collisions via **separate chaining** (each bucket is a linked list)
and grows automatically when the load factor exceeds 0.7.

---

## How It Works

```
key → hash function → bucket index → linked list → entry
```

```
table (vector of lists):

index 0: [ ]
index 1: [ ("apple", 5) ]
index 2: [ ("banana", 3) → ("mango", 7) ]   ← collision: both hash to 2
index 3: [ ]
index 4: [ ("cherry", 1) ]
...
```

Each `table[i]` is a `std::list<Entry>`. Most buckets hold zero or one entry;
collisions produce chains of two or more.

---

## The DJB2 Hash Function

Created by Dan Bernstein. Simple, fast, and surprisingly good distribution over ASCII strings.

```cpp
size_t h = 5381;
for (char c : key)
    h = h * 33 + c;
return h % table_size;
```

The `* 33` is written as `(h << 5) + h` — a single shift + add, which is faster
than a multiply on most hardware.

**Why 5381?** It was found empirically to produce good avalanche behavior: a small
change in the key cascades into a very different hash value.

```
"hello" → 210700827 % 53 → bucket 24
"Hello" → 210700795 % 53 → bucket 47   ← one bit different, different bucket
```

---

## Collision Resolution — Separate Chaining

When two keys hash to the same bucket, they are stored as separate nodes in
the same linked list:

```
push("banana", 3)   → bucket 2: [ ("banana", 3) ]
push("mango",  7)   → bucket 2: [ ("banana", 3) → ("mango", 7) ]

get("mango")        → scan bucket 2, skip "banana", return 7
```

**Average case:** O(1) when the load factor is low (chains stay short).  
**Worst case:** O(n) if all keys collide (degenerate chain).

---

## Load Factor & Rehashing

The **load factor** is `count / size`. When it exceeds **0.7**, the table rehashes:

```
load = count / size > 0.7  →  rehash()
```

**Rehash steps:**
1. Compute `newSize = nextPrime(size * 2)`
2. Allocate a new `vector<list<Entry>>` of that size
3. Re-insert every existing entry (bucket indices change because `% size` changed)
4. Swap the new table in with `std::move`

**Why a prime size?**  
Modulo a prime distributes keys more evenly than modulo an even number.
For example, if many keys have even hash values, `% 100` always maps them to
even indices — half the buckets are wasted. `% 101` has no such bias.

---

## API

```cpp
HashTable ht;            // default size 53 (a prime)
HashTable ht(101);       // custom initial size

ht.push("score", 42);   // insert; if key exists, update value
ht.get("score");        // → 42; returns -1 if not found
ht.contains("score");   // → true
ht.remove("score");     // → true if found and removed
ht.get_count();         // → number of stored key-value pairs
```

---

## Complexity

| Operation | Average | Worst |
|---|---|---|
| `push` | O(1) | O(n) |
| `get` | O(1) | O(n) |
| `contains` | O(1) | O(n) |
| `remove` | O(1) | O(n) |
| `rehash` | O(n) | O(n) |

Worst case only occurs when all keys hash to the same bucket (extreme input or
a badly chosen hash function). With DJB2 and a prime table size this is rare in practice.

---

## Memory Layout

```
HashTable object (stack):
┌───────────────────────────────┐
│ table: vector<list<Entry>>    │  ← metadata on stack
│ size:  53                     │
│ count: 3                      │
└──────────────────┬────────────┘
                   │
                   ▼  (heap)
┌────┬────┬────┬────┬────┬─────┐
│ [] │ [] │ L2 │ [] │ L4 │ ... │   vector of 53 list heads
└────┴────┴──┬─┴────┴──┬─┴─────┘
             │          │
             ▼          ▼
      ("banana",3)   ("cherry",1)
            │
            ▼
       ("mango",7)
```

---

## Key Takeaways

- Hash tables trade space for time: O(1) average by keeping chains short.
- The hash function must distribute keys uniformly — DJB2 is a solid default for strings.
- Load factor is the knob that balances memory usage vs. chain length.
- Rehashing is O(n) but amortized O(1) per insertion (same logic as `vector::push_back`).
- Prime table sizes reduce clustering when hash values share common factors.

---

## Further Reading

- [DJB2 original post by Dan Bernstein](http://www.cse.yorku.ca/~oz/hash.html)
- *Introduction to Algorithms* (CLRS) — Chapter 11: Hash Tables
- [cppreference — std::unordered_map](https://en.cppreference.com/w/cpp/container/unordered_map) (STL's hash table)
- [cppreference — std::list](https://en.cppreference.com/w/cpp/container/list)
