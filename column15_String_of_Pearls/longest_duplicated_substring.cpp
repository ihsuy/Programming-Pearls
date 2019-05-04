#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <list>
#include <chrono>
#include <random>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <sstream>
#include <utility>
#include <bitset>
#include <fstream>
#include <string>

typedef long long ll;
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Given an input file of text, find the longest duplicated substring
of characters in it.

For instance, the longest repeated string in
    “Ask not what your country can do for you,
    but what you can do for your country”
is “ can do for you”, with “ your country” a close second place.
*/

// brute force method
// by comparing each possible substrings
pair<int, int> FindLDS1(const string& text)
{
    int text_len = text.length();

    int lhs = 0, rhs = 0, maxlen = 0;

    for (int p = 0; p < text_len; ++p)
    {
        for (int i = p + 1; i < text_len; ++i)
        {
            int len = 0, p0 = p, i0 = i;
            while (p0 < text_len and text[p0] == text[i0])
            {
                len++; p0++; i0++;
            }
            if (len > maxlen)
            {
                maxlen = len;
                lhs = p;
                rhs = p0;
            }
        }
    }
    return {lhs, rhs};
}

// optimal method uses index array
pair<int, int> FindLDS2(const char* text, const int& size)
{
    char const** index_arr = new char const*[size];
    for (int i = 0; i < size; ++i)
    {
        index_arr[i] = &text[i];
    }

    sort(index_arr, index_arr + size,
    [](char const * lhs, char const * rhs) { return strcmp(lhs, rhs) < 0;});

    int lhs = 0, rhs = 0, maxlen = 0;
    for (int i = 1; i < size; ++i)
    {
        int j = 0, len = 0;
        while (j < size and index_arr[i - 1][j] == index_arr[i][j])
        {
            j++; len++;
        }
        if (len > maxlen)
        {
            maxlen = len;
            lhs = (index_arr[i] - text);
            rhs = lhs + len;
        }
    }

    delete[] index_arr;
    return {lhs, rhs};
}

int main()
{
    const string text = "Ask not what your country can do for you, "
                        "but what you can do for your country";
    auto lds1 = FindLDS1(text);
    cout << "result 1: " << text.substr(lds1.first, lds1.second - lds1.first) << endl;

    auto lds2 = FindLDS2(text.c_str(), text.length());
    cout << "result 2: " << text.substr(lds2.first, lds2.second - lds2.first) << endl;

    return 0;
}
