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
The implementation of several sorting algorithms decribed in the book.
*/

void InsertionSort1(vector<int>& nums)
{
    auto len = nums.size();
    for (int i = 0, j = 0; i < len; ++i)
    {
        for (j = i; j > 0 and nums[j - 1] > nums[j]; --j)
        {
            swap(nums[j - 1], nums[j]);
        }
    }
}
void InsertionSort2(vector<int>& nums)
{
    auto len = nums.size();
    for (int i = 0, j = 0; i < len; ++i)
    {
        for (j = i; j > 0 and nums[j - 1] > nums[j]; --j)
        {
            auto tmp = nums[j];
            nums[j] = nums[j - 1];
            nums[j - 1] = tmp;
        }
    }
}

void InsertionSort3(vector<int>& nums)
{
    auto len = nums.size();
    for (int i = 0, j = 0; i < len; ++i)
    {
        auto tmp = nums[i];
        for (j = i; j > 0 and nums[j - 1] > tmp; --j)
        {
            nums[j] = nums[j - 1];
        }
        nums[j] = tmp;
    }
}

void qsort1_helper(vector<int>& nums, int low, int high)
{
    if (low >= high)
    {   // try to sort empty array
        return;
    }
    // always use the leftmost entry as pivot
    auto pivot = nums[low];

    // reserve low for later use
    // create l a index that alway point at the end of 
    // the "left part"
    int l = low;
    // partitions nums[low, high] with respect to the pivot
    for (int i = low + 1; i <= high; ++i)
    {
        if (nums[i] < pivot)
        {   // if found an entry < pivot
            // we know it must be placed 
            // after l, and we move l ahead
            swap(nums[++l], nums[i]);
        }
    }
    // move pivot to its correct position
    swap(nums[l], nums[low]);
    // recursively partition left and right
    qsort1_helper(nums, low, l - 1);
    qsort1_helper(nums, l + 1, high);
}
void qsort1(vector<int>& nums)
{
    qsort1_helper(nums, 0, nums.size() - 1);
}


// test and timing

bool isSorted(const vector<int>& nums)
{
    auto len = nums.size();
    for(int i = 1; i < len; ++i)
    {
        if(nums[i-1]>nums[i])
        {
            return false;
        }
    }
    return true;
}

const string time_unit = "microseconds";
void profiler(void(SortAlgorithm)(vector<int>&), vector<int> nums/*not sorted*/,
              const string& algorithm_name)
{
    auto t1 = chrono::high_resolution_clock::now();
    SortAlgorithm(nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    long long t = chrono::duration_cast<chrono::microseconds>(t2).count();

    printf("Algorithm: %s\ntook %lld %s to sort %ld numbers\n",
           algorithm_name.c_str(), t, time_unit.c_str(), nums.size());

    cout << (isSorted(nums)?"Correctly sorted\n":"Something is wrong\n") << '\n';
}

const size_t rand_upper_bound = 1000;
vector<int> RandomVector(const size_t& n)
{
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        nums.push_back(rand() % rand_upper_bound);
    }
    return nums;
}


int main()
{   srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    auto nums = RandomVector(2000);
    profiler(InsertionSort1, nums, "InsertionSort1");
    profiler(InsertionSort2, nums, "InsertionSort2");
    profiler(InsertionSort3, nums, "InsertionSort3");
    profiler(qsort1, nums, "qsort1");
    return 0;
}
