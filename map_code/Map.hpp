// Map.hpp
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <string>
#include <utility>
#include <stdexcept>

template<typename KeyType, typename ValueType>
class Map {
private:
    // We'll use a vector of pairs to store our key-value pairs
    std::vector<std::pair<KeyType, ValueType>> entries;
    
    // Helper function to find a key's position
    int findKeyPosition(const KeyType& key) const;

public:
    // Put something in the map with a key
    void put(const KeyType& key, const ValueType& value);
    
    // Get something from the map using its key
    ValueType get(const KeyType& key) const;
    
    // Check if a key exists in the map
    bool contains(const KeyType& key) const;
    
    // Remove an entry by key
    void remove(const KeyType& key);
    
    // Get all the keys in the map
    std::vector<KeyType> getKeys() const;
    
    // Get all the values in the map
    std::vector<ValueType> getValues() const;
    
    // Check if the map is empty
    bool isEmpty() const;
    
    // Get the number of entries in the map
    size_t size() const;
};

// Implementation of template methods

template<typename KeyType, typename ValueType>
int Map<KeyType, ValueType>::findKeyPosition(const KeyType& key) const {
    for (size_t i = 0; i < entries.size(); i++) {
        if (entries[i].first == key) {
            return static_cast<int>(i);
        }
    }
    return -1;  // Key not found
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
    int pos = findKeyPosition(key);
    if (pos != -1) {
        // Key already exists, update the value
        entries[pos].second = value;
    } else {
        // Add new key-value pair
        entries.push_back(std::make_pair(key, value));
    }
}

template<typename KeyType, typename ValueType>
ValueType Map<KeyType, ValueType>::get(const KeyType& key) const {
    int pos = findKeyPosition(key);
    if (pos != -1) {
        return entries[pos].second;
    }
    throw std::out_of_range("Key not found in map");
}

template<typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::contains(const KeyType& key) const {
    return findKeyPosition(key) != -1;
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType& key) {
    int pos = findKeyPosition(key);
    if (pos != -1) {
        entries.erase(entries.begin() + pos);
    }
}

template<typename KeyType, typename ValueType>
std::vector<KeyType> Map<KeyType, ValueType>::getKeys() const {
    std::vector<KeyType> keys;
    for (const auto& entry : entries) {
        keys.push_back(entry.first);
    }
    return keys;
}

template<typename KeyType, typename ValueType>
std::vector<ValueType> Map<KeyType, ValueType>::getValues() const {
    std::vector<ValueType> values;
    for (const auto& entry : entries) {
        values.push_back(entry.second);
    }
    return values;
}

template<typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::isEmpty() const {
    return entries.empty();
}

template<typename KeyType, typename ValueType>
size_t Map<KeyType, ValueType>::size() const {
    return entries.size();
}

#endif // MAP_HPP