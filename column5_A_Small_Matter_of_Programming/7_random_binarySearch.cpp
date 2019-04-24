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
implement a randomized binary search algorithm
time it and compare with the ordinary one
*/

int binarySearch_randomized(const vector<int>& nums, const int& val)
{
    int low = 0, high = nums.size() - 1;
    while (low <= high)
    {
        int pos = low + rand() % (high - low + 1);

        if (nums[pos] == val)
        {
            return pos;
        }
        else if (nums[pos] < val)
        {
            low = pos + 1;
        }
        else
        {
            high = pos - 1;
        }
    }
    return -1;
}

int binarySearch_original(const vector<int>& nums, const int& val)
{
    int low = 0, high = nums.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;

        if (nums[mid] == val)
        {
            return mid;
        }
        else if (nums[mid] < val)
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

// check if vector is sorted in ascending order
bool isSorted(const vector<int>& nums)
{
    for (int i = 0; i < nums.size() - 1; ++i)
    {
        if (nums[i] > nums[i + 1])
        {
            return false;
        }
    }
    return true;
}

void test(const vector<int>& arr, const int& arr_size, const int& num_step)
{
    // test
    const int extra_search = 10; // search some out of bound values
    const int test_lower = -extra_search;
    const int test_upper = arr_size * num_step + extra_search;

    for (int i = test_lower; i < test_upper; ++i)
    {
        auto res = binarySearch_randomized(arr, i);

        if (i<arr[0] or i > arr.back())
        {
            assert(res == -1);
        }
        else if (i % num_step == 0)
        {
            assert(res == (i / num_step));
        }
        else if (i % num_step != 0)
        {
            assert(res == -1);
        }
    }
    cout << "passed " << test_upper - test_lower << " test cases\n";
}

void timeThem(int(bs1)(const vector<int>&, const int&),
              int(bs2)(const vector<int>&, const int&),
              const vector<int>& nums)
{
    int i_lower = nums[0] - 10;
    int i_upper = nums.back() + 10;

    long long total_t1 = 0, total_t2 = 0;

    for (int i = i_lower; i < i_upper; ++i)
    {
        auto t1 = chrono::high_resolution_clock::now();
        bs1(nums, i);
        auto t2 = chrono::high_resolution_clock::now() - t1;
        auto time_bf1 = chrono::duration_cast<chrono::nanoseconds>(t2).count();

        t1 = chrono::high_resolution_clock::now();
        bs2(nums, i);
        t2 = chrono::high_resolution_clock::now() - t1;
        auto time_bf2 = chrono::duration_cast<chrono::nanoseconds>(t2).count();

        total_t1 += time_bf1;
        total_t2 += time_bf2;
    }

    double avg1 = (double)total_t1/(i_upper-i_lower);
    double avg2 = (double)total_t2/(i_upper-i_lower);

    printf("bf1 avg search time: %f\nbf2 avg search time: %f\n", avg1, avg2);
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    // create array for searching
    const int arr_size = 100000;
    const int num_step = 7;
    assert(num_step != 0);
    vector<int> arr;
    for (int i = 0; i < arr_size; i += num_step)
    {
        arr.push_back(i);
    }
    isSorted(arr);

    test(arr, arr_size, num_step);

    timeThem(binarySearch_randomized, binarySearch_original, arr);

    return 0;
}
