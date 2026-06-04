# include "./include/hash-table.hpp"


// These helpers are file-local — no other translation unit should see them.
namespace {
    // Checks whether n is a prime number. Used to pick good table sizes,
    // since prime sizes reduce hash clustering.
    bool isPrime(int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0) return false;
        return true;
    }

    // Returns the first prime >= n. Used after doubling the table size
    // to land on a prime rather than an even number.
    int nextPrime(int n) {
        while (!isPrime(n)) n++;
        return n;
    }
}


HashTable::HashTable(int size) : size(size), count(0) {
    table.resize(size);
}

// Delegates to hashWithSize so rehash() can compute indices for the
// new table before swapping it in — without temporarily changing this->size.
size_t HashTable::hash(const std::string& key) {
    return hashWithSize(key, size);
}

// DJB2 hash by Dan Bernstein. The magic number 5381 and multiplier 33
// (expressed as (h << 5) + h) were chosen empirically for good distribution
// across ASCII strings. Cast to unsigned char so high-bit chars don't
// sign-extend and corrupt the running hash.
size_t HashTable::hashWithSize(const std::string& key, int s) {
    size_t h = 5381;
    for (char c : key)
        h = ((h << 5) + h) + static_cast<unsigned char>(c);
    return h % s;
}

// If the key already exists, update its value in-place instead of
// inserting a duplicate. The load-factor check after insertion keeps
// average chain length near O(1) by triggering a rehash before the
// table gets crowded.
void HashTable::push(const std::string& key, int value) {
    size_t index = hash(key);

    for (auto& entry : table[index]) {
        if (entry.key == key) {
            entry.value = value;
            return;
        }
    }

    table[index].push_back({key, value});
    count++;

    // 0.7 load factor is a common sweet spot: low enough to keep chains
    // short, high enough to not waste memory.
    if ((double)count / size > 0.7)
        rehash();
}

// Doubles the table size then rounds up to the next prime so the modulo
// in hashWithSize distributes evenly. Every existing entry must be
// rehashed because the bucket index depends on the table size.
void HashTable::rehash() {
    int newSize = nextPrime(size * 2);
    std::vector<std::list<Entry>> newTable(newSize);

    for (auto& bucket : table) {
        for (auto& entry : bucket) {
            size_t newIndex = hashWithSize(entry.key, newSize);
            newTable[newIndex].push_back(entry);
        }
    }

    // std::move avoids copying all the lists; table becomes the new storage
    // and the old memory is freed when newTable goes out of scope.
    table = std::move(newTable);
    size = newSize;
}

// Returns -1 as the sentinel for "not found". Matches the common convention
// for integer-valued maps where -1 is not a valid stored value.
int HashTable::get(const std::string& key) {
    size_t index = hash(key);

    for (const auto& entry : table[index]) {
        if (entry.key == key) {
            return entry.value;
        }
    }

    return -1;
}

bool HashTable::contains(const std::string& key) {
    size_t index = hash(key);

    for (const auto& entry : table[index]) {
        if (entry.key == key) {
            return true;
        }
    }

    return false;
}

// Uses an iterator instead of a range-for because std::list::erase
// requires an iterator — range-for gives a reference, not an iterator.
bool HashTable::remove(const std::string& key) {
    size_t index = hash(key);

    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == key) {
            table[index].erase(it);
            count--;
            return true;
        }
    }

    return false;
}

int HashTable::get_count() {
    return count;
}
