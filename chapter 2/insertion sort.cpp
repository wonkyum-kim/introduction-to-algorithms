#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

std::mt19937 gen(std::random_device{}());

template<typename T>
void insertion_sort(std::vector<T>& a) {
    for (int j = 1; j < a.size(); j++) {
        T key = a[j];
        int i = j - 1;
        while (i >= 0 && a[i] > key) {
            a[i + 1] = a[i];
            i--;
        }
        a[i + 1] = key;
    }
}

int main()
{
    std::vector<int> a(100);
    std::iota(a.begin(), a.end(), 1);
    std::shuffle(a.begin(), a.end(), gen);
    insertion_sort(a);
    for (auto x : a) {
        std::cout << x << ' ';
    }
}
