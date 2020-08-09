#include <iostream>
#include <queue>
#include <utility>

template<typename T>
struct Stack {
	std::queue<T> A;
	std::queue<T> B;

	Stack() : A{}, B{}	{};
	void push(const T x);
	T pop();
};

template<typename T>
void Stack<T>::push(const T x)
{
	A.push(x);
}

template<typename T>
T Stack<T>::pop()
{
	while (A.size() > 1)
	{
		T x = A.front();
		A.pop();
		B.push(x);
	}
	T x = A.front();
	A.pop();
	std::swap(A, B);
	return x;
}

int main()
{
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	std::cout << s.pop() << s.pop() << s.pop() << s.pop();
}
