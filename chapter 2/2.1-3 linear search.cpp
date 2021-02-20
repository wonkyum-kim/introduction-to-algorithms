#include <vector>
#include <iostream>

template<typename T>
int linear_search(const std::vector<T>& A, const T key)
{
	for (size_t i = 0; i < A.size(); ++i) {
		if (key == A[i]) {
			return i;
		}
	}
	return -1;
}

int main()
{
	std::vector<int> v = { 5,2,3,1,4 };
	auto ans = linear_search(v, 3);
	if(ans == -1) {
		std::cout << "NIL";
	}
	else {
		std::cout << ans + 1;
	}
}
