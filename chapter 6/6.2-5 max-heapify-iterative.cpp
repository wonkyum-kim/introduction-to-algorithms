#include <algorithm>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <numeric>
#include <string>
#include <queue>
#include <cassert>
#include <map>
#include <set>
#include <tuple>
#include <deque>
#include <stack>
#include <random>

std::mt19937 gen(std::random_device{}());
std::vector<int> A;

int parent(int i)
{
	return i >> 1;
}

int left(int i)
{
	return i << 1;
}

int right(int i)
{
	return (i << 1) + 1;
}

void max_heapify(int i)
{
	while (i < A.size()) {
		int l = left(i);
		int r = right(i);
		int largest = i;
		if (l < A.size() && A[l] > A[i]) {
			largest = l;
		}
		if (r < A.size() && A[r] > A[largest]) {
			largest = r;
		}
		if (largest != i) {
			std::swap(A[i], A[largest]);
			i = largest;
		}
		else {
			return;
		}
	}
}

void build_max_heap()
{
	for (int i = (A.size() - 1) / 2; i >= 1; --i) {
		max_heapify(i);
	}
}

int main()
{
	A.resize(10);
	std::iota(A.begin() + 1, A.end(), 1);
	std::shuffle(A.begin() + 1, A.end(), gen);
	build_max_heap();
	for (auto x : A) {
		std::cout << x << ' ';
	}

}
