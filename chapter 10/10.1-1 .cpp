#include <vector>
#include <iostream>
#include <algorithm>
#include <memory>
#include <cassert>

template<typename T>
class Stack {
private:
	std::vector<T> data;
	int size;
	int t;

public:
	Stack(size_t k) : size(k), t(-1) {
		data.resize(k);
	}

	bool is_empty() {
		return t == -1;
	}

	void push(T x) {
		assert(t != data.size());
		t++;
		data[t] = x;
	}

	void pop() {
		assert(!is_empty());
		t--;
	}

	T top() {
		assert(!is_empty());
		return data[t];
	}
};

int main()
{
	Stack<int> s(6);
	s.push(4);
	std::cout << s.top() << '\n';
	s.push(1);
	std::cout << s.top() << '\n';
	s.push(3);
	std::cout << s.top() << '\n';
	s.pop();
	std::cout << s.top() << '\n';
	s.push(8);
	std::cout << s.top() << '\n';
	s.pop();
	std::cout << s.top() << '\n';
}
