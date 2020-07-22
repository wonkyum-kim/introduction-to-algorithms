#include <iostream>
#include <vector>

using namespace std;

// 두 벡터를 합친 벡터를 반환한다.
template <typename T>
vector<T> merge(const vector<T>& A, const vector<T>& B) {
    if (A.empty()) {
        return B;
    }
    else if (B.empty()) {
        return A;
    }

    vector<T> merged;
    merged.reserve(A.size() + B.size());

    size_t current_a = 0, current_b = 0;
    while (current_a < A.size() && current_b < B.size()) {
        if (A[current_a] <= B[current_b]) {
            merged.push_back(A[current_a++]);
            if (current_a == A.size()) {
                merged.insert(merged.end(), B.begin() + current_b, B.end());
                return merged;
            }
        }
        else if (A[current_a] > B[current_b]) {
            merged.push_back(B[current_b++]);
            if (current_b == B.size()) {
                merged.insert(merged.end(), A.begin() + current_a, A.end());
                return merged;
            }
        }
    }
    return merged;
}

// 위에서 만든 merge 함수를 사용한다.
template <typename T>
vector<T> merge_sort(const vector<T>& data) {
    if (data.size() <= 1) {
        return data;
    }
    size_t mid = data.size() / 2;
    const auto left = merge_sort(vector<T>(data.begin(), data.begin() + mid));
    const auto right = merge_sort(vector<T>(data.begin() + mid, data.end()));

    return merge(left, right);
}
int main() {
    auto merged = merge_sort(vector<int>{8, 5, 1, 4, 2, 3, 7, 6});

    for (int num : merged) {
        cout << num << " ";
    }
}

