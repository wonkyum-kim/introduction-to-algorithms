#include <iostream>
#include <memory>
#include <stdexcept>

template<typename T>
struct List_node {
    T key;
    std::shared_ptr<List_node<T>> next;
    List_node(const T key) : key{key} {}
};

// circular, singly linked list with a sentinel node
template<typename T>
class List{
private:
    std::shared_ptr<List_node<T>> nil;
public:
    List() {
        nil = std::make_shared<List_node<T>>(T());
        nil->next = nil;
    }
    
    void list_delete(const T k) {
        auto prev = nil;
        while(prev->next->key != k) {
            if(prev->next == nil)
                throw std::runtime_error("key does not exist");
            prev = prev->next;
        }
        prev->next = prev->next->next;
    }
    
    std::shared_ptr<List_node<T>> list_search(const T k) {
        auto x = nil->next;
        while(x != nil && x->key != k) 
            x = x->next;
        if(x == nil)
            return nullptr;
        else
            return x;
    }
    
    void list_insert(const T k) {
        auto x = std::make_shared<List_node<T>>(k);
        x->next = nil->next;
        nil->next = x;
    }
};

int main()
{
    List<int> L;
    L.list_insert(1);
    L.list_insert(2);
    L.list_insert(3);
    L.list_delete(3);
}
