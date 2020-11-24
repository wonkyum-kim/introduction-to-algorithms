#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>
#include <utility>
#include <cassert>

std::mt19937 gen(std::random_device{}());

template<typename T>
bool two_sum(std::vector<T>& S, const T& key)
{
	size_t left = 0;
	size_t right = S.size() - 1;
	std::sort(S.begin(), S.end());

	while (left < right) {
		if ((S[left] + S[right]) < key) {
			left++;
		}
		else if ((S[left] + S[right]) > key) {
			right--;
		}
		else {
			return true;
		}
	}
	return false;
}


int main()
{
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 0);
	std::shuffle(v.begin(), v.end(), gen);
	// nlogn
	std::sort(v.begin(), v.end());
	if (two_sum(v, 5000)) {
		std::cout << "true";
	}
	else {
		std::cout << "false";
	}
}
