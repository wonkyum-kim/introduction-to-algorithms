#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cassert>


template<typename T>
class Circular_Queue {
private:
    using pointer = T*;
    std::unique_ptr<T[]> data;
    const size_t size;
    pointer head;
    pointer tail;

    pointer prev(pointer p) const {
        // p가 맨 앞의 원소를 가리킨다면
        if (p == data.get()) {
            return data.get() + size - 1;
        }
        return p - 1;
    }

    pointer next(pointer p) const {
        // p가 맨 뒤의 원소를 가리킨다면
        if (p == data.get() + size - 1) {
            return data.get();
        }
        return p + 1;
    }
public:
    Circular_Queue(size_t k)
        : data(std::make_unique<T[]>(k)),
        size(k),
        head(data.get()),
        tail(data.get()) {}

    void push(const T value) {
        assert(!is_full(), "queue overflow");
        *tail = value;
        tail = next(tail);
        if (tail == head) {
            tail = nullptr;
        }
    }

    void pop() {
        assert(!is_empty(), "queue underflow");
        if (is_full()) {
            tail = head;
        }
        head = next(head);
    }

    T front() {
        assert(!is_empty(), "empty");
        return *head;
    }

    T back() {
        assert(!is_empty(), "empty");
        return *prev(tail);
    }

    bool is_empty() {
        return head == tail;
    }

    bool is_full() {
        return tail == nullptr;
    }
 };


int main()
{
    Circular_Queue<int> cq(6);
    cq.push(4);
    cq.push(1);
    cq.push(3);
    cq.pop();
    cq.push(8);
    cq.pop();
    while (!cq.is_empty()) {
        std::cout << cq.front() << ' ';
        cq.pop();
    }
}
