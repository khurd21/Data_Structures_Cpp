#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "hash.hpp"

enum EntryState {EMPTY=0,ACTIVE=1,DELETED=2};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> {
private:

	// Vars

	struct hashed_item {
		std::pair<K,V> item;
		EntryState state;

		hashed_item(
				const std::pair<K,V>& i = std::pair<K,V>{},
				EntryState st = EMPTY
				) : item{i}, state{st} { }

		hashed_item(
				std::pair<K,V>&& i,
				EntryState st = EMPTY
				) : item{std::move(i)}, state{st} { }

	};

	std::vector<hashed_item> array;
	int current_size;
	float LOAD_FACTOR_MAX = 0.75;

	// Private Functions

	bool is_active(int current_position) const {
		return array[current_position].state == ACTIVE;
	}

	int find_position(const K& k) const {
		int offset = 1;
		int current_position = hash(k);
		
		while (array[current_position].state != EMPTY &&
				array[current_position].item.first != k) {
			current_position += offset;
			// Uncomment for quadratic probing
			// offset += 2;
			if ((int)array.size() > current_position) {
				current_position -= array.size();
			}
		}
		return current_position;
	}

	void rehash() {
		std::vector<hashed_item> old_array = array;

		array.resize(next_prime(2*old_array.size()));
		for (auto& entry : array) {
			entry.state = EMPTY;
		}

		this->current_size = 0; 
		for (auto& entry : old_array) {
			if (entry.state == ACTIVE) {
				insert(std::move(entry.item));
			}
		}
	}

	size_t hash(const K& k) const {
		return k % array.size();
	}

    int next_prime(int n) {
        while (is_prime(n) == false) {
            n++;
        }
        return n;
    }

    int is_prime(const int& n) {
		if (n <= 1) return false;

		int range = n;
		for (int i = 2; i < range; ++i) {
			if (n % i == 0) return false;
			range = n / i;
		}
		return true;
    }

public:

    explicit ProbingHash(int n = 11)
		: array(next_prime(n)) { clear(); }

    ~ProbingHash() {
	   clear();
	}


	bool contains(const K& k) const {
		return is_active(find_position(k));
	}

    bool insert(const std::pair<K, V>& p) {
		int current_position = find_position(p.first);
		if (is_active(current_position)) {
			return false;
		}
		array[current_position].item = p;
		array[current_position].state = ACTIVE;

		this->current_size += 1;
		if (load_factor() > LOAD_FACTOR_MAX) {
			rehash();
		}
        return true;
    }

    bool erase(const K& k) {
		int current_position = find_position(k);
		if (is_active(current_position) == false) {
			return false;
		}
		this->current_size -= 1;
		array[current_position].state = DELETED;
		return true;
    }

	void clear() {
		this->current_size = 0;
		for(auto& entry : array) {
			entry.state = EMPTY;
		}
	}

    int size() const { 
		return this->current_size;
	}

    int bucket_count() const {
		return array.size();
    }

    float load_factor() const {
        return (float)this->current_size / array.size();
    }

    V operator[](const K& key) const {
        return array[find_position(key)].item.second;
    }
};

#endif //__PROBING_HASH_H
