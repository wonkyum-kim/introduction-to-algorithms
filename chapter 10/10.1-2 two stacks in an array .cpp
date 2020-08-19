#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Two_Stack {
    std::array<T, N> data;
    size_t left;
    size_t right;

    Two_Stack(size_t l, size_t r) : data{}, left{ l }, right{ r }  {};
    void push_l(const T x);
    void push_r(const T x);
    T pop_l();
    T pop_r();
};

template<typename T, size_t N>
void Two_Stack<T, N>::push_l(const T x)
{
    if (right < left)
        throw std::overflow_error("Stack overflow");
    else
        data[left++] = x;
}

template<typename T, size_t N>
void Two_Stack<T, N>::push_r(const T x)
{
    if (right < left)
        throw std::overflow_error("Stack overflow");
    else
        data[right--] = x;
}

template<typename T, size_t N>
T Two_Stack<T, N>::pop_l()
{
    if (left == -1)
        throw std::underflow_error("stack underflow");
    else
        return data[left--];
}

template<typename T, size_t N>
T Two_Stack<T, N>::pop_r()
{
    if (right == data.size())
        throw std::underflow_error("stack underflow");
    else
        return data[right++];
}

int main()
{
    Two_Stack<int,50> ts{-1, 50};
    ts.push_l(1);
    ts.push_l(2);
    ts.push_r(4);
    ts.push_r(3);

    std::cout << ts.pop_l() << ' ' << ts.pop_l() << ' ' << ts.pop_r() << ' ' << ts.pop_r();     // 2 1 3 4
}
