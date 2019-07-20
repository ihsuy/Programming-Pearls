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
Because sequential search is simpler than binary search,
it is usually more efficient for small tables.
On the other hand, the logarithmic number of
comparisons made by binary search implies that
it will be faster than the linear time of sequential
search for large tables. The break-even point is a
function of how much each program is tuned.
How low and how high can you make that break-even point?
What is it on your machine when both programs are
equally tuned?
*/

int sequentialSearch(vector<int>& nums, const int& target, const int& size) {
    nums.push_back(0);
    nums[size] = target;

    int i = 0;
    for (;; i++) {
        if (nums[i] == target) {
            break;
        }
    }
    if (i == size) {
        return -1;
    }
    nums.pop_back();
    return i;
}

int binarySearch(const vector<int>& nums, const int& target) {
    int low = 0;
    for (int i = (nums.size() - 1) >> 1; i > 0; i >>= 1) {
        if (nums[low + i] < target) {
            low = low + i + 1;
        }
    }

    if (low < nums.size() and nums[low] == target) {
        return low;
    }

    return -1;
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int init_size = 2;
    int max_size = 1 << 20;
    int n = 1;

    vector<int> nums{0};
    nums.reserve(max_size);
    int nTest = 60;  // time to search for each array size for each algorithm

    for (int sz = init_size; sz <= max_size;
         sz <<= 1) {  // create a sorted array of sz size
        for (int i = 0; i < (sz >> 1); ++i) {
            if (rand() % 2) {
                n++;
            }
            nums.push_back(n);
        }

        shuffle(nums.begin(), nums.end(),
                default_random_engine(chrono::high_resolution_clock::now()
                                          .time_since_epoch()
                                          .count()));

        cout << "testing on array of size " << nums.size() << "...\n";

        // for each array size test nTest times
        ll t1_sum = 0, t2_sum = 0;

        for (int i = 0; i < nTest; ++i) {
            int target = rand() % (n + n / 8);

            auto t1 = chrono::high_resolution_clock::now();

            auto res1 = sequentialSearch(nums, target, sz);

            auto t2 = chrono::high_resolution_clock::now() - t1;
            auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
            t1_sum += t;
            assert(res1 < 0 or nums[res1] == target);
        }

        auto t1 = chrono::high_resolution_clock::now();
        sort(nums.begin(), nums.end());
        auto t2 = chrono::high_resolution_clock::now() - t1;
        auto sort_time = chrono::duration_cast<chrono::nanoseconds>(t2).count();

        for (int i = 0; i < nTest; ++i) {
            int target = rand() % (n + n / 8);

            auto t1 = chrono::high_resolution_clock::now();
            auto res2 = binarySearch(nums, target);
            auto t2 = chrono::high_resolution_clock::now() - t1;
            auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
            t2_sum += t;

            assert(res2 < 0 or nums[res2] == target);
        }
        t2_sum += sort_time;
        cout << "avg sequential search time: " << (double)t1_sum / nTest
             << '\n';
        cout << "avg binary search time    : " << (double)t2_sum / nTest
             << '\n';
    }

    return 0;
}
