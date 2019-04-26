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
Surgeries on binary search and test their speed
*/

// find any position of the occurences of target in nums
// the ordinary binary search
int bs1(const vector<int>& nums, const int& target)
{
    int low = 0, high = nums.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (nums[mid] == target)
        {
            return mid;
        }

        if (nums[mid] < target)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

// My version of finding the FIRST OCCURENCE of target in nums
// use the fact that the search range is halved in every step
// and since we know low and range size, we directly calculate mid 
// without having to hold "high". also do not terminate when nums[mid] is target
// but include that item in the range and continue
int bs2(const vector<int>& nums, const int& target)
{
    int low = 0;
    for (int i = (nums.size() - 1) >> 1; i > 0; i >>= 1)
    {
        if (nums[low + i] < target)
        {
            low = low + i + 1;
        }
    }

    if (low < nums.size() and nums[low] == target)
    {
        return low;
    }

    return -1;
}

// book's solution: first version of finding the
// first occurence of target in nums
int bs3(const vector<int>& nums, const int& target)
{
    /*  l = -1; u = n
        while l+1 != u
            // invariant: x[l] < t && x[u] >= t && 1 < u
            m = (l + u) / 2
            if x[m] < t
                l = m
            else
                u = m
        assert l+1 = u && x[l] < t && x[u] >= t
        p = u
        if p >= n || x[p] != t
                p = -1
    */
    int low = -1, high = nums.size();
    while (low + 1 != high)
    {
        int mid = (low + high) >> 1;
        if (nums[mid] < target)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    int pos = high;
    if (pos >= nums.size() or nums[pos] != target)
    {
        return -1;
    }
    return pos;
}

int bs4(const vector<int>& nums, const int& target)
{
    return 0;
}

template<typename container_type>
pair<long long, int> profiler(int(bs)(container_type, const int&),
                              container_type nums, const int& target)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = bs(nums, target);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    // cout << "result: " << res << '\n';
    // cout << "func time: " << t << " nanoseconds\n";
    return {t, res};
}


int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int sz = 1000001;
    const int n_lower = -5000;
    vector<int> nums;

    for (int i = 0, n = n_lower; i < sz; ++i)
    {
        if (rand() % 2)
        {
            n++;
        }
        if (rand() % 4)
        {   // occasionally introduce big gaps
            n += 1000;
        }
        nums.push_back(n);
    }

    const int nTest = 150000;

    long long t1_sum = 0, t2_sum = 0, t3_sum = 0;

    for (int i = 0; i < nTest; ++i)
    {
        int tar = rand() % (sz + sz / 3) - sz / 5;
        auto res1 = profiler<const vector<int>&>(bs1, nums, tar);
        auto res2 = profiler<const vector<int>&>(bs2, nums, tar);
        auto res3 = profiler<const vector<int>&>(bs3, nums, tar);
        t1_sum += res1.first;
        t2_sum += res2.first;
        t3_sum += res3.first;
        assert(res1.second < 0 or nums[res1.second] == tar);
        assert(res2.second < 0 or (nums[res2.second] == tar and nums[res2.second - 1] != tar));
        assert(res3.second < 0 or (nums[res3.second] == tar and nums[res3.second - 1] != tar));
    }

    cout << "t1 avg: " << t1_sum / nTest << '\n';
    cout << "t2 avg: " << t2_sum / nTest << '\n';
    cout << "t3 avg: " << t3_sum / nTest << '\n';
    return 0;
}
