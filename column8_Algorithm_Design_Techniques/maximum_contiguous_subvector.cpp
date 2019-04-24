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
The input is a vector x of n floating-point numbers;
the output is the maximum sum found in any contiguous
subvector of the input.
*/

// "mcs" used in the solutions below stands for maximum contiguous subvector

// the most naive implementation runs in O(n^3) time
// by checking every single subvector and calculate sum
// for each possibility
int mcs_bruteForce(const vector<int>& nums)
{
    int max_sum = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        for (int j = i; j < nums.size(); ++j)
        {
            int temp_sum = 0;
            for (int n = i; n <= j; ++n)
            {
                temp_sum += nums[n];
            }

            if (temp_sum > max_sum)
            {
                max_sum = temp_sum;
            }
        }
    }
    return max_sum;
}

// a better version of the previous algorithm
// by realize there's no need to re-calculate
// the sum from scratch for each possibility
// since we are looking at subvectors that are
// subset of each others
// and reduce the run time to O(n^2)
int mcs_bruteForce2(const vector<int>& nums)
{
    int max_sum = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        int temp_sum = 0;
        for (int j = i; j < nums.size(); ++j)
        {
            temp_sum += nums[j];

            if (temp_sum > max_sum)
            {
                max_sum = temp_sum;
            }
        }
    }
    return max_sum;
}

// my O(n) solution that do preprocess once before search
int mcs_runningSum(const vector<int>& nums)
{
    vector<int> runningSums;
    vector<int> offsets;

    int runningSum = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        runningSum += nums[i];
        runningSums.push_back(runningSum);
        offsets.push_back(nums[i] - runningSum);
    }

    int temp_max = INT_MIN;
    int max_sum = 0;

    for (int i = 0; i < runningSums.size(); ++i)
    {
        temp_max = max(temp_max, offsets[i]);
        max_sum = max(max_sum, runningSums[i] + temp_max);
    }
    return max_sum;
}

pair<unsigned long, unsigned long>
run(int(mcs)(const vector<int>&), const vector<int>& nums)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = mcs(nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}


int main()
{
    vector<int> nums3{31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
    vector<int> nums2{ -1, -1, -1000, 1};

    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int& sz = 2000;
    vector<int> nums;
    for (int i = 0; i < sz; ++i)
    {
        nums.push_back(rand() % sz - sz / 2);
    }

    auto res1 = run(mcs_bruteForce, nums);
    auto res2 = run(mcs_bruteForce2, nums);
    auto res3 = run(mcs_runningSum, nums);

    cout << "time spent: \n";
    cout << res1.first << '\n';
    cout << res2.first << '\n';
    cout << res3.first << '\n';

    assert(res1.second == res2.second and res1.second == res3.second);

    return 0;
}
