#include <iostream>
#include <stack>

int main()
{
    std::stack<int> S;
    S.push(4);
    std::cout << S.top() << '\n';
    S.push(1);
    std::cout << S.top() << '\n';
    S.push(3);
    std::cout << S.top() << '\n';
    S.pop();
    std::cout << S.top() << '\n';
    S.push(8);
    std::cout << S.top() << '\n';
    S.pop();
    std::cout << S.top() << '\n';
}
