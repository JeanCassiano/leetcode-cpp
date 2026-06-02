// Problem: LRU Cache
// Link: https://leetcode.com/problems/lru-cache/
// Difficulty: Medium
//
// Approach:
// We use a combination of a doubly-linked list and a hash map.
// - Hash map: stores key -> Node* mapping for O(1) access to nodes
// - Doubly-linked list: maintains LRU order with dummy nodes at both ends
//   * Most recently used is near the right (before 'right' dummy node)
//   * Least recently used is near the left (after 'left' dummy node)
//
// Operations:
// - get(key): Find in map, move to right (mark as recently used), return value
// - put(key, value): Insert/update, move to right, evict LRU (left) if over capacity
//
// Time Complexity: O(1)
//   - get and put both perform constant time operations
//
// Space Complexity: O(capacity)
//   - stores at most 'capacity' nodes

#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int cap;
    unordered_map<int, Node*> cache;
    Node* left;
    Node* right;

    void remove(Node* node) {
        Node* prev = node->prev;
        Node* nxt = node->next;
        prev->next = nxt;
        nxt->prev = prev;
    }

    void insert(Node* node) {
        Node* prev = right->prev;
        prev->next = node;
        node->prev = prev;
        node->next = right;
        right->prev = node;
    }

public:
    LRUCache(int capacity) {
        cap = capacity;
        cache.clear();
        left = new Node(0, 0);
        right = new Node(0, 0);
        left->next = right;
        right->prev = left;
    }

    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            remove(node);
            insert(node);
            return node->val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            remove(cache[key]);
        }
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        insert(newNode);

        if (cache.size() > cap) {
            Node* lru = left->next;
            remove(lru);
            cache.erase(lru->key);
            delete lru;
        }
    }
};
