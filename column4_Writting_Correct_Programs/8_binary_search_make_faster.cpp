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
Binary search is fundamentally faster than sequential search:
to search an n-element table, it makes roughly log2 n comparisons
while sequential search makes roughly n/2.
While it is often fast enough, in a few cases binary search
must be made faster yet. Although you can’t reduce the
logarithmic number of comparisons made by the algorithm,
can you rewrite the binary search code to be faster?
For definiteness, assume that you are to search a sorted
table of n = 1000 integers.
*/

int BinarySearch(const vector<int>& nums, const int& val) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
        long long mid = (low + high) >> 1;
        int n = nums[mid];

        if (n == val) {
            return mid;
        }

        if (n > val) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

long timeit(int(bs)(const vector<int>&, const int&),
            const vector<int>& nums,
            const int& val,
            const bool& verbose = true) {
    auto t1 = chrono::high_resolution_clock::now();
    bs(nums, val);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    long t_nano = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    if (verbose)
        cout << "time: " << t_nano << " nanoseconds\n";
    return t_nano;
}

int main() {
    const int arr_size = 1000;
    const int max_num = 80000;

    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    vector<int> nums;
    for (int i = 0; i < arr_size; ++i) {
        nums.push_back(rand() % max_num);
    }
    sort(nums.begin(), nums.end());

    const int nTest = 100000;
    const int verbose = false;

    long long time_nano = 0;
    for (int i = 0; i < nTest; ++i) {
        int val = rand() % max_num;
        time_nano += timeit(BinarySearch, nums, val, verbose);
    }
    cout << "avg: " << (double)time_nano / nTest << '\n';

    return 0;
}
