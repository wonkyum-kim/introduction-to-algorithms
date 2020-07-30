#include <iostream>
#include <vector>
#include <algorithm>

void counting_sort(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
{
	for (auto j = 0; j < A.size(); j++)
		C[A[j]]++;
	for (auto i = 1; i < C.size(); i++)
		C[i] += C[i - 1];
	for (auto i = A.size() - 1; i > 0; i--)
	{
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--;
	}
	B[C[A[0]] - 1] = A[0];
}



int main()
{
	std::vector<int> A{ 2,5,3,0,2,3,0,3 };
	std::vector<int>::iterator k;
	k = std::max_element(A.begin(), A.end());

	std::vector<int> C((*k) + 1);
	std::vector<int> B(A.size());

	counting_sort(A, B, C);
	for (auto x : B)
		std::cout << x << ' ';
}
