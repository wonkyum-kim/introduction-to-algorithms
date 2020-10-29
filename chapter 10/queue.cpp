#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

constexpr int dummy = 0;

template<typename T>
struct Queue {
	//--------------------------------

	std::vector<T> data;
	int head;
	int tail;

	//--------------------------------

	Queue() : data{ dummy }, head{1}, tail{1} {};
	void enqueue(const T x);
	T dequeue();

	//--------------------------------
};

template<typename T>
void Queue<T>::enqueue(const T x)
{
	data.push_back(x);
	tail++;
}

template<typename T>
T Queue<T>::dequeue()
{
	T x = data[head];
	head++;
	return x;
}

int main()
{
	Queue<int> q;
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);
	q.enqueue(4);
	q.enqueue(5);
	std::cout << q.dequeue() << q.dequeue() << q.dequeue();
}
