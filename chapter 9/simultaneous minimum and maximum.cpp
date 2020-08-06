#include<iostream>
#include<algorithm>
#include<vector>
#include<utility>

template<typename T>
std::pair<int, int> simultaneous(const std::vector<T>& A)
{
    T min, max;
    if(A.size() % 2 == 0)
    {
        max = std::max(A[0], A[1]);
        min = std::min(A[0], A[1]);
        for(auto i = 2; i < A.size(); i+=2)
        {
            if(max < std::max(A[i], A[i + 1]))
                max = std::max(A[i], A[i + 1]);
            if(min > std::min(A[i], A[i + 1]))
                min = std::min(A[i], A[i + 1]);
        }
    }
    else
    {
        max = A[0];
        min = A[0];
        for(auto i = 1; i < A.size(); i+=2)
        {
            if(max < std::max(A[i], A[i + 1]))
                max = std::max(A[i], A[i + 1]);
            if(min > std::min(A[i], A[i + 1]))
                min = std::min(A[i], A[i + 1]);
        }
    }
    return {min, max};
}

int main()
{
    std::vector<int> A {5,3,2,1,4};
    std::pair<int, int> max_min = simultaneous(A); 
    std::cout << max_min.first << ' ' << max_min.second;
}
