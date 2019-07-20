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
The input consists of two integers m and n,
with m < n. The output is a sorted list of m
random integers in the range 0..n – 1 in which
no integer occurs more than once.
*/

// implementations of the 3 method for generating the random number
// described in the problem statements
// explainations can be found in the book
// I did a little bit of number distribution measuring to test the
// correctness at the bottom.

vector<int> RandomSelection(int select, int remain) {
    assert(select <= remain);

    vector<int> res;
    res.reserve(select);

    int upper = remain;
    for (int i = 0; i < upper; ++i, --remain) {
        if (rand() % remain < select) {
            res.push_back(i);
            select--;
        }
    }

    return res;
}

vector<int> RandomSelection2(int select, int remain) {
    set<int> s;
    while (s.size() < select) {
        s.insert(rand() % remain);
    }
    return vector<int>{s.begin(), s.end()};
}

vector<int> RandomSelection3(int select, int remain) {
    int nums[remain];

    for (int i = 0; i < remain; ++i) {
        nums[i] = i;
    }

    for (int i = 0; i < select; ++i) {
        auto rand_index = i + rand() % (remain - i);
        auto tmp = nums[i];
        nums[i] = nums[rand_index];
        nums[rand_index] = tmp;
    }

    sort(nums, nums + select);
    return vector<int>{nums, nums + select};
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    // check random distribution
    int c1[20];
    memset(c1, 0, sizeof(int) * 20);
    for (int i = 0; i < 10000; ++i) {
        auto res = RandomSelection2(10, 20);
        for (auto& n : res) {
            c1[n]++;
        }
    }

    for (int i = 0; i < 20; ++i) {
        cout << c1[i] << ',';
    }
    cout << '\n';

    int c2[20];
    memset(c2, 0, sizeof(int) * 20);

    for (int i = 0; i < 10000; ++i) {
        auto res = RandomSelection3(10, 20);
        for (auto& n : res) {
            c2[n]++;
        }
    }

    for (int i = 0; i < 20; ++i) {
        cout << c2[i] << ',';
    }
    cout << '\n';

    // inspect<vector<int>>(res);
    return 0;
}
