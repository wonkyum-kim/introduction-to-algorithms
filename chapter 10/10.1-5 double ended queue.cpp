#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

template<typename T>
class Deque {
private:
    std::vector<T> data;
    size_t size;

public:
    Deque(int k) : 
        size(k) {}

    void push_front(T value) {
        assert(data.size() != size);
        data.insert(data.begin(), value);
    }

    void push_back(T value) {
        assert(data.size() != size);
        data.push_back(value);
    }

    void pop_front() {
        assert(!data.empty());
        data.erase(data.begin());
    }

    void pop_back() {
        assert(!data.empty());
        data.erase(data.begin() + data.size() - 1);
    }

    T front() {
        assert(!data.empty());
        return data.front();
    }

    T back() {
        assert(!data.empty());
        return data.back();
    }

    bool is_empty() {
        return data.empty();
    }
};
