#include <forward_list>
#include <iostream>

template<typename T>
void push(std::forward_list<T>& L, const T x)
{
    L.push_front(x);
}

template<typename T>
void pop(std::forward_list<T>& L)
{
    L.pop_front();
}

int main()
{
    std::forward_list<int> stack;
    push(stack, 1);     // 1
    push(stack, 2);     // 2 1
    push(stack, 3);     // 3 2 1
    pop(stack);         // 2 1
    std::cout << stack.front(); // 2
}
