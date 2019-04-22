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

template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
As laborious as our proof of binary search was,
it is still unfinished by some standards.
How would you prove that the program is free of run-time
errors (such as division by zero, word overflow,
variables out of declared range, or array indices
out of bounds)? If you have a background in discrete
mathematics, can you formalize the proof in a logical system?
*/

// do binary search for "val" in nums from left to right inclusively
// Assume nums is sorted
int BinarySearch(const vector<int>& nums, const int& val, const int& left, const int& right)
{
    assert(left >= 0 and left <= right);
    assert(right < nums.size());

    int low = left, high = right;

    while (low <= high)
    {
        long long mid = (low + high) / 2;

        if (nums[mid] == val)
        {
            return mid;
        }

        if (nums[mid] > val)
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

// division of zero:
// the only division happened is when computing mid = (low + high) / 2
// however, since the denominator is a constant 2,
// it can never become 0.

// word overflow:
// should happen when value of a
// variable becomes too large (or too small) to be properly
// contained in its original data type
// there're 3 locations where we modified value of variables
// (except initialization without operator overloading)

// 1. mid = (low + high)/2
// note that dividing two none negative integers by 2
// will yield value no smaller than 0
// since if (a+b)/2 < 0 then a+b < 0, therefore a < -b but this can
// never be true for 2 none negative numbers a and b as a+b must be >= 0
// so we aren't getting any data overflow here

// 2. high = mid-1
// in other words, will mid become INT_MIN so we can't substract 1 from it?
// NO, because mid is calculated using the formula in the previous bullet point
// mid can't be smaller than 0
// but be careful to not use unsigned integer for low, high and mid
// word overflow will happen i.e. if you search -1 in {0,1,2,3}

// 3. low = mid+1
// in other words, will mid become LLONG_MAX?
// if mid is LLONG_MAX, and we know mid is computed using the formula
// mid = (low + high)/2
// that would mean low + high is twice as large as LLONG_MAX
// and that necessarily implies
// either low or high have to be larger or equal to LLONG_MAX
// thats impossible, since low and high are of int type
// the program won't compile.

// 4. variables out of declared range
// we assert left to be no smaller than 0 
// and right to be no smaller than left
// thus right can't be smaller than 0

// we also assert right to be less than nums.size()
// then its true for any number no larger than right including left

// so our left and right are good before we begin
// as well as low and high
// in the process of search, the values thats changing are
// mid, low, high
// will these number exceeds [left, right] ?
// YES, it will happen only when we search for value thats 
// larger than nums.back() or smaller than nums.front(), 
// and low will become right+1 and and high will become left-1 respectively
// but will this cause undefined behaviour? 
// NO, since either case will cause low > high and immediently breaks the while
// loop and -1 is returned indicating no found which is correct

int main()
{
    vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10};
    cout << BinarySearch(nums, 5, 0, nums.size() - 1) << '\n';
    return 0;
}
