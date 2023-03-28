#include <iostream>
using namespace std;

void bar(int& x)
{
    cout << "bar&" << endl;
}

void bar(int&& x)
{
    cout << "bar&&" << endl;
}

template<typename T>
void foo(T&& t)
{
    bar(forward<T>(t));
}

int main()
{
    int a = 10;
    foo(a);
    foo(10);

    return 0;
}