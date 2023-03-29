#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main()
{
    vector<string> strs = {"hello", "world", "hello", "world", "set", "unordered_set"};
    unordered_set<string> s;
    for (auto &str : strs)
    {
        if (s.count(str))
            cout << "Found duplicate: " << str << endl;
        else
            s.insert(str);
    }
    return 0;
}