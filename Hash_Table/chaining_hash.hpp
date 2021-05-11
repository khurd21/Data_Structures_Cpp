#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>

// Custom project includes
#include "hash.h"


// Separate chaining based hash table - derived from Hash
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:

	// Private Vars
	struct hashed_item {
		std::pair<K,V> item;

		hashed_item(
				std::pair<K,V>& i = std::pair<K,V>{}
				) : item{i} { }

		hashed_item(
				std::pair<K,V>&& i
				) : item{std::move(i)} { }
	};

	std::vector<std::list<hashed_item>> list;
	int current_size;
	float LOAD_FACTOR_MAX = 0.75;

	// Private Functions

    int next_prime(int n) {
        while (is_prime(n) == false) {
            n++;
        }
        return n;
    }

    int is_prime(const int& n) {
		if (n <= 1) return false;
		if (n == 2) return true;

		int range = n;
        for (int i = 2; i < range; i++) {
            if (n % i == 0) {
                return false;
            }
			range = n / i;
        }
        return true;
    }

    size_t hash(const K& key) const {
        return key % this->list.size(); 
    }

	void rehash() {
		std::vector<std::list<hashed_item>> copy_list = this->list;
		this->list.resize(next_prime(2*this->list.size()));
		for (auto& l : this->list) {
			l.clear();
		}

		this->current_size = 0;
		for (auto& l : copy_list) {
			for (auto& entry : l) {
				insert(std::move(entry.item));
			}
		}
	}

public:
    explicit ChainingHash(int n = 11)
		: list(next_prime(n)) { clear(); }

    ~ChainingHash() {
        this->clear();
    }

    bool insert(const std::pair<K,V>& pair) {
		auto& l = this->list[hash(pair.first)];
		auto itr = std::find_if(std::begin(l), std::end(l), 
				[&](const hashed_item& element) { 
					return element.item.first == pair.first;
					});

		if (itr != std::end(l)) {
			return false;
		}
		this->current_size += 1;
		std::pair<K,V> tmp = pair;
		l.push_back(hashed_item{tmp});
		if (load_factor() > LOAD_FACTOR_MAX) {
			rehash();
		}
        return true;
    }

	bool contains(const K& key) const {
		auto& l = this->list[hash(key)];
		return std::find_if(std::begin(l), std::end(l),
				[&](const hashed_item& element) {
					return element.item.first == key;
				}) != std::end(l); 
	}

    bool erase(const K& key) {
		auto& l = this->list[hash(key)];
		auto itr = std::find_if(std::begin(l), std::end(l),
				[&](const hashed_item& element) {
			   		return element.item.first == key; 
			   		});

		if (itr == std::end(l)) {
			return false;
		}
		this->current_size -= 1;
		l.erase(itr);
		return true;
    }

    void clear() {
		this->current_size = 0;
		for (auto& l : this->list) {
			l.clear();
		}
    }

    int size() const {
        return this->current_size;
    }

    int bucket_count() const {
        return this->list.size();
    }

    float load_factor() const {
        return (float)this->current_size / this->list.size();
    }

    V operator[](const K& key) const {
		auto& l = this->list[hash(key)];
		auto itr = std::find_if(std::begin(l), std::end(l),
				[&](const hashed_item& element) {
					return element.item.first == key;
				});
		if (itr == std::end(l)) {
			return V{};
		}
		return itr->item.second;
    }
};

#endif //__CHAINING_HASH_H
