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
If the original binary search was too easy for you,
try the variant that returns in p the position of the
first occurrence of t in the array x
(if there are multiple occurrences of t, the original
algorithm returns an arbitrary one). Your code should make
a logarithmic number of comparisons of array elements;
it is possible to do the job in log2 n such comparisons.
*/

// this solution is probably not the solution suggested in chapter 9
// since i haven't got there at this point
// *UPDATE: chapter 9 is completed, check them out
// if you're looking for something faster. :)
// (also for speed test and comparisons)

// my idea is to normally search for the element x
// but when x is found, we do an extra check:
// in english "is this the left most x in the array?"
// or in c++ "i == 0 or nums[i-1] != x"
// if not we continue searching on mid's left as if we've never
// seen the previous value, since it wasn't actually the target value

// Assume nums is sorted in ascending order
int BinarySearchFirstOccurence(const vector<int>& nums, const int& val) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        long long mid = (low + high) / 2;
        if (nums[mid] == val and ((mid == 0) or (nums[mid - 1] != val))) {
            return mid;
        }

        if (nums[mid] >= val) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

int main() {
    vector<int> nums{1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};
    for (int i = -1; i < 8; ++i) {
        cout << "n: " << i << " pos: " << BinarySearchFirstOccurence(nums, i)
             << '\n';
    }

    return 0;
}
