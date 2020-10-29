#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

constexpr int dummy = 0;

template<typename T>
struct Stack {
	//--------------------------------

	std::vector<T> data;
	int top = 0;

	//--------------------------------

	Stack() : data{dummy}, top{} {};
	bool stack_empty();
	void push(const T x);
	T pop();

	//--------------------------------
};

template<typename T>
bool Stack<T>::stack_empty()
{
	if (top == 0) {
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
void Stack<T>::push(const T x)
{
	top++;
	data.push_back(x);
}

template<typename T>
T Stack<T>::pop()
{
	assert(!stack_empty(), "stack underflow");
	return data[top--];
}

int main()
{
	Stack<int> s;
	s.push(1);	// top == 1
	s.push(2);	// top == 2
	s.push(3);	// top == 3
	s.push(4);	// top == 4
	s.push(5);	// top == 5
	std::cout << s.pop() << s.pop() << s.pop() << s.pop() << s.pop();

}
