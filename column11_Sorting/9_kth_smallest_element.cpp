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
// The essence of quicksort is concentrated in the "partition" process
// which only costs O(N) time but allows us to put 1 element in its correct 
// position and every other elements in their correct range.

// How will this help us find the kth smallest element?
// Let's just apply quicksort for once and see.
// after first partition, we have and element say n, thats placed at
// the r-th position. 
// What can we say about the result array now?
// we know that every element that is smaller than n is on its left 
// and vise versa. which means, if the k is less than r then the k-th smallest
// element must be on n's left and vise versa.
// Therefore we can just ignore all elements on n's right from now on, and 
// do another partition on the left of n(exclusive) until we place an element
// in the k-th position of the array. we know that we've found our result.

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

    return kth_smallest_helper(0, nums_size - 1, nums, k - 1);
}


// a more versatile version of the algorithm above
int kth_smallest2_helper(const int& low, const int& high,
                         vector<int>& nums, const int& k)
{
    if (low >= high)
    {
        return -1;
    }

    swap(nums[low], nums[(rand() % (high - low + 1)) + low]);

    int pivot = nums[low],
        l = low + 1, h = high + 1;

    for (;;)
    {
        while (nums[--h] > pivot);
        while (nums[l++] < pivot);
        if (l > h)
        {
            break;
        }
        swap(nums[l], nums[h]);
    }
    swap(nums[low], nums[h]);

    if (h == k)
    {
        return nums[h];
    }

    if (h < k)
    {
        return kth_smallest2_helper(h + 1, high, nums, k);
    }
    else
    {
        return kth_smallest2_helper(low, h - 1, nums, k);
    }
}

int kth_smallest2(vector<int>& nums, const int& k)
{
    int nums_size = nums.size();
    if (k < 1 or k > nums_size or nums_size == 0)
    {
        return -1;
    }

    return kth_smallest_helper(0, nums_size - 1, nums, k - 1);
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int arr_size = 1000;
    vector<int> nums;
    nums.reserve(arr_size);
    for (int i = 0; i < arr_size; ++i)
    {
        nums.push_back(i);
    }
    shuffle(nums.begin(), nums.end(), default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count()));

    for (int i = -10; i < arr_size+10; ++i)
    {
        //cout << "naive1  : " << kth_smallest_naive1(nums, i) << endl;
        auto res2 = kth_smallest_naive2(nums, i);
        auto res3 =  kth_smallest(nums, i);
        auto res4 =  kth_smallest(nums, i);
        assert(res2 == res3);
        assert(res2 == res4);
    }

    return 0;
}
