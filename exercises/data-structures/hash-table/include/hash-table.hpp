# pragma once
#include <string>
#include <vector>
#include <list>



struct Entry {
    std::string key;
    int value;
};

class HashTable {
private:
    std::vector<std::list<Entry>> table;
    int size;
    int count;
    size_t hash(const std::string& key);
public:
    HashTable(int size = 53);
    void push(const std::string& key, int value);
    int get_count();
    int get(const std::string& key);
    bool remove(const std::string& key);
    bool contains(const std::string& key);
    void rehash();
    size_t hashWithSize(const std::string& key, int s);


};