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
Write and verify a recursive binary search program.
Which parts of the code and proof stay the same as
in the iterative version, and which parts change?
*/

// this program is almost identical to its iterative counter part
// except instead of using a while loop that breaks when value is found
// or low > high, we recursive calls the function until
// we find the value or low > high is true.
// the invariant for both algorithm is the fact that if val exists in nums,
// then val must be in the range [low, high].
// it then keep shrinking down this range by recursively
// calling itself with a smaller range until there's one or zero element
// in the range
int BinarySearch(const vector<int>& nums,
                 const int& val,
                 const int& low,
                 const int& high) {
    if (low > high) {
        return -1;
    }

    int mid = (low + high) / 2;

    assert(mid >= low and mid <= high);

    if (nums[mid] == val) {
        return mid;
    }

    if (nums[mid] < val) {
        return BinarySearch(nums, val, mid + 1, high);
    } else {
        return BinarySearch(nums, val, low, mid - 1);
    }
}

int main() {
    vector<int> nums{1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};
    for (int i = -1; i < 8; ++i) {
        cout << "n: " << i
             << " pos: " << BinarySearch(nums, i, 0, nums.size() - 1) << '\n';
    }

    return 0;
}
