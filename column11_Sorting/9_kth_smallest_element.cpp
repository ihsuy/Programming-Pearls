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
Write a program for finding the kth-smallest element
in the array x[0..n-1] in O(n) expected time.
Your algorithm may permute the elements of x.
*/

// naive approach
// sorts the array first
// O(nlogn)

// kth_smallest_naive1 assumes none unique array as its input
int kth_smallest_naive1(vector<int>& nums, const int& k)
{
    int nums_size = nums.size();
    if (k < 0 or nums_size == 0)
    {
        return -1;
    }

    sort(nums.begin(), nums.end());

    if (k == 1)
    {
        return nums[0];
    }

    for (int i = 1, count = 1; i < nums_size; ++i)
    {
        if (nums[i - 1] != nums[i])
        {
            if (++count == k)
            {
                return nums[i];
            }
        }
    }

    return -1;
}
// kth_smallest_naive1 assumes unique array as its input
int kth_smallest_naive2(vector<int>& nums, const int& k)
{
    int nums_size = nums.size();
    if (k - 1 < 0 or k - 1 >= nums_size or nums_size == 0)
    {
        return -1;
    }

    sort(nums.begin(), nums.end());

    return nums[k - 1];
}

// optimal solution
// this solution is based on the observation that we don't need to sort
// all N elements in the array to find its k-th smallest
// ideally we want to only put the first k element in their correct place
// We know that we can't do bette than this, because in order to know
// weither if an element is the kth smallest, we must have information about
// all elements that are smaller than it, otherwise that one element we don't
// know about can be set to a value thats smaller than it and thus invalidate
// our answer.
// To achieve our goal, we review what we've done in quicksort.

int kth_smallest_helper(const int& low, const int& high,
                        vector<int>& nums, const int& k)
{
    if (low > high)
    {
        return -1;
    }

    swap(nums[low], nums[(rand() % (high - low + 1)) + low]);

    int pivot = nums[low],
        i = high + 1, m = i;

    while (m != low)
    {
        while (nums[--m] < pivot);
        swap(nums[m], nums[--i]);
    }

    if (i == k)
    {
        return nums[i];
    }

    if (i < k)
    {
        return kth_smallest_helper(i + 1, high, nums, k);
    }
    else
    {
        return kth_smallest_helper(low, i - 1, nums, k);
    }
}

int kth_smallest(vector<int>& nums, const int& k)
{
    int nums_size = nums.size();
    if (k < 1 or k > nums_size or nums_size == 0)
    {
        return -1;
    }

    return kth_smallest_helper(0, nums_size - 1, nums, k-1);
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    vector<int> nums {5, 2, 6, 1, 7, 3, 9};
    for (int i = 0; i < 10; ++i)
    {
        cout << "naive1 : " << kth_smallest_naive1(nums, i) << endl;
        cout << "naive2 : " << kth_smallest_naive2(nums, i) << endl;
        cout << "optimal: " << kth_smallest(nums, i) << endl;
    }

    return 0;
}
