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

// *NOTE THERE'S a hidden bug in this code below
// when searching for the last item in the array

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
    else if(nums[low+1] == target)
    {
        return low+1;
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

// assume nums.size == 1000
// this solution on the book hard-codes every thing
// this is definitely gonna be a little bit faster haha
int bs4(const vector<int>& nums, const int& target)
{
    int low = -1;
    if (nums[511] < target)
    {
        low = 488;
    }
    if (nums[low + 256] < target)
    {
        low += 256;
    }
    if (nums[low + 128] < target)
    {
        low += 128;
    }
    if (nums[low + 64] < target)
    {
        low += 64;
    }
    if (nums[low + 32] < target)
    {
        low += 32;
    }
    if (nums[low + 16] < target)
    {
        low += 16;
    }
    if (nums[low + 8] < target)
    {
        low += 8;
    }
    if (nums[low + 4] < target)
    {
        low += 4;
    }
    if (nums[low + 2] < target)
    {
        low += 2;
    }
    if (nums[low + 1] < target)
    {
        low += 1;
    }
    int pos = low + 1;
    if (pos > 1000 or nums[pos] != target)
    {
        return -1;
    }
    return pos;
}

// my first inplementation of binarysearch for first occurence back in column 4
// added here for speed comparisions
int bs5(const vector<int>& nums, const int& val)
{
    int low = 0, high = nums.size() - 1;

    while (low <= high)
    {
        long long mid = (low + high) / 2;
        if (nums[mid] == val and
                ((mid == 0) or (nums[mid - 1] != val)))
        {
            return mid;
        }

        if (nums[mid] >= val)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}

// empty template for new binary search implementations
// int bs6(const vector<int>& nums, const int& target)
// {
//     return 0;
// }
// int bs7(const vector<int>& nums, const int& target)
// {
//     return 0;
// }

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

/*
average result on searching in 1000 numbers for 500000 times :
bf1 avg time spent: 82 nanoseconds
bf2 avg time spent: 61 nanoseconds
bf3 avg time spent: 70 nanoseconds
bf4 avg time spent: 55 nanoseconds
bf5 avg time spent: 130 nanoseconds

average result on searching in 10,000,000 numbers for 500000 times :
(didn't test on bf4 since it only works for vector of size 1000)
bf1 avg: 228 nanoseconds
bf2 avg: 175 nanoseconds
bf3 avg: 190 nanoseconds
bf5 avg: 310 nanoseconds
*/

int main()
{   // create test vector
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int sz = 10000000;
    const int n_lower = -sz / 10;
    vector<int> nums;

    for (int i = 0, n = n_lower; i < sz; ++i)
    {
        if (rand() % 2)
        {
            n++;
        }
        if (rand() % 15)
        {   // occasionally introduce big gaps
            n += 10;
        }
        nums.push_back(n);
    }
    assert(nums.size() == sz);

    // test
    const int nTest = 500000;

    long long t1_sum = 0, t2_sum = 0, t3_sum = 0/*, t4_sum = 0*/, t5_sum = 0;

    for (int i = 0; i < nTest; ++i)
    {
        int tar = rand() % (sz + sz / 3) - sz / 5;
        auto res1 = profiler<const vector<int>&>(bs1, nums, tar);
        auto res2 = profiler<const vector<int>&>(bs2, nums, tar);
        auto res3 = profiler<const vector<int>&>(bs3, nums, tar);
        //auto res4 = profiler<const vector<int>&>(bs4, nums, tar);
        auto res5 = profiler<const vector<int>&>(bs5, nums, tar);

        t1_sum += res1.first;
        t2_sum += res2.first;
        t3_sum += res3.first;
        //t4_sum += res4.first;
        t5_sum += res5.first;

        assert(res1.second < 0 or nums[res1.second] == tar);
        assert(res2.second < 0 or (nums[res2.second] == tar and nums[res2.second - 1] != tar));
        assert(res3.second < 0 or (nums[res3.second] == tar and nums[res3.second - 1] != tar));
        //assert(res4.second < 0 or (nums[res4.second] == tar and nums[res4.second - 1] != tar));
        assert(res5.second < 0 or (nums[res5.second] == tar and nums[res5.second - 1] != tar));
        assert(res2.second == res3.second);
        //assert(res2.second == res4.second);
        assert(res2.second == res5.second);
    }

    cout << "t1 avg: " << t1_sum / nTest << '\n';
    cout << "t2 avg: " << t2_sum / nTest << '\n';
    cout << "t3 avg: " << t3_sum / nTest << '\n';
    //cout << "t4 avg: " << t4_sum / nTest << '\n';
    cout << "t5 avg: " << t5_sum / nTest << '\n';
    return 0;
}
