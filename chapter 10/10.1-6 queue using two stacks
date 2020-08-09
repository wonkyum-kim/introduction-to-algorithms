#include <iostream>
#include <stack>

template<typename T>
struct Queue {
	std::stack<T> A;
	std::stack<T> B;
	
	Queue() : A{}, B{}	{};
	void enqueue(const T x);
	T dequeue();
};

template<typename T>
void Queue<T>::enqueue(const T x)
{
	A.push(x);
}

template<typename T>
T Queue<T>::dequeue()
{
	if (B.empty())
	{
		while (!A.empty())
		{
			T x = A.top();
			A.pop();
			B.push(x);
		}
	}
	T x = B.top();
	B.pop();
	return x;
}

int main()
{
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	std::cout << q.dequeue() << q.dequeue() << q.dequeue() << q.dequeue();
}
