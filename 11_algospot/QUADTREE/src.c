//https://www.algospot.com/judge/problem/read/QUADTREE
#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>

using namespace std;
const int MAX_LENGTH = (1000 + 10);

string reverse(string::iterator& it)
{
    char head = *it;
    it++;
    if ('b' == head || 'w' == head)
    {
        return string(1, head);
    }

    string upperLeft  = reverse(it);
    string upperRight = reverse(it);
    string lowerLeft  = reverse(it);
    string lowerRight = reverse(it);

    return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main()
{
    freopen("input.txt", "r", stdin);
    int C;
    scanf("%d", &C);
    for (int i = 0; i < C; i++)
    {
        string str;
        cin >> str;
        string::iterator iter = str.begin();
        cout << reverse(iter) << '\n';
    }
    return 0;
}