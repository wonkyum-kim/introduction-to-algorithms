#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Stack {
    std::array<T, N> data;
    size_t top = 0;
    Stack(std::array<T, N> d, size_t t) : data{d}, top{t}   {};
};

template<typename T, size_t N>
bool stack_empty(const Stack<T, N>& s)
{
    return s.top == 0;
}

template<typename T, size_t N>
void push(Stack<T, N>& s, const T& x)
{

    s.data[s.top++] = x;
}

template<typename T, size_t N>
T pop(Stack<T, N>& s)
{
    if(stack_empty(s))
        throw std::underflow_error("Stack underflow");
    else
        return s.data[s.top--];
}

int main()
{
    std::array<int, 5> data;
    size_t top = 0;
    Stack s {data, top};
    for(auto i = 1; i <= 5; i++)
        push(s, i);
    pop(s);
    for(auto j = 0; j < s.top; j++)
        std::cout << s.data[j] << ' ';
}
