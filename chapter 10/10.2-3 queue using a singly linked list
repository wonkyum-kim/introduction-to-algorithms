#include <forward_list>
#include <iostream>

template<typename T>
void enqueue(std::forward_list<T>& L, const T x)
{
    auto it = L.before_begin();
    L.insert_after(it, x);
}

template<typename T>
void dequeue (std::forward_list<T>& L)
{
    L.pop_front();
}

int main()
{
    std::forward_list<int> queue;
    enqueue(queue, 1);      // 1
    enqueue(queue, 2);      // 2 1
    enqueue(queue, 3);      // 3 2 1
    dequeue(queue);         // 2 1
    std::cout << queue.front(); // 2
}
