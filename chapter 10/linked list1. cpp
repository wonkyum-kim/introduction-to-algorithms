#include <iostream>
#include <memory>
#include <utility>

template<typename T>
struct List_node {
	T key;
	List_node<T>* prev;
	std::unique_ptr<List_node<T>> next;
	List_node(const T key) : key{key}	{}
};

template<typename T>
struct List {
	std::unique_ptr<List_node<T>> head;
};

template<typename T>
List_node<T>* list_search(const List<T>& L, const T k)
{
	auto x = L.head.get();
	while (x && x->key != k)
		x = x->next.get();
	return x;
}

template<typename T>
void list_insert(List<T>& L, std::unique_ptr<List_node<T>> x)
{
	if (L.head)
		L.head->prev = x.get();
	x->next = std::move(L.head);
	L.head = std::move(x);
}

template<typename T>
void list_delete(List<T>& L, List_node<T>* x)
{
	if (x->prev)
		x->prev->next = std::move(x->next);
	else
		L.head = std::move(x->next);
	if (x->next)
		x->next->prev = x->prev;
}

int main() 
{
	auto x1 = std::make_unique<List_node<int>>(1);
	auto x2 = std::make_unique<List_node<int>>(2);
	auto x3 = std::make_unique<List_node<int>>(3);
	List<int> l;
	list_insert(l, std::move(x1));
	list_insert(l, std::move(x2));
	list_insert(l, std::move(x3));
	list_delete(l, list_search(l, 2));
}
