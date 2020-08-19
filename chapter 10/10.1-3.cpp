#include <iostream>
#include <queue>

int main()
{
    std::queue<int> Q;
    Q.push(4);
    Q.push(1);
    Q.push(3);
    Q.pop();
    Q.push(8);
    Q.pop();
}
