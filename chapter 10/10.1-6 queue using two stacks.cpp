#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <queue>
#include <stack>

template<typename T>
struct Queue {
	std::stack<T> A;
	std::stack<T> B;
	Queue() : A{}, B{}	{};
	void push(const T x);
	T pop();
};

template<typename T>
void Queue<T>::push(const T x) 
{
	A.push(x);
}

template<typename T>
T Queue<T>::pop()
{
	if (B.empty()) {
		while (!A.empty()) {
			T x = A.top();
			A.pop();
			B.push(x);
		}
	}
	T y = B.top();
	B.pop();
	return y;
}

int main()
{
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	std::cout << q.pop() << q.pop() << q.pop() << q.pop();
}
