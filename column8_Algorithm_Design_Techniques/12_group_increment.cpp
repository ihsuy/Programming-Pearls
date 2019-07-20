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
After the array x[0..n – 1] is initialized so that
every element is zero, n of the following operations
are performed

for i = [l, u]
    x[i] += v

where l, u and v are parameters of each operation
(l and u are integers satisfying 0≤l≤u<n, and v
is a real number). After the n operations,
the values of x[0..n – 1] are reported in order.
The method just sketched requires O(n2) time.
Can you find a faster algorithm?
*/

// this is an extremely useful function
// I've been using the O(n^2) algorithm to do this job
// without even considering the possibility of finding a O(n)
// algorithm for this, but now yeah, this is good

// assume ranges are within range of v and no int overflow
// all elements in v are initialized to 0
void GroupIncrement(vector<int>& v,
                    const vector<pair<int, pair<int, int>>>& ranges) {
    for (const auto& range_pair : ranges) {
        int val = range_pair.first;
        pair<int, int> range = range_pair.second;

        v[range.first] += val;
        if (range.second + 1 < v.size()) {
            v[range.second + 1] -= val;
        }
    }

    for (int i = 1; i < v.size(); ++i) {
        v[i] += v[i - 1];
    }
}

int main() {
    vector<pair<int, pair<int, int>>> ranges{
        {1, {0, 3}}, {2, {1, 4}}, {1, {0, 0}}, {3, {3, 7}}};
    vector<int> v{0, 0, 0, 0, 0, 0, 0, 0};

    GroupIncrement(v, ranges);
    inspect<vector<int>>(v);
    return 0;
}
