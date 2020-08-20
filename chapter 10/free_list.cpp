#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>

// let's start at first elemnt.
int free_space = 7;

template<typename T, size_t N>
struct Free_list {
    //std::array<T, N> prev;
    std::array<T, N> next;
    std::array<T, N> key;
    int dummy;
    
    // -1 meams that there is not a prev or next element.
    Free_list() : next{-1}, key{}, dummy{0} {}
    
    void traverse() {
        int cur = next[dummy];
        while(cur != -1) {
            std::cout << key[cur] << ' ';
            cur = next[cur];
        }
        std::cout << '\n';
    }
    
    size_t allocate_object() {
        if(free_space == -1)
            std::runtime_error("out of space");
        else {
            size_t x = free_space;
            // the next object allocated is the last one freed.
            free_space = next[7];
            return x;
        }
    }
    
    void free_object(size_t x) {
        next[x] = free_space;
        free_space = x;
    }
    
    // list_insert, list_delete....
}

int main()
{
    Free_list<int, 9> L;
    
    // dummy->9->16->4->1
    L.next[L.dummy] = 7;
    L.next[2] = 3;
    L.key[2] = 4;
    /*L.prev[2] = 5;*/
    L.key[3] = 1;
    /*L.prev[3] = 2;*/
    L.next[5] = 2;
    L.key[5] = 16;
    /*L.prev[5] = 7;*/
    L.next[7] = 5;
    L.key[7] = 9;
    
}
