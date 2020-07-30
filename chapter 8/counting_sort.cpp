#include <iostream>
#include <vector>
#include <algorithm>

void counting_sort(std::vector<int>& A, std::vector<int>& B, std::vector<int>& C)
{
	for (auto i = 0; i < A.size(); i++)
		C[A[i]]++;
	for (auto j = 1; j < C.size(); j++)
		C[j] += C[j - 1];
	for (int k = A.size() - 1; k >= 0; k--)
	{
		B[C[A[k]] - 1] = A[k];
		C[A[k]]--;
	}
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
