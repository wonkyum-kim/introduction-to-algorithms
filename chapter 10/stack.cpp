#include <iostream>
#include <array>
#include <stdexcept>


template<typename T, size_t N>
struct Stack {
	std::array<T, N> data;
	int top;

	Stack(int t) : data{}, top{ t }	{};
	bool stack_empty();
	void push(const T x);
	T pop();
};

template<typename T, size_t N>
bool Stack<T, N>::stack_empty()
{
	if (top == -1)
		return true;
	else
		return false;
}

template<typename T, size_t N>
void Stack<T, N>::push(const T x)
{
	data[++top] = x;
}

template<typename T, size_t N>
T Stack<T, N>::pop()
{
	if (stack_empty())
		throw std::underflow_error("stack underflow");
	else
		return data[top--];
}

int main()
{
	Stack<int, 50> s(-1);
	s.push(1);	// top == 0
	s.push(2);	// top == 1
	s.push(3);	// top == 2
	s.push(4);	// top == 3
	s.push(5);	// top == 4
	std::cout << s.pop() << s.pop() << s.pop() << s.pop() << s.pop();
}
