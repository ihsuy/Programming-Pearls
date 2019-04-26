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
When n is a positive integer at most the size of the array,
this recursive C function returns the maximum value
in the array x[0..n – 1]:

float arrmax(int n)
{   if (n == 1)
        return x[0];
    else
        return max(x[n-l], arrmax(n-l));
}

When max is a function, it finds the maximum element of a vector
with n = 10,000 elements in a few milliseconds. When max is the C macro

#define max(a, b) ((a) > (b) ? (a) : (b))

this algorithm takes 6 seconds to find the maximum of
n = 27 elements and 12 seconds to find the maximum of
n = 28 elements. Give an input that tickles this dreadful
behavior, and analyze the run time mathematically.
*/

int call_counter = 0;

#define MAX_MACRO(a, b) (a<b?b:a)

double max_func(const double& d1, const double& d2)
{
    return d1 < d2 ? d2 : d1;
}

double arrmax1(const vector<double>& nums, const int& n)
{
    call_counter++;
    if (n == 1)
    {
        return nums[0];
    }
    return max_func(nums[n - 1], arrmax1(nums, n - 1));
}

double arrmax2(const vector<double>& nums, const int& n)
{
    call_counter++;
    if (n == 1)
    {
        return nums[0];
    }
    return MAX_MACRO(nums[n - 1], arrmax2(nums, n - 1));
}

double arrmax3(const vector<double>& nums, const int& n)
{
    call_counter++;
    if (n == 1)
    {
        return nums[0];
    }
    auto res = arrmax2(nums, n - 1);
    return MAX_MACRO(nums[n - 1], res);
}

pair<ll, double> profiler(double(arrmax)(const vector<double>&, const int&),
                          const vector<double>& nums, const int& n)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = arrmax(nums, n);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}

/*
result for array of size 15

arrmax1 result: 9
time spend: 513 nanoseconds
called 15 times

arrmax2 result: 9
time spend: 108640 nanoseconds
called 12543 times

arrmax3 result: 9
time spend: 53329 nanoseconds
called 6272 times

stop using nested function result as macro's parameter
halve the time it calls itself

arr size of 2 will result in MAX_MACRO behaves like this 
MAX_MACRO(a, MAX_MACRO(a, b) (a<b?b:a)) (a < MAX_MACRO(a, b) (a<b?b:a)?MAX_MACRO(a, b) (a<b?b:a):a)
while arrmax1 only calls itself twice to get the answer
arrmax2 and arrmax3 calls themselves 169 and 127 times respectively
*/

int main()
{
    const int arr_size = 2;
    vector<double> nums;
    for (int i = 0; i < arr_size; ++i)
    {
        nums.push_back((double)i * 0.7);
    }

    shuffle(nums.begin(), nums.end(),
            default_random_engine(chrono::high_resolution_clock::now()
                                  .time_since_epoch().count()));

    const char* schema = "arrmax%d result: %lf\ntime spend: %lld nanoseconds\ncalled %d times\n";

    auto res1 = profiler(arrmax1, nums, nums.size());
    printf(schema, 1, res1.second, res1.first, call_counter);

    call_counter = 0;
    auto res2 = profiler(arrmax2, nums, nums.size());
    printf(schema, 2, res2.second, res2.first, call_counter);

    call_counter = 0;
    auto res3 = profiler(arrmax3, nums, nums.size());
    printf(schema, 3, res3.second, res3.first, call_counter);

    return 0;
}
