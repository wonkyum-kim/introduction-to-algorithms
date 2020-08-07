#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Queue{
    std::array<T, N> data;
    size_t head = 0;
    size_t tail = 0;
    Queue(std::array<T, N> d, size_t h, size_t t) : data{d}, head{h}, tail{t}   {};
};

template<typename T, size_t N>
void enqueue(Queue<T, N>& q, const T x)
{
    // array is full
    if(q.head == q.tail + 1 || (q.head == 0 && q.tail == q.data.size()))
        throw std::overflow_error("Queue overflow");
        
    
    if(q.tail == q.data.size()) // circular queue
    {
        q.tail = 0;
        q.data[q.tail++] = x;
    }
    else
    {
        q.data[q.tail] = x;
        q.tail++;
    }
        
}

template<typename T, size_t N>
T dequeue(Queue<T, N>& q)
{
    // array is empty
    if(q.head == q.tail)
        throw std::underflow_error("Queue underflow");
    
    if(q.head == q.data.size())     // circular Queue
    {
        q.head = 0;
        T x = q.data[q.head];
        return x;
    }
    else
    {
        T x = q.data[q.head];
        q.head++;
        return x;
    }
}

int main()
{
    std::array<int, 4> data;
    size_t head = 1;
    size_t tail = 1;
    
    Queue q {data, head, tail};
    
    for(auto i = 0; i < 4; ++i)
        enqueue(q, i);
    
    for(auto j = 0; j < 4; ++j)
        std::cout << dequeue(q) << " dequeue a element" << '\n';
}
