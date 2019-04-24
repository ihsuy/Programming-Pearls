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

// my O(n) solution that requires doing preprocess before search
// but uses O(n) space complexity
int mcs_linear(const vector<int>& nums)
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

// my optimal linear solution
// still O(n) but with smaller constant multiplier
// and O(1) space
// I think there's no better solution
// than this one, algorithmically speaking
// since this solution only look at every element once
// and thats the best conceivable time we can get
// this solution is about 10 time faster than mcs_linear
// the core idea is when ever we see a negative number
// we need to decide whether its worth it to include it
int mcs_linear2(const vector<int>& nums)
{
    int max_sum = 0;

    int runningSum = 0;

    for (int i = 0; i < nums.size(); ++i)
    {
        if (nums[i] < 0)
        {
            if (max_sum < runningSum)
            {
                max_sum = runningSum;
            }

            while (nums[i] < 0 and i < nums.size())
            {
                runningSum += nums[i];
                i++;
            }

            if (i == nums.size())
            {
                break;
            }

            if (runningSum < 0)
            {
                runningSum = 0;
            }
        }

        runningSum += nums[i];
    }

    return max(max_sum, runningSum);
}

// a simplified version of linear2
// this algorithm is suggested by the book
// and is esstentially identical to my second linear solution
// but a little bit slower
int mcs_linear3(const vector<int>& nums)
{
    int max_sum = 0;
    int runningSum = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        runningSum = max(0, runningSum);
        max_sum = max(max_sum, runningSum);
        runningSum += nums[i];
    }
    return (max_sum > runningSum) ? max_sum : runningSum;
}
// but linear3 uses significantly less variables than linears
// and much cleaner logic it should be faster
// so actually the source of slowness came from
// repeatedly calling the max function and assign the value
// so i modified it to
int mcs_linear3_1(const vector<int>& nums)
{
    int max_sum = 0;
    int runningSum = 0;
    for (int i = 0; i < nums.size(); ++i)
    {
        if (runningSum < 0)
        {
            runningSum = 0;
        }
        if (max_sum < runningSum)
        {
            max_sum = runningSum;
        }
        runningSum += nums[i];
    }
    return (max_sum > runningSum) ? max_sum : runningSum;
}
// this final solution successfully 2.2 x speeded up linear2 solution

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
    //inspect<vector<int>>(nums);

    const int nTest = 1000;
    unsigned long long accumulate_t3 = 0,
                       accumulate_t4 = 0,
                       accumulate_t5 = 0,
                       accumulate_t6 = 0;
    for (int i = 0; i < nTest; ++i)
    {
        //auto res1 = run(mcs_bruteForce, nums);
        //auto res2 = run(mcs_bruteForce2, nums);
        auto res3 = run(mcs_linear, nums);
        auto res4 = run(mcs_linear2, nums);
        auto res5 = run(mcs_linear3, nums);
        auto res6 = run(mcs_linear3_1, nums);

        accumulate_t3 += res3.first;
        accumulate_t4 += res4.first;
        accumulate_t5 += res5.first;
        accumulate_t6 += res6.first;
        // cout << "time spent: \n";
        // cout << res1.first << '\n';
        //cout << res2.first << '\n';
        // cout << res3.first << '\n';
        // cout << res4.first << '\n';
        //cout << res2.second << " " << res4.second << '\n';
        //assert(res1.second == res2.second);
        assert(res3.second == res3.second);
        assert(res3.second == res4.second);
        assert(res3.second == res5.second);
        assert(res3.second == res6.second);
    }

    cout << "successfully completed " << nTest << " test cases\n";
    cout.precision(10);
    cout << "avg time spent for linear1: " << (double)accumulate_t3 / nTest << '\n';
    cout << "avg time spent for linear2: " << (double)accumulate_t4 / nTest << '\n';
    cout << "avg time spent for linear3: " << (double)accumulate_t5 / nTest << '\n';
    cout << "avg time spent for linear3.5: " << (double)accumulate_t6 / nTest << '\n';
    return 0;
}
