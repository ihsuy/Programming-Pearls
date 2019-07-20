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
problem 10
Write a “fat pivot” partitioning function with the postcondition
*--------*--------*--------*
|   <t   |  ==t   |   >t   |
*--------*--------*--------*
How would you incorporate the function into a Quicksort program?
*/

// result after comparing with qsort2 and qsort3
/*
Algorithm: Fat Pivot Quicksort
took 81009 microseconds to sort 500000 numbers

Algorithm: Quicksort2
took 1249420 microseconds to sort 500000 numbers

Algorithm: Quicksort3
took 74182 microseconds to sort 500000 numbers

it wasn't as good as qsort3 but its did run faster compared to
optimized lumoto's method (qsort2)
*/

// My old version without optimization
// I left it here since perhaps its easier to understand

// pair<int, int> FatPivotPartition(vector<int>& nums,
//                                  const int& low,
//                                  const int& high)
// {
//     int pivot = nums[low];
//     int p_left = low, p_right = low;

//     for (int i = low + 1; i <= high; ++i)
//     {
//         if (nums[i] < pivot)
//         {
//             swap(nums[++p_left], nums[i]);
//             if (++p_right != p_left)
//             {
//                 swap(nums[p_right], nums[i]);
//             }
//         }
//         else if (nums[i] == pivot)
//         {
//             swap(nums[++p_right], nums[i]);
//         }
//     }
//     swap(nums[low], nums[p_left]);
//     return {p_left, p_right};
// }

pair<int, int> FatPivotPartition(vector<int>& nums,
                                 const int& low,
                                 const int& high) {
    swap(nums[low], nums[rand() % (high - low + 1) + low]);

    int pivot = nums[low];
    int p_left = low, p_right = low;

    for (int i = low + 1; i <= high; ++i) {
        if (nums[i] < pivot) {
            int temp = nums[++p_left];
            nums[p_left] = nums[i];
            if (++p_right != p_left) {
                nums[i] = nums[p_right];
                nums[p_right] = temp;
            } else {
                nums[i] = temp;
            }
        } else if (nums[i] == pivot) {
            int temp = nums[++p_right];
            nums[p_right] = nums[i];
            nums[i] = temp;
        }
    }
    swap(nums[low], nums[p_left]);
    return {p_left, p_right};
}

void QuickSort_FatPivot_helper(vector<int>& nums,
                               const int& low,
                               const int& high) {
    if (low >= high) {
        return;
    }
    // fat pivot is a pair of value pointing at the first and last element
    // of the fat pivot
    auto fat_pivot = FatPivotPartition(nums, low, high);

    QuickSort_FatPivot_helper(nums, low, fat_pivot.first - 1);
    QuickSort_FatPivot_helper(nums, fat_pivot.second + 1, high);
}

void QuickSort_FatPivot(vector<int>& nums) {
    QuickSort_FatPivot_helper(nums, 0, nums.size() - 1);
}

// algorithms introduced earlier in this chapter for speed comparision
// since the fat pivot quicksort is implemented based on these algorithms
// im trying to see if fat pivot did improve their speed
void qsort2_helper(vector<int>& nums, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = nums[low], m, i = m = high + 1;
    do {
        while (nums[--i] < pivot)
            ;
        swap(nums[--m], nums[i]);
    } while (i != low);

    qsort2_helper(nums, i, m - 1);
    qsort2_helper(nums, m + 1, high);
}
void qsort2(vector<int>& nums) {
    qsort2_helper(nums, 0, nums.size() - 1);
}

void qsort3_helper(vector<int>& nums, int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = nums[low];
    int l = low, h = high + 1;

    for (;;) {
        do {
            l++;
        } while (l <= h and nums[l] < pivot);

        do {
            h--;
        } while (nums[h] > pivot);
        // in the loop above,
        // since nums[low] == pivot,
        // it serves as a sentinel value
        // to prevent infinite loop

        if (l > h) {
            break;
        }

        swap(nums[l], nums[h]);
    }
    swap(nums[h], nums[low]);

    qsort3_helper(nums, low, h - 1);
    qsort3_helper(nums, h + 1, high);
}

void qsort3(vector<int>& nums) {
    qsort3_helper(nums, 0, nums.size() - 1);
}

const size_t rand_upper_bound = 1000;
vector<int> RandomVector(const size_t& n) {
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) {
        nums.push_back(rand() % rand_upper_bound);
    }
    return nums;
}

const string time_unit = "microseconds";
void profiler(void(SortAlgorithm)(vector<int>&),
              vector<int>& nums /*not sorted*/,
              const string& algorithm_name) {
    auto t1 = chrono::high_resolution_clock::now();
    SortAlgorithm(nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    long long t = chrono::duration_cast<chrono::microseconds>(t2).count();

    printf("Algorithm: %s\ntook %lld %s to sort %ld numbers\n",
           algorithm_name.c_str(), t, time_unit.c_str(), nums.size());
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    int arr_size = 500000;

    vector<int> nums(RandomVector(arr_size));
    vector<int> cp1(nums);
    vector<int> cp2(nums);
    vector<int> cp3(nums);

    profiler(QuickSort_FatPivot, nums, "Fat Pivot Quicksort");
    profiler(qsort2, cp1, "Quicksort2");
    profiler(qsort3, cp2, "Quicksort3");

    // check if correctly sorted
    sort(cp3.begin(), cp3.end());
    assert(nums == cp3);
    assert(cp1 == cp3);

    return 0;
}
