#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    string words[] = {"hello", "world", "map", "world", "example", "map", "example", "hello"};
    unordered_map<string, int> wordCount;

    for (string word : words)
        wordCount[word]++;

    for (auto it : wordCount)
        cout << it.first << " : " << it.second << endl;

    return 0;
}