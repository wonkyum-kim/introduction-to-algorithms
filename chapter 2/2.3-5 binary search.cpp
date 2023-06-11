#include <iostream>
#include <vector>

bool binary_search(std::vector<int>& A, const int a, const int b, const int target)
{
    int left = a;
    int right = b;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (A[mid] == target) {
            return true;
        } else if (A[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

int main()
{
    std::vector<int> A { 1, 2, 3, 4, 5 };
    std::cout << binary_search(A, 0, A.size() - 1, 1) << '\n'
              << binary_search(A, 0, A.size() - 1, 6) << '\n';
}
