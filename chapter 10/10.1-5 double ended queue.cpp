#include<iostream>
#include<array>
#include<stdexcept>

template<typename T, size_t N>
struct Double_ended_queue {
    std::array<T, N> data;
    int head = 0;
    int tail = 0;
    Double_ended_queue() : data{}, head{ 0 }, tail{ 0 }   {};

    void head_enqueue(const T x);
    void tail_enqueue(const T x);
    T head_dequeue();
    T tail_dequeue();
};

template<typename T, size_t N>
void Double_ended_queue<T, N>::head_enqueue(const T x)
{
    if (head == tail + 1 || (head == 0 && tail == data.size() - 1))
        throw std::overflow_error("queue overflow");
    else
    {
        if (head == 0)
            head == data.size() - 1;
        else
            head--;
        data[head] = x;
    }
}

template<typename T, size_t N>
void Double_ended_queue<T, N>::tail_enqueue(const T x)
{
    if (head == tail + 1 || (head == 0 && tail == data.size() - 1))
        throw std::overflow_error("queue overflow");
    else
    {
        data[tail] = x;
        if (tail == data.size() - 1)
            tail = 0;
        else
            tail++;
    }
}

template<typename T, size_t N>
T Double_ended_queue<T, N>::head_dequeue()
{
    // the array is empty
    if (head == tail)
        throw std::underflow_error("Queue underflow");
    else
    {
        T x = data[head];
        if (head == data.size() - 1)
            head = 0;
        else
            head++;
        return x;
    }
}

template<typename T, size_t N>
T Double_ended_queue<T, N>::tail_dequeue()
{
    // the array is empty
    if (head == tail)
        throw std::underflow_error("Queue underflow");
    else
    {
        if (tail == 0)
            tail = data.size() - 1;
        else
            tail--;
        T x = data[tail];
        return x;
    }
}

int main()
{
    Double_ended_queue<int, 50> dq;

    dq.tail_enqueue(1);
    dq.tail_enqueue(2);
    dq.tail_enqueue(3);

    std::cout << dq.tail_dequeue() << dq.tail_dequeue() << dq.tail_dequeue();
}
