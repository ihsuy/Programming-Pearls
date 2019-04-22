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
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

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
int BinarySearch(const vector<int>& nums, const int& val,
                 const int& low, const int& high)
{   
    if (low > high)
    {
        return -1;
    }

    int mid = (low + high) / 2;

    assert(mid >= low and mid <= high);

    if (nums[mid] == val)
    {
        return mid;
    }

    if (nums[mid] < val)
    {
        return BinarySearch(nums, val, mid + 1, high);
    }
    else
    {
        return BinarySearch(nums, val, low, mid - 1);
    }
}

int main()
{
    vector<int> nums {1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 5};
    for (int i = -1; i < 8; ++i)
    {
        cout << "n: " << i
             << " pos: " << BinarySearch(nums, i, 0, nums.size()-1) << '\n';
    }

    return 0;
}
