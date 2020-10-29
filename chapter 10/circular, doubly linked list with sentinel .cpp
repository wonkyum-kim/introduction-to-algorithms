#include <iostream>
#include <utility>
#include <memory>

template<typename T>
struct Node {
	T data;
	std::shared_ptr<Node<T>> next;
	std::weak_ptr<Node<T>> prev;
	Node(const T data) : data{data} {}
};

template<typename T>
class List {
private:
	std::shared_ptr<Node<T>> nil;
public:
	List() {
		nil = std::make_shared<Node<T>>(T());
		nil->next = nil;
		nil->prev = nil;
	}

	std::shared_ptr<Node<T>> search(const T k) {
		auto x = nil->next;
		while (x != nil && x->data != k) {
			x = x->next;
		}
		if (x == nil) {
			return nullptr;
		}
		return x;
	}

	void pop(std::shared_ptr<Node<T>>& x) {
		x->prev.lock()->next = x->next;
		x->next->prev = x->prev;
		x.reset();
	}

	void pop(const T k) {
		std::shared_ptr<Node<T>> x = search(k);
		if (x) {
			pop(x);
		}
	}

	void push(const T k) {
		auto x = std::make_shared<Node<T>>(k);
		push(x);
	}

	void push(std::shared_ptr<Node<T>>& x) {
		x->next = nil->next;
		nil->next->prev = x;
		nil->next = x;
		x->prev = nil;
	}
};

int main()
{
	List<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	l.pop(2);
}
