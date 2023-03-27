#include <iostream>
#include <vector>

using namespace std;

void print(vector<int>&& v)
{
    for (auto i : v)
        cout << i << " ";
    cout << endl;
}

int main()
{
    vector<int> v1{1, 2, 3};
    print(move(v1)); // 将v1作为右值引用传递给print函数
    return 0;
}