#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Two_Stack {

    std::array<T, N> data;
    int left;
    int right;

    Two_Stack() : data{}, left{ -1 }, right{ N }  {};

    void push_l(const T x) {
        if (left + 1 == right) {
            throw std::overflow_error("Stack overflow");
        }
        else {
            data[++left] = x;
        }
    }

    void push_r(const T x) {
        if (left + 1 == right) {
            throw std::overflow_error("Stack overflow");
        }
        else {
            data[--right] = x;
        }
    }

    T pop_l() {
        if (left == -1) {
            throw std::underflow_error("stack underflow");
        }
        else {
            return data[left--];
        }
    }

    T pop_r() {
        if (right == data.size()) {
            throw std::underflow_error("stack underflow");
        }
        else {
            return data[right++];
        }
    }
};

int main()
{
    Two_Stack<int, 4> ts;
    ts.push_l(1);
    ts.push_l(2);
    ts.push_r(4);
    ts.push_r(3);

    std::cout << ts.pop_l() << ' ' << ts.pop_l() << ' ' << ts.pop_r() << ' ' << ts.pop_r();     // 2 1 3 4
}
