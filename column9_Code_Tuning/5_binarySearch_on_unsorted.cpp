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
observe how binarysearch algorithms behave when applied on
unsorted arrays
*/

// conclusion:
// do binary search in a size 1000 jumble of integers
// doesn't cause any of the assertion to fail
// meaning it returns either -1 or the correct location
// in other words, it either can't find the target 
// or it locates the target correctly
// Since binary search always assume a sorted array as its input
// and repeatedly compare its target with its "mid-th" element 
// while halving its probing range.
// Here the mid-th element serves as a accurate "Compass" that tells 
// our binary search which direction to go
// However, in a unsorted array, the "Compass" points at arbitrary
// directions. But binary search won't stop halving its range and 
// finally stop when the range becomes empty, and then since it has been looking
// at arbitrary spots thats pointed by the "broken compass", the result will
// extremely likily to have nothing to do with the actual location of the target

// copy binarysearch functions from the file "BinarySearch_speedTest.cpp"
// in the same repository
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

int bs3(const vector<int>& nums, const int& target)
{
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
{   // create test vector
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int sz = 1000;
    const int n_lower = -sz / 10;
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
    assert(nums.size() == sz);

    shuffle(nums.begin(), nums.end(), default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count()));

    // test
    const char* schema = "res1:%d ; res2:%d ; res3:%d ; res4:%d\n";
    const int nTest = 200000;

    long long t1_sum = 0, t2_sum = 0, t3_sum = 0, t4_sum = 0;

    for (int i = 0; i < nTest; ++i)
    {
        int tar = rand() % sz;
        auto res1 = profiler<const vector<int>&>(bs1, nums, tar);
        auto res2 = profiler<const vector<int>&>(bs2, nums, tar);
        auto res3 = profiler<const vector<int>&>(bs3, nums, tar);
        auto res4 = profiler<const vector<int>&>(bs4, nums, tar);

        t1_sum += res1.first;
        t2_sum += res2.first;
        t3_sum += res3.first;
        t4_sum += res4.first;

        //printf(schema, res1.second , res2.second , res3.second , res4.second);
        if (res1.second != -1 or  res2.second != -1 or  res3.second != -1  or res4.second != -1)
        {   // extremely rarely we can enter this if statement
            // I got something like:
            // res1:499 ; res2:-1 ; res3:-1 ; res4:-1
            // after running this test for about one billion times
            printf(schema, res1.second , res2.second , res3.second , res4.second);
            break;
        }

        assert(res1.second < 0 or nums[res1.second] == tar);
        assert(res2.second < 0 or (nums[res2.second] == tar and nums[res2.second - 1] != tar));
        assert(res3.second < 0 or (nums[res3.second] == tar and nums[res3.second - 1] != tar));
        assert(res4.second < 0 or (nums[res4.second] == tar and nums[res4.second - 1] != tar));
    }

    cout << "t1 avg: " << t1_sum / nTest << '\n';
    cout << "t2 avg: " << t2_sum / nTest << '\n';
    cout << "t3 avg: " << t3_sum / nTest << '\n';
    cout << "t4 avg: " << t4_sum / nTest << '\n';

    return 0;
}
