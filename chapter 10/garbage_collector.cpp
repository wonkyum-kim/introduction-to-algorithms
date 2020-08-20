#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

template<typename T, size_t N>
struct Garbage_collector {
    std::array<T, N> prev;
    std::array<T, N> next;
    std::array<T, N> key;
    
    int free = 0;
    int head = 0;
    
    Garbage_collector() : key{} {
        for(int i = 0; i < N; ++i) {
            prev[i] = i - 1;
            next[i] = i + 1;
        }
        next[N - 1] = -1;
    }
    
    size_t allocate_object() {
        if(free == -1)
            throw std::runtime_error("out of space");
        else {
            size_t x = free;
            free = next[x];
            return x;
        }
    }
    
    void free_object(size_t x) {
        next[x] = free;
        free = x;
    }
};

int main()
{
    
}
