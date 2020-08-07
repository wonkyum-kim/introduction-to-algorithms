#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Double_ended_queue{
    std::array<T, N> data;
    int head = 0;
    int tail = 0;
    Double_ended_queue(std::array<T, N> d, int h, int t) : data{d}, head{h}, tail{t}   {};
    
    void head_enqueue(const T x);
    void tail_enqueue(const T x);
    T head_dequeue();
    T tail_dequeue();
};

template<typename T, size_t N>
void Double_ended_queue<T, N>::head_enqueue(const T x)
{
    // array is full
    if(head == tail + 1 || (head == 0 && tail == data.size()))
        throw std::overflow_error("Queue overflow");
    else
    {
        if(head < 0)        // circular queue
        {
            head == data.size() - 1;
            data[head--] = x;
        }
        else
            data[head--] = x;
    }
}

template<typename T, size_t N>
void Double_ended_queue<T, N>::tail_enqueue(const T x)
{
    // array is full
    if(head == tail + 1 || (head == 0 && tail == data.size()))
        throw std::overflow_error("Queue overflow");
    else
    {
        if(tail == data.size())     // circular queue
        {
            tail = 0;
            data[tail++] = x;
        }
        else
            data[tail++] = x;
    }
}

template<typename T, size_t N>
T Double_ended_queue<T, N>::head_dequeue()
{
    // array is empty
    if(head == tail)
        throw std::underflow_error("Queue underflow");
    else
    {
        if(head == data.size())
        {
            head = 0;
            T x = data[head++];
            return x;
        }
        else
        {
            T x = data[head++];
            return x;
        }
    }
}

template<typename T, size_t N>
T Double_ended_queue<T, N>::tail_dequeue()
{
    // array is empty
    if(head == tail)
        throw std::underflow_error("Queue underflow");
    else
    {
        if(tail < 0)
        {
            tail = data.size() - 1;
            T x = data[tail--];
            return x;
        }
        else
        {
            T x = data[tail--];
            return x;
        }
    }
}

int main()
{
    std::array<int, 4> data;
    int head = -1;
    int tail = 0;
    Double_ended_queue dq {data, head, tail};
    
    dq.tail_enqueue(1);
    dq.tail_enqueue(2);
    dq.tail_enqueue(3);
    dq.tail_enqueue(4);     // 1 2 4 3
    
    std::cout << dq.tail_dequeue() << dq.tail_dequeue() << dq.tail_dequeue() << dq.tail_dequeue();
}
