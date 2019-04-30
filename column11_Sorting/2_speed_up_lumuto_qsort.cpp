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
Speed up Lomuto’s partitioning scheme by using x[l] as a sentinel.
Show how this scheme allows you to remove the swap after the loop.
*/

// QuickSort that uses Lomuto's partitioning scheme:
void qsort1_helper(vector<int>& nums, int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int l = low;
    int pivot = nums[low];

    for (int h = low + 1; h <= high; ++h)
    {
        if (nums[h] < pivot)
        {
            swap(nums[++l], nums[h]);
        }
    }

    swap(nums[l], nums[low]);

    qsort1_helper(nums, low, l - 1);
    qsort1_helper(nums, l + 1, high);
}
void qsort1(vector<int>& nums)
{
    qsort1_helper(nums, 0, nums.size() - 1);
}

// the code mentioned in the back of the book
// which does similar job that lomuto's algorithm does
// but uses sentinel value techniques to make code more succinct
// and reduce loop condition
// I'll call this method the "backward method"
void qsort2_helper(vector<int>& nums, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pivot = nums[low], m, i = m = high + 1;
    do
    {
        while (nums[--i] < pivot);
        swap(nums[--m], nums[i]);
    }
    while (i != low);

    qsort2_helper(nums, i, m - 1);
    qsort2_helper(nums, m + 1, high);
}
void qsort2(vector<int>& nums)
{
    qsort2_helper(nums, 0, nums.size() - 1);
}

// my version of the "backward method" which doesn't use
// do-while loop
// I implemented this method myself after i got the hit "from backward"
// and ended up producing an almost identical algorithm as suggested in
// the solution section of the book.
// However I found my implementation more straight forward 
// its maybe just my personal opinion
void qsort21_helper(vector<int>& nums, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int i = high, pivot = nums[low];

    for (int j = high+1; j != low;)
    {
        while (nums[--j] < pivot);
        swap(nums[j], nums[i--]);
    }

    qsort21_helper(nums, low, i);
    qsort21_helper(nums, i + 2, high);
}
void qsort21(vector<int>& nums)
{
    qsort21_helper(nums, 0, nums.size() - 1);
}

int main()
{
    vector<int> nums {9, 5, 1, 1, 0, 9, 0, 9, 3, 2, 5, 0};
    qsort2(nums);
    inspect<vector<int>>(nums);
    // srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    // for (int i = 0; i < 1000; ++i)
    // {
    //     vector<int> nums;
    //     for (int j = 0; j < 100; ++j)
    //     {
    //         nums.push_back(rand() % 100);
    //     }
    //     vector<int> cp = nums;
    //     sort(cp.begin(), cp.end());
    //     qsort2(nums);
    //     assert(cp == nums);
    // }

    return 0;
}
