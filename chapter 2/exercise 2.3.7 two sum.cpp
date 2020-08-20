#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
bool two_sum(std::vector<T>& S, const T& key)
{
	size_t left = 0;
	size_t right = S.size()-1;
	std::sort(S.begin(), S.end());

	while (left < right) {
		if ((S[left] + S[right]) < key)
			left++;
		else if ((S[left] + S[right]) > key)
			right--;
		else
			return true;
	}
	return false;
}

int main()
{
	std::vector<int> S{ 5,2,4,3,1 };
	if(two_sum(S, 5))
	    std::cout << "true";
	else
	    std::cout << "false";
}
