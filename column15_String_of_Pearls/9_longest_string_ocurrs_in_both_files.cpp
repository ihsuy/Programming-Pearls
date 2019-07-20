#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Given two input texts, find the longest string that occurs in both.
*/

// My method first appen 2nd strings to the end of the 1st string
// then build index array as if the merged string is 1 single string
// however ignore the null character in middle,
// and everything else is then straightforward
char const* MergeStrings(const char* text1,
                         const int& len1,
                         const char* text2,
                         const int& len2) {
    char* merged_text = new char[len1 + len2 + 2];

    int i = 0;
    for (; i < len1; ++i) {
        merged_text[i] = text1[i];
    }
    merged_text[i++] = 0;
    for (int j = 0; i < len1 + len2 + 1; ++i, ++j) {
        merged_text[i] = text2[j];
    }
    merged_text[i] = 0;

    return merged_text;
}

char const** MakeMergedIndexArray(const char*& merged_text,
                                  const int& len1,
                                  const int& len2) {
    char const** idx_arr = new char const*[len1 + len2];
    int i = 0, j = 0;
    for (; i < len1; ++i, ++j) {
        idx_arr[i] = &merged_text[j];
    }
    for (++j; j < len1 + len2 + 1; ++i, ++j) {
        idx_arr[i] = &merged_text[j];
    }
    return idx_arr;
}

bool a_strcmp(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs) < 0;
}

int CommonLength(const char* c1, const char* c2) {
    int l = 0, r = 0, len = 0;
    while (c1[l++] == c2[r++]) {
        len++;
    }
    return len;
}

string LongestCommonSubstring(const string& s1, const string& s2) {
    int len1 = s1.length(), len2 = s2.length();
    auto merged_text = MergeStrings(s1.c_str(), len1, s2.c_str(), len2);
    auto idx_arr = MakeMergedIndexArray(merged_text, len1, len2);

    int idx_arr_len = len1 + len2;
    sort(idx_arr, idx_arr + idx_arr_len, a_strcmp);

    int max_len = 0, max_lhs = 0;
    for (int i = 0; i < idx_arr_len - 1; ++i) {
        bool test1 = (idx_arr[i] - merged_text) < len1,
             test2 = (idx_arr[i + 1] - merged_text) < len1;
        if (test1 ^ test2) {
            auto len = CommonLength(idx_arr[i], idx_arr[i + 1]);
            if (len > max_len) {
                max_len = len;
                max_lhs = i;
            }
        }
    }
    return s1.substr(
        min(idx_arr[max_lhs] - merged_text, idx_arr[max_lhs + 1] - merged_text),
        max_len);
}

int main() {
    string s1 = "banana and pinapple", s2 = "apple and pinabanana";
    auto res = LongestCommonSubstring(s1, s2);
    cout << "result1: " << res << '\n';

    s1 = "bananananab and pinapple";
    s2 = "apple and pinabananananab";
    res = LongestCommonSubstring(s1, s2);
    cout << "result2: " << res << '\n';

    return 0;
}
