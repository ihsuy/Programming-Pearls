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
The implementation of several sorting algorithms decribed in the book.
*/

// simplest implementation that keeps the invariant
// "every element in the range [0~i) is sorted"
// and examine and insert next number
// in its correct position on its lhs by repeated swapping
void InsertionSort1(vector<int>& nums) {
    auto len = nums.size();
    for (int i = 1, j = 1; i < len; ++i) {
        for (j = i; j > 0 and nums[j - 1] > nums[j]; --j) {
            swap(nums[j - 1], nums[j]);
        }
    }
}

// almost identical to InsertionSort1 but expanded swap function
// to avoid system function overhead
void InsertionSort2(vector<int>& nums) {
    auto len = nums.size();
    for (int i = 1, j = 1; i < len; ++i) {
        for (j = i; j > 0 and nums[j - 1] > nums[j]; --j) {
            auto tmp = nums[j];
            nums[j] = nums[j - 1];
            nums[j - 1] = tmp;
        }
    }
}

// InsertionSort3 cleverly notice that the swap happens
// consecutively between contiguous elements
// and there's no need to "swap everything"
// but just save nums[j] and "shift" every elements that
// are supposed to be swapped to the right by 1
// then put saved nums[j] in its correct position
void InsertionSort3(vector<int>& nums) {
    auto len = nums.size();
    for (int i = 1, j = 1; i < len; ++i) {
        auto tmp = nums[i];
        for (j = i; j > 0 and nums[j - 1] > tmp; --j) {
            nums[j] = nums[j - 1];
        }
        nums[j] = tmp;
    }
}

void qsort1_helper(vector<int>& nums, int low, int high) {
    if (low >= high) {  // try to sort empty array
        return;
    }
    // always use the leftmost entry as pivot
    auto pivot = nums[low];

    // reserve low for later use
    // create l a index that alway point at the end of
    // the "left part"
    int l = low;
    // partitions nums[low, high] with respect to the pivot
    for (int i = low + 1; i <= high; ++i) {
        if (nums[i] < pivot) {  // if found an entry < pivot
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
void qsort1(vector<int>& nums) {
    qsort1_helper(nums, 0, nums.size() - 1);
}

// for qsort2, check out my solution to problem 2:
// "2_speed_up_lumuto_qsort.cpp"

// qsort3 is motivated by the a corner case input
// namely, when the input vector is made of identical elements.
// this will result in excessively long sorting time for qsort1
// since it must move its left index one by one while checking
// everything on its left and found that there's nothing to be
// sorted.
// qsort3 tackles the problem from two ends of the array
// uses a main loop and 2 subloops
// subloop 1 will move left index to the right first and
// continue as long as its pointing at elements that are strickly
// smaller than pivot, and the subloop 2 does the opposite job
// from right to left. The 2 subloops will stop at the elements
// that are supposed to be swapped.
// the main loop breaks when the left and right
// index examined every number in the array.
// we move pivot to its correct position and excluded it from the range
// the partition procedure needs to
// be carried on in further recursion until
// every element is in its right position
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

// qsort4 made 3 optimizations based on qsort3
// 1. Randomize pivot choice by swapping the leftmost
// entry with another randomly selected entry. This approach
// allows qsort4 to overcome "worst cases runtime" when sorting a
// already sorted array.
// 2. Introduce the idea "cut off" which allows us to
// sort the array while leaving small intervals unsorted
// and use the sorting algorithms that are efficient at
// sorting "nearly sorted" array to complete the job
// 3. Expand the swap function in main loop to reduce function calls
// and avoid unnecessary overhead by complex APIs offered by
// system swap function. Expanding system swaps outside the loop
// wasn't a must since they are called fewer times.
const int cut_off = 10;
void qsort4_helper(vector<int>& nums, int low, int high) {
    int hl_diff = high - low;
    if (hl_diff <= cut_off) {
        return;
    }
    // random pivot
    swap(nums[low], nums[rand() % (hl_diff + 1) + low]);
    int pivot = nums[low];

    int l = low, h = high + 1;
    for (;;) {
        do {
            l++;
        } while (l <= high and nums[l] < pivot);

        do {
            h--;
        } while (nums[h] > pivot);

        if (l > h) {
            break;
        }
        // hand made swap
        auto tmp = nums[l];
        nums[l] = nums[h];
        nums[h] = tmp;
    }
    swap(nums[h], nums[low]);

    qsort4_helper(nums, low, h - 1);
    qsort4_helper(nums, h + 1, high);
}

void qsort4(vector<int>& nums) {
    qsort4_helper(nums, 0, nums.size() - 1);
    InsertionSort3(nums);
}

// Testing and timing
bool isSorted(const vector<int>& nums) {
    auto len = nums.size();
    for (int i = 1; i < len; ++i) {
        if (nums[i - 1] > nums[i]) {
            return false;
        }
    }
    return true;
}

const string time_unit = "microseconds";
void profiler(void(SortAlgorithm)(vector<int>&),
              vector<int> nums /*not sorted*/,
              const string& algorithm_name) {
    auto t1 = chrono::high_resolution_clock::now();
    SortAlgorithm(nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    long long t = chrono::duration_cast<chrono::microseconds>(t2).count();

    printf("Algorithm: %s\ntook %lld %s to sort %ld numbers\n",
           algorithm_name.c_str(), t, time_unit.c_str(), nums.size());

    cout << (isSorted(nums) ? "Correctly sorted\n" : "Something is wrong\n")
         << '\n';
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

// create a vector of size n where every element has identical value "val"
vector<int> TrivialVector(const size_t& n, const int& val = 1) {
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) {
        nums.push_back(val);
    }
    return nums;
}

// create a sorted vector of size n
vector<int> SortedVector(const size_t& n) {
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) {
        nums.push_back(i);
    }
    return nums;
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int vec_size = 10000;

    cout << ">>>Testing on vector of random elements<<<\n";
    auto nums = RandomVector(vec_size);
    profiler(InsertionSort1, nums, "InsertionSort1");
    profiler(InsertionSort2, nums, "InsertionSort2");
    profiler(InsertionSort3, nums, "InsertionSort3");
    profiler(qsort1, nums, "qsort1");
    profiler(qsort3, nums, "qsort3");
    profiler(qsort4, nums, "qsort4");

    cout << ">>>Testing on vector of identical elements<<<\n";
    auto nums_t = TrivialVector(vec_size);
    profiler(InsertionSort1, nums_t, "InsertionSort1");
    profiler(InsertionSort2, nums_t, "InsertionSort2");
    profiler(InsertionSort3, nums_t, "InsertionSort3");
    profiler(qsort1, nums_t, "qsort1");
    profiler(qsort3, nums_t, "qsort3");
    profiler(qsort4, nums_t, "qsort4");

    cout << ">>>Testing on vector of sorted integers<<<\n";
    auto nums_s = SortedVector(vec_size);
    profiler(InsertionSort1, nums_s, "InsertionSort1");
    profiler(InsertionSort2, nums_s, "InsertionSort2");
    profiler(InsertionSort3, nums_s, "InsertionSort3");
    profiler(qsort1, nums_s, "qsort1");
    profiler(qsort3, nums_s, "qsort3");
    profiler(qsort4, nums_s, "qsort4");
    return 0;
}
