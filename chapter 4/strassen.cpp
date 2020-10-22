#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <numeric>
#include <string>

template<typename T>
std::vector<std::vector<T>> make_matrix(const size_t n, const size_t m)
{
	std::vector<std::vector<T>> matrix(n + 1, std::vector<T>(m + 1));
	for (auto i = 1; i <= n; ++i) {
		for (auto j = 1; j <= m; ++j) {
			std::cin >> matrix[i][j];
		}
	}
	return matrix;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& A) {
	for (auto i = 1; i < A.size(); ++i) {
		for (auto j = 1; j < A[0].size(); ++j) {
			os << A[i][j] << ' ';
		}
		os << '\n';
	}
	return os;
}

template<typename T>
std::vector<std::vector<T>> operator+(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
	std::vector<std::vector<T>> result(A.size(), std::vector<T>(A[1].size()));
	for (auto i = 1; i < A.size(); ++i) {
		for (auto j = 1; j < A[1].size(); ++j) {
			result[i][j] = A[i][j] + B[i][j];
		}
	}
	return result;
}

template<typename T>
std::vector<std::vector<T>> operator-(const std::vector<std::vector<T>>& A, const std::vector<std::vector<T>>& B)
{
	std::vector<std::vector<T>> result(A.size(), std::vector<T>(A[1].size()));
	for (auto i = 1; i < A.size(); ++i) {
		for (auto j = 1; j < A[1].size(); ++j) {
			result[i][j] = A[i][j] - B[i][j];
		}
	}
	return result;
}

template<typename T>
void strassen(std::vector<std::vector<T>>& A, std::vector<std::vector<T>>& B, std::vector<std::vector<T>>& C, size_t n)
{
	// size_t n = A.size() - 1;
	// A and B must be n x n matrix.
	if (n == 1) {
		C[1][1] = A[1][1] * B[1][1];
		return;
	}
	else {
		size_t m = n / 2;
		/************************************************************/
		std::vector<std::vector<T>> A11(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> A12(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> A21(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> A22(m + 1, std::vector<T>(m + 1));
		/************************************************************/
		std::vector<std::vector<T>> B11(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> B12(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> B21(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> B22(m + 1, std::vector<T>(m + 1));
		/************************************************************/
		std::vector<std::vector<T>> P1(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P2(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P3(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P4(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P5(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P6(m + 1, std::vector<T>(m + 1));
		std::vector<std::vector<T>> P7(m + 1, std::vector<T>(m + 1));
		/************************************************************/

		for (auto i = 1; i <= m; ++i) {
			for (auto j = 1; j <= m; ++j) {
				A11[i][j] = A[i][j];
				A12[i][j] = A[i][j + m];
				A21[i][j] = A[i + m][j];
				A22[i][j] = A[i + m][j + m];
				B11[i][j] = B[i][j];
				B12[i][j] = B[i][j + m];
				B21[i][j] = B[i + m][j];
				B22[i][j] = B[i + m][j + m];
			}
		}

		/************************************************************/
		auto S1 = B12 - B22;
		auto S2 = A11 + A12;
		auto S3 = A21 + A22;
		auto S4 = B21 - B11;
		auto S5 = A11 + A22;
		auto S6 = B11 + B22;
		auto S7 = A12 - A22;
		auto S8 = B21 + B22;
		auto S9 = A11 - A21;
		auto S10 = B11 + B12;
		/************************************************************/
		strassen(A11, S1, P1, m);					// P1 = A11 * S1
		strassen(S2, B22, P2, m);					// P2 = S2 * B22
		strassen(S3, B11, P3, m);					// P3 = S3 * B11
		strassen(A22, S4, P4, m);					// P4 = A22 * S4
		strassen(S5, S6, P5, m);					// P2 = S5 * S6
		strassen(S7, S8, P6, m);					// P6 = S7 * S8
		strassen(S9, S10, P7, m);					// P7 = S9 * S10
		/************************************************************/
		auto C11 = P5 + P4 - P2 + P6;
		auto C12 = P1 + P2;
		auto C21 = P3 + P4;
		auto C22 = P5 + P1 - P3 - P7;
		/************************************************************/

		for (auto i = 1; i <= m; ++i) {
			for (auto j = 1; j <= m; ++j) {
				C[i][j] = C11[i][j];
				C[i][j + m] = C12[i][j];
				C[i + m][j] = C21[i][j];
				C[i + m][j + m] = C22[i][j];
			}
		}
	}
}

int main()
{	
	auto m1 = make_matrix<int>(2, 2);
	auto m2 = make_matrix<int>(2, 2);
	std::vector<std::vector<int>> m3(3, std::vector<int>(3));
	strassen(m1, m2, m3, 2);
	std::cout << m3;
}
