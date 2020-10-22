#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

template<typename T>
std::vector<T> merge_array(std::vector<std::vector<T>>& A) 
{
	std::vector<T> min_heap;
	std::vector<T> merged;
	while (true) {
		for (auto i = 0; i < A.size(); ++i) {
			if (!A[i].empty()) {
				min_heap.push_back(A[i].front());
				std::cout << i << "번째 배열의 원소 " << A[i].front() << '\n';
				A[i].erase(A[i].begin());
			}
			else {
				A.erase(A.begin() + i);
			}
		}
		std::make_heap(min_heap.begin(), min_heap.end(), std::greater<T>{});
		merged.push_back(min_heap.front());
		min_heap.erase(min_heap.begin(), min_heap.end());
		if (A.size() == 0) {
			break;
		}
	}
	return merged;
}


int main()
{
	std::vector<int> A1{ 1,2,3,4,5 };
	std::vector<int> A2{ 5,6,7 };
	std::vector<std::vector<int>> A{ A1,A2 };
	auto merged = merge_array(A);
	for (auto x : merged) {
		std::cout << x << ' ';
	}
}
