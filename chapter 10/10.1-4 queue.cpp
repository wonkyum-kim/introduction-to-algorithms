#include <iostream> 
#include <array> 
#include <stdexcept> 

template<typename T, size_t N> 
struct Queue {
 	std::array<T, N> data;
 	int head;
 	int tail;
 	Queue(int h, int t) : data{}, head{ h }, tail{ t }	{};
 	void enqueue(const T x);
 	T dequeue(); 
}; 

template<typename T, size_t N> 
void Queue<T, N>::enqueue(const T x) 
{
        if (head == tail + 1 || (head == 0 && tail == data.size() - 1))
                throw std::overflow_error ("queue overflow");
 	data[tail] = x;
 	if (tail == data.size() - 1)
 		tail = 0;
 	else
 		tail++;
}

template<typename T, size_t N> T Queue<T, N>::dequeue() 
{
        if (head == tail)
                throw std::underflow_error ("queue underflow");
 	T x = data[head];
 	if (head == data.size() - 1)
 		head = 0;
 	else
 		head++;
 	return x; 
}

int main()
{
 	Queue<int, 50> q(0, 0);
 	q.enqueue(0);
 	q.enqueue(1);
 	q.enqueue(2);
 	q.enqueue(3);
 	std::cout << q.dequeue() << q.dequeue() << q.dequeue() << q.dequeue(); 
}
