#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>
#include <utility>

std::mt19937 gen(std::random_device{}());

template<typename T>
void selection_sort(std::vector<T>& a) {
    for (int i = 0; i < a.size() - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < a.size(); ++j) {
            if (a[min_index] > a[j]) {
                min_index = j;
            }
        }
        std::swap(a[i], a[min_index]);
    }
}

int main() 
{
    std::vector<int> a(100);
    std::iota(a.begin(), a.end(), 1);
    std::shuffle(a.begin(), a.end(), gen);
    selection_sort<int>(a);
    for (auto x : a) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
