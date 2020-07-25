#include <iostream>
#include <vector>


/* the result of this code is false */
/* not to use right now*/

template<typename T>
int merge(std::vector<T>& A, size_t left, size_t mid, size_t right)
{
	size_t i = left;
	size_t j = mid + 1;
	int count = 0;

	std::vector<T> sorted;

	while (i <= mid && j <= right)
	{
		if (A[i] <= A[j])
			sorted.push_back(A[i++]);
		else
		{
			sorted.push_back(A[j++]);
			count++;
		}
			
	}

	if (i > mid)
	{
		while (j <= right)
			sorted.push_back(A[j++]);
	}
	else if (j > right)
	{
		while (i <= mid)
			sorted.push_back(A[i++]);
	}

	size_t k = 0;
	for (size_t i = left; i <= right; i++)
		std::swap(A[i], sorted[k++]);

	return count;
}

template<typename T>
int inversion_count(std::vector<T>& A, size_t left, size_t right)
{
	if (left < right)
	{
		size_t mid = (left + right) / 2;
		int count = 0;

		count += inversion_count(A, left, mid);
		count += inversion_count(A, mid + 1, right);
		count += merge(A, left, mid, right);
		return count;
	}
	else
		return 0;
}

template<typename T>
int inversion(std::vector<T>& A)
{
	return inversion_count(A, 0, A.size() - 1);
}


int main()
{
	std::vector<int> A{ 5,2,4,1,3 };
	std::cout << inversion(A);

	return 0;
}

/*

pair(0,1) pair(0,2) pair(0,3) pair(0,4)
pair(1,3)
pair(2,3)

fail...
*/