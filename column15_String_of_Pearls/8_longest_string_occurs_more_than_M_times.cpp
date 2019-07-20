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
How would you modify the program for finding duplicated strings
to find the longest string that occurs more than M times?
*/

char const** MakeIndexArray(const char* s, const int& slen) {
    char const** index_array = new char const*[slen];
    for (int i = 0; i < slen; ++i) {
        index_array[i] = &s[i];
    }
    return index_array;
}

bool a_strcmp(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs) < 0;
}

// Find the longest duplicated string that ocurs more than M times
// This algorithm utilizes the fact that if a sub string repeated M times
// they must consecutively appear at the beginning of M entries in a sorted
// index array
pair<int, int> LongestDuplicates(const char*& s,
                                 const int& slen,
                                 const int& M) {
    auto idxarr = MakeIndexArray(s, slen);
    sort(idxarr, idxarr + slen, a_strcmp);
    const char *max_lhs = s, *max_rhs = s;
    for (int i = 0, max_len = 0; i < slen - M; ++i) {
        int l = 0, r = 0, len = 0, j = i + M;
        while (idxarr[i][l] == idxarr[j][r]) {
            len++;
            r++;
            l++;
        }
        if (len > max_len) {
            max_len = len;
            max_lhs = idxarr[i];
            max_rhs = max_lhs + len;
        }
    }
    return {max_lhs - s, max_rhs - s};
}

string ChToStr(const char* s, const int& begin_index, const int& end_index) {
    assert(begin_index >= 0 and end_index >= 0 and (begin_index <= end_index));

    return string(s + begin_index, s + end_index);
}

int main() {
    const char* s = "banana is a banana";
    const int& slen = strlen(s);
    auto res = LongestDuplicates(s, slen, 3);
    cout << ChToStr(s, res.first, res.second) << '\n';

    return 0;
}
