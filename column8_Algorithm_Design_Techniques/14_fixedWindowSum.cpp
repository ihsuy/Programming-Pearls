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
Given integers m and n and the real vector x[n],
find the integer i (0≤i < n – m) such that the sum
x[i] +...+ x[i + m] is nearest zero.
*/

int ABS(const double& n) {
    return n < 0 ? -n : n;
}

// instead of finding the subvector whos sums is closest to 0
// i implement a more generic version of it

// the function below find the first index of the subvector of nums
// whos sum is the closest to number "target"

// this is actually is much easier variation of the mcs problem in this question
// since the subvector size is already fixed, we only have to slide it thru
// and find that one sum which is closest to "target"
int fixedWindowSum(const vector<double>& nums,
                   const int& m,
                   const int& target = 0) {  // some error handling code are
                                             // expected here but I didnt write
    double window = 0.0;
    for (int i = 0; i < m; ++i) {  // get the initial window
        window += nums[i];
    }

    int res = 0, min_dist = ABS(window - target);

    for (int i = 0, j = m; j < nums.size();
         ++i, ++j) {  // slide while removing last number and adding next number
        window += nums[j] - nums[i];

        int dist = ABS(window - target);

        if (dist < min_dist) {
            res = i + 1;
            min_dist = dist;
        }
    }
    return res;
}

int main() {
    vector<double> nums{1, 1, 1, 2, 2, -2, 1, 0, 0};
    cout << fixedWindowSum(nums, 3) << '\n';

    return 0;
}
