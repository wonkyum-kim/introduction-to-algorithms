#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cassert>

template<typename T>
class Stack {
private:
	std::unique_ptr<T[]> data;
	size_t size;
	size_t t;

public:
	Stack(size_t k) :
		data(std::make_unique<T[]>(k)),
		size(k),
		t(0) {}

	bool is_empty() {
		return t == 0;
	}

	bool is_full() {
		return t == size;
	}

	void push(T x) {
		assert(!is_full());
		auto p = data.get() + t;
		*p = x;
		t++;
	}

	void pop() {
		assert(!is_empty());
		t--;
	}

	T top() {
		assert(!is_empty());
		auto p = data.get() + t - 1;
		return *p;
	}
};

int main()
{
	Stack<int> s(6);
	s.push(4);
	s.push(1);
	s.push(3);
	s.pop();
	s.push(8);
	s.pop();
}
