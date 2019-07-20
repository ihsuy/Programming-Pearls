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
Sequential search and binary search represent a
tradeoff between search time and preprocessing time.
How many binary searches need be performed in an n-element
table to buy back the preprocessing time required to
sort the table?
*/

int SequentialSearch(const vector<int>& nums, const int& target) {
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] == target) {
            return i;
        }
    }
    return -1;
}

int BinarySearch(const vector<int>& sorted_nums, const int& target) {
    int low = 0, high = sorted_nums.size() - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (sorted_nums[mid] == target) {
            return mid;
        }

        if (sorted_nums[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main() {
    const size_t kNumsSize = 100000;
    const size_t test_case_number = 50000;
    size_t checkpoint = test_case_number / 5;

    // generate kNumsSize unique random numbers
    vector<int> nums;
    nums.reserve(kNumsSize);

    cout << "generating " << kNumsSize << " unique random integers...\n";

    for (int i = 0; i < kNumsSize; ++i) {
        nums.push_back(i);
    }

    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 0; i < kNumsSize; ++i) {
        swap(nums[i], nums[i + rand() % (kNumsSize - i)]);
    }
    vector<int> nums_for_seqSearch = nums;

    cout << "completed\n";

    cout << "preprocessing for binarySearch...\n";

    auto t1 = chrono::high_resolution_clock::now();
    sort(nums.begin(), nums.end());
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto sorting_time_in_nanoseconds =
        chrono::duration_cast<chrono::nanoseconds>(t2).count();

    cout << "completed\nsorting time spent: " << sorting_time_in_nanoseconds
         << " nanoseconds\n";

    cout << "comparing performance of BinarySearch and SequentialSearch for "
         << test_case_number << " times\n";

    long long total_sequential_search_time = 0;
    long long total_binary_search_time = 0;

    long long total_time_difference = 0;
    long long turning_point =
        -1;  // number of search need to perform to make binary search cheaper

    for (int i = 0; i < test_case_number; ++i) {
        if (i % checkpoint == 0) {
            cout << "processing... " << ((double)i / test_case_number) * 100
                 << "%\n";
        }
        auto begin = chrono::high_resolution_clock::now();
        SequentialSearch(nums_for_seqSearch, i);
        auto time_elapsed = chrono::high_resolution_clock::now() - begin;

        auto sequential_search_time =
            chrono::duration_cast<chrono::nanoseconds>(time_elapsed).count();

        begin = chrono::high_resolution_clock::now();
        BinarySearch(nums, i);
        time_elapsed = chrono::high_resolution_clock::now() - begin;

        auto binary_search_time =
            chrono::duration_cast<chrono::nanoseconds>(time_elapsed).count();

        total_sequential_search_time += sequential_search_time;
        total_binary_search_time += binary_search_time;

        // cout << "sequential_search_time: " << sequential_search_time << "
        // nanoseconds\n"; cout << "binary_search_time    : " <<
        // binary_search_time << " nanoseconds\n";
        long long time_difference = sequential_search_time - binary_search_time;
        // cout << "difference            : " << time_difference << "
        // nanoseconds\n";
        total_time_difference += time_difference;

        if (turning_point == -1 and
            total_time_difference > sorting_time_in_nanoseconds) {
            turning_point = i;
        }
    }

    cout << "processing... 100%\nComplete\n";

    cout << "total_sequential_search_time: " << total_sequential_search_time
         << " nanoseconds\n";
    cout << "total_binary_search_time    : " << total_binary_search_time
         << " nanoseconds\n";
    cout << "total_time_difference       : " << total_time_difference
         << " nanoseconds\n";
    cout << "number binary searches need be performed to buy back the "
            "preprocessing time:\n";
    cout << turning_point << '\n';

    return 0;
}
