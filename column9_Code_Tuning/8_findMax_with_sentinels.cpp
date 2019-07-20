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
How can sentinels be used in a program
to find the maximum element in an array?
*/

/*
result on size 100000 array
average after 100 tests

naive    maxElement1 average time: 365587 nanoseconds
sentinel maxElement2 average time: 203024
stl      maxElement3 average time: 1085066
*/

// naive method
// find the largest element in input
// assume input is non-empty
int maxElement1(vector<int>& nums) {
    int max_val = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }
    return max_val;
}

// sentinel method
// use the last value in the array to gaurantee
// the loop ends
// and reduce number of checking from 2 to 1 in the loop
int maxElement2(vector<int>& nums) {
    int n = nums.size();

    // nums.push_back(0);

    int max_val;
    for (int i = 0; i < n;) {
        nums[n] = max_val = nums[i];
        i++;
        while (nums[i] < max_val) {
            i++;
        }
    }

    // nums.pop_back();

    return max_val;
}

// stl max_element function wrapper
// the performance result is that
// this function is the slowest
// i assume the generic features (custom comp func)
// and the fact that this function actually return a iterator
// slows it down

int maxElement3(vector<int>& nums) {
    return *max_element(nums.begin(), nums.end());
}

pair<long long, int> profiler(int(maxele)(vector<int>&), vector<int> nums) {
    auto t1 = chrono::high_resolution_clock::now();
    auto res = maxele(nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int arr_size = 100000;
    vector<int> nums;
    for (int i = 0; i < arr_size; ++i) {
        nums.push_back(rand() % arr_size);
    }

    int jumble_factor = arr_size + 1;
    int nTest = 1000;

    ll t1_sum = 0, t2_sum = 0, t3_sum = 0;
    for (int i = 0; i < nTest; ++i) {
        int pos = rand() % arr_size;
        nums[pos] = jumble_factor;

        auto res1 = profiler(maxElement1, nums);
        auto res2 = profiler(maxElement2, nums);
        auto res3 = profiler(maxElement3, nums);

        assert(res1.second == jumble_factor);
        assert(res2.second == jumble_factor);
        assert(res3.second == jumble_factor);

        t1_sum += res1.first;
        t2_sum += res2.first;
        t3_sum += res3.first;
    }

    cout << "maxElement NaiveLoop average time: " << t1_sum / nTest << '\n';
    cout << "maxElement MaxAtEnd average time:  " << t2_sum / nTest << '\n';
    cout << "maxElement STL average time:       " << t3_sum / nTest << '\n';

    return 0;
}

// one interesting bonus personal discovery (not related to this book)
// say we have vector<int> vec;
// and we loop through it using a for loop
// for(int i = 0; i < vec.size(); ++i)
// is 40% slower than saving the size first : auto n = vec.size(); and do
// for(int i = 0; i < n; ++i)
// code below can be used to verify this fact
// of course assume that we are not going to
// modify the size of vector in the loop
// I once thought if vec is passed to a function as a constant reference
// then the compiler will optimize the process since the size of it won't change
// anyway but that wasn't the case

//
// pair<long long, int> profiler2(int(f)(const vector<int>&), const vector<int>&
// nums)
// {
//     auto t1 = chrono::high_resolution_clock::now();
//     auto res = f(nums);
//     auto t2 = chrono::high_resolution_clock::now() - t1;
//     auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
//     return {t, res};
// }

// int func1(const vector<int>& nums)
// {
//     int count = 0;
//     for (int i = 0; i < nums.size(); ++i)
//     {
//         count++;
//     }
//     return count;
// }

// int func2(const vector<int>& nums)
// {
//     int n = nums.size();
//     int count = 0;
//     for (int i = 0; i < n; ++i)
//     {
//         count++;
//     }
//     return count;
// }

// void test_forloop()
// {
//     auto res11 = profiler2(func1, nums);
//     auto res22 = profiler2(func2, nums);
//     cout << res11.first << "\n";
//     cout << res22.first << '\n';
//     assert(res11.second == res22.second);
// }
