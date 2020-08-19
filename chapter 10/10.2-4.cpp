#include <iostream>
#include <utility>
#include <memory>

template<typename T>
struct List_node {
    T key;
    std::shared_ptr<List_node<T>> next;
    std::weak_ptr<List_node<T>> prev;
    List_node(const T key) : key{key} {}
};

template<typename T>
class List {
private:
    std::shared_ptr<List_node<T>> nil;
public:
    List()
    {
        nil = std::make_shared<List_node<T>>(T());
        nil->next = nil;
        nil->prev = nil;
    }

    void list_delete(std::shared_ptr<List_node<T>>& x)
    {
        x->prev.lock()->next = x->next;
        x->next->prev = x->prev;
        x.reset();
    }

    std::shared_ptr<List_node<T>> list_search(const T k)
    {
        auto x = nil->next;
        nil->key = k;
        while (x->key != k)
            x = x->next;
        if (x == nil)
            return nullptr;
        return x;
    }

    void list_insert(std::shared_ptr<List_node<T>>& x)
    {
        x->next = nil->next;
        nil->next->prev = x;
        nil->next = x;
        x->prev = nil;
    }
};

int main()
{
    auto x1 = std::make_shared<List_node<int>>(1);
    auto x2 = std::make_shared<List_node<int>>(2);
    auto x3 = std::make_shared<List_node<int>>(3);

    List<int> l;

    l.list_insert(x1);
    l.list_insert(x2);
    l.list_insert(x3);
    l.list_delete(x2);
}
