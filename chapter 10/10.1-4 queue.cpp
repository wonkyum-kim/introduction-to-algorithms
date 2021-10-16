#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cassert>
#include <array>


template<typename T, size_t N>
struct Queue {
    std::array<T, N> data;
    int f;
    int size;

    Queue() : data{}, f{ 0 }, size{ 0 } {};

    bool is_empty() {
        return size == 0;
    }

    void enqueue(const T x) {
        int temp = (f + size) % N;
        assert(size != N);
        data[temp] = x;
        size++;
    }

    void dequeue() {
        assert(!is_empty());
        f = (f + 1) % N;
        size--;
    }

    T front() {
        assert(!is_empty());
        return data[f];
    }
};


int main()
{
    Queue<int, 5> q;
    q.enqueue(3);
    std::cout << q.front() << '\n';
    q.enqueue(5);
    std::cout << q.front() << '\n';
    q.dequeue();
    std::cout << q.front() << '\n';
    q.dequeue();
    if (q.is_empty()) {
        std::cout << "empty\n";
    }
}
