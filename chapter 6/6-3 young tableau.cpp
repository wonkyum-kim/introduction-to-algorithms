#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <utility>

constexpr int emp = std::numeric_limits<int>::max();

template<typename T>
void make_young(std::vector<std::vector<T>>& A, int i, int j)
{
	// base case
	if (i == 0 && j == 0) {
		return;
	}
	// handle seperately for the first row
	if (i == 0) {
		if (A[i][j] < A[i][j - 1]) {
			std::swap(A[i][j], A[i][j - 1]);
			make_young(A, i, j - 1);
		}
		return;
	}
	// handle seperately for the first column
	if (j == 0) {
		if (A[i][j] < A[i - 1][j]) {
			std::swap(A[i][j], A[i - 1][j]);
			make_young(A, i - 1, j);
		}
		return;
	}
	// go up
	if (A[i][j] < A[i - 1][j]) {
		std::swap(A[i][j], A[i - 1][j]);
		make_young(A, i - 1, j);
	}
	// go left
	if (A[i][j] < A[i][j - 1]) {
		std::swap(A[i][j], A[i][j - 1]);
		make_young(A, i, j - 1);
	}
}

template<typename T>
std::vector<std::vector<T>> young_tableau(std::vector<T>& keys, int m, int n)
{
	std::vector<std::vector<T>> Y(m, std::vector<T>(n, emp));
	for (auto& x : keys) {
		Y[m - 1][n - 1] = x;
		make_young(Y, m - 1, n - 1);
	}
	return Y;

}

template<typename T>
void fix_tableau(std::vector<std::vector<T>>& A, int i, int j)
{
	int bottom = (i + 1) < A.size() ? A[i + 1][j] : emp;
	int right = (j + 1) < A[0].size() ? A[i][j + 1] : emp;

	if (bottom < right) {
		std::swap(A[i][j], A[i + 1][j]);
		fix_tableau(A, i + 1, j);
	}
	if(bottom > right) {
		std::swap(A[i][j], A[i][j + 1]);
		fix_tableau(A, i, j + 1);
	}
}

template<typename T>
T extract_min(std::vector<std::vector<T>>& A)
{
	T min = A[0][0];
	A[0][0] = emp;
	fix_tableau(A, 0, 0);
	return min;
}

template<typename T>
bool search(std::vector<std::vector<T>>& A, T key) 
{
	int i = 0;
	int j = A[0].size() - 1;
	while (i < A.size() && j >= 0) {
		if (A[i][j] < key) {
			++i;
		}
		else if (A[i][j] > key) {
			--j;
		}
		else {
			return true;
		}
	}
	return false;
}

int main()
{
	std::vector<int> keys { 9,16,3,2,4,8,5,14,12 };
	auto YT = young_tableau(keys, 4, 4);
	for (auto& x : YT) {
		for (auto& y : x) {
			if (y != emp) {
				std::cout << y << ' ';
			}
		}
		std::cout << '\n';
	}
	for (auto i = 0; i < 4 * 4; ++i) {
		std::cout << extract_min(YT) << ' ';
	}
}
