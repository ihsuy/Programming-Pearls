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
Suppose that we wished to find the subvector
with the sum closest to zero rather than
that with maximum sum. What is the most efficient
algorithm you can design for this task? What algorithm
design techniques are applicable?
What if we wished to find the subvector with the sum
closest to a given real number t?
*/

// find the subvector with the sum closest to zero
pair<int, int> SubvectorClosestToZero(const vector<int>& nums)
{
    vector<pair<int, int>> runningSums{{0, -1}};
    for (int i = 1; i < nums.size(); ++i)
    {
        runningSums.push_back({runningSums[i - 1].first + nums[i - 1], i-1});
    }
    sort(runningSums.begin(), runningSums.end());

    pair<int, int> result;
    int min_val = INT_MAX;
    for (int i = 1; i < runningSums.size(); ++i)
    {
        int temp = runningSums[i].first - runningSums[i - 1].first;
        if (temp < min_val)
        {
            min_val = temp;
            auto left = min(runningSums[i - 1].second, runningSums[i].second);
            auto right = max(runningSums[i - 1].second, runningSums[i].second);
            result = {left+1, right};
        }
    }
    return result;
}


// find the subvector with the sum closest to a given real number N
int ABS(const int& n)
{
    return n<0?-n:n;
}

pair<int, int> SubvectorClosestTo(const int& N, const vector<int>& nums)
{
    vector<pair<int, int>> runningSums{{0, -1}};
    for (int i = 1; i < nums.size(); ++i)
    {
        runningSums.push_back({runningSums[i - 1].first + nums[i - 1], i-1});
    }
    sort(runningSums.begin(), runningSums.end());

    pair<int, int> result;
    int min_val = INT_MAX;

    for (int i = 1; i < runningSums.size(); ++i)
    {
        int temp = ABS(runningSums[i].first - runningSums[i - 1].first - N);
        if (temp < min_val)
        {
            min_val = temp;
            auto left = min(runningSums[i - 1].second, runningSums[i].second);
            auto right = max(runningSums[i - 1].second, runningSums[i].second);
            result = {left+1, right};
        }
    }
    return result;
}

int main()
{
    vector<int> nums{7, 16, -32, 14, -65, 23, -1, -9};
    auto res1 = SubvectorClosestToZero(nums);
    printf("SubvectorClosestToZero: [%d, %d]\n", res1.first, res1.second);

    int N = 5;
    auto res2 = SubvectorClosestTo(N, nums);
    printf("SubvectorClosestTo%d: [%d, %d]\n", N, res2.first, res2.second);
    return 0;
}
