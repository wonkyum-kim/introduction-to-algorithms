#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

int merge(std::vector<int>& A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    std::vector<int> L;
    std::vector<int> R;

    for (int i = 0; i < n1; ++i) {
        L.push_back(A[p + i]);
    }
    for (int j = 0; j < n2; ++j) {
        R.push_back(A[q + j + 1]);
    }

    L.push_back(std::numeric_limits<int>::max());
    R.push_back(std::numeric_limits<int>::max());

    int i = 0;
    int j = 0;
    int inversions = 0;

    for (int k = p; k <= r; ++k) {
        if (L[i] <= R[j]) {
            A[k] = L[i++];
        } else {
            inversions += n1 - i;
            A[k] = R[j++];
        }
    }
    return inversions;
}

int count_inversions(std::vector<int>& A, int p, int r)
{
    if (p < r) {
        int q = (p + r) / 2;
        return count_inversions(A, p, q) + count_inversions(A, q + 1, r) + merge(A, p, q, r);
    }
    return 0;
}

int main()
{
    std::vector<int> v { 4, 2, 7, 1, 5, 6, 3 };
    std::cout << count_inversions(v, 0, v.size() - 1);
}
