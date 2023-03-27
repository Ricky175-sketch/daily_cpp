#include <iostream>
#include <vector>
using namespace std;

void printVector(vector<int>& v) // 左值引用参数
{
    for (auto i : v)
        cout << i << " ";

    cout << endl;
}

void printVector(vector<int>&& v) // 右值引用参数
{
    for (auto i : v)
        cout << i << " ";

    cout << endl;
}

int main()
{
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {6, 7, 8, 9, 10};

    // 左值引用参数
    printVector(v1);

    // 右值引用参数
    printVector(move(v2));

    return 0;
}