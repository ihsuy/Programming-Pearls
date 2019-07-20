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
D. B. Lomet observes that hashing may solve the 1000-integer
search problem more efficiently than the tuned binary search.
Implement a fast hashing program and compare it to the tuned
binary search; how do they compare in terms of
speed and space?
*/

/*
As opposed to what was suggested in the problem,
the hashing search that I came up with was less efficient
than binary search in all kinds of situation that I could think of
although they are both very fast already and their difference is small
the hashing search uses a hashtable to store the first position of every
unique number and later retrieve their position directly by looking up in the
hashtable

result: after 100000 tests on size 1000 integer array
binarysearch  time: 132 nanoseconds
hashingsearch time: 164 nanoseconds
*/

int binarySearch(const vector<int>& nums, const int& target) {
    int low = -1, high = nums.size();
    while (low + 1 != high) {
        int mid = (low + high) >> 1;
        if (nums[mid] < target) {
            low = mid;
        } else {
            high = mid;
        }
    }
    int pos = high;
    if (pos >= nums.size() or nums[pos] != target) {
        return -1;
    }
    return pos;
}

unordered_map<int, int> locations;
int hashingSearch(const vector<int>& nums, const int& target) {
    if (locations.empty()) {
        locations[nums[0]] = 0;
        int sz = nums.size();
        for (int i = 1; i < sz; ++i) {
            if (nums[i] != nums[i - 1]) {
                locations[nums[i]] = i;
            }
        }
    }

    auto ite = locations.find(target);
    if (ite == locations.end()) {
        return -1;
    } else {
        return ite->second;
    }
}

pair<long long, int> profiler(int(bs)(const vector<int>&, const int&),
                              const vector<int>& nums,
                              const int& target) {
    auto t1 = chrono::high_resolution_clock::now();
    auto res = bs(nums, target);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}

int main() {
    // create test vector
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int sz = 1000;
    const int n_lower = 0;
    vector<int> nums;

    for (int i = 0, n = n_lower; i < sz; ++i) {
        if (rand() % 2) {
            n++;
        }
        nums.push_back(n);
    }
    assert(nums.size() == sz);

    const int nTest = 100000;
    ll t1_sum = 0, t2_sum = 0;
    for (int i = 0; i < nTest; ++i) {
        int tar = rand() % (sz + 5);

        auto p1 = profiler(binarySearch, nums, tar);
        auto p2 = profiler(hashingSearch, nums, tar);

        t1_sum += p1.first;
        t2_sum += p2.first;

        auto res1 = p1.second;
        auto res2 = p2.second;

        assert(res1 == -1 or nums[res1] == tar);
        assert(res1 == -1 or nums[res2] == tar);
        assert(res1 == res2);
    }

    cout << "binarysearch  time: " << t1_sum / nTest << endl;
    cout << "hashingsearch time: " << t2_sum / nTest << endl;

    return 0;
}
