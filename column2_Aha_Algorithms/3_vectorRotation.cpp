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
We skimmed two vector rotation algorithms
that require subtle code; implement each as
a program. How does the greatest common divisor
of i and n appear in each program?
*/

// method 1 do 3 reverse
// this method can be understood if you look at an example
// let nums = 1,2,3,4,5,6 and we want to
// rotate it to the right by 3 steps
// original: 1 2 3 4 5 6
// rotated : 4 5 6 1 2 3
// notice if we reverse the first half and the
// second half of the rotated result
// we get    6 5 4 3 2 1
// which is what we get reversing the original vector
void vector_rotate_withReverse(vector<int>& nums,
                               int n) {  // rotate nums to the right by n
    n %= nums.size();

    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + n);
    reverse(nums.begin() + n, nums.end());
}

// method 2 juggling
// notice that it doesn't matter what our n is
// keep walking in a wrapping manner will always result in an cycle
// in other words we will always be going back to where we started
// number of steps we need to take in order to go back to the starting point
// is actually equal to lcm(nums.size(), n)/n
// To rotate a vector to the right we just need to find all the cycles and swap
// every entry in the cycle with the value on its right in the same cycle
void vector_rotate_withJuggling(vector<int>& nums, int n) {
    if (n == 0 or n == nums.size()) {
        return;
    }
    n %= nums.size();

    int swap_count = 0;
    int i = 0;
    while (swap_count <
           nums.size()) {  // we know that there's only nums.size() swaps
        // we keep proceeding with step size = n until
        // we return back to the beginning point
        int begin = i;
        int prev = nums[begin];
        do {
            i = (i + n) % nums.size();
            // keep a record of the value thats going to be
            // replaced by the previous value
            // since we are going to assign the next value in
            // the cycle to this value
            int temp = nums[i];
            nums[i] = prev;
            prev = temp;

            swap_count++;
        } while (i != begin);
        // if we didn't swap enough times in this cycle
        // we shift our beginning point to the right by 1
        i++;
    }
}

void vector_rotate_withJuggling2(vector<int>& nums, int n) {  // rotate backward
    if (n == 0 or n == nums.size()) {
        return;
    }
    n %= nums.size();

    int number_of_cycle = gcd(nums.size(), n);

    // int cycle_size = nums.size()/number_of_cycle;

    for (int i = 0; i < number_of_cycle; ++i) {
        int prev = nums[i];
        int j = i;
        for (;;) {
            int next = j + n;

            if (next >= nums.size()) {
                next -= nums.size();
            }

            if (next == i) {
                break;
            }

            nums[j] = nums[next];

            j = next;
        }

        nums[j] = prev;
    }
}

void mSwap(vector<int>& nums,
           const int& a,
           const int& b,
           const int& m) {  // swap nums[a, ..., a+m-1] with nums[b, ..., b+m-1]
    for (int i = 0; i < m; ++i) {
        swap(nums[a + i], nums[b + i]);
    }
}

void vector_rotate_withGCD(vector<int>& nums, const int& n) {
    if (n == nums.size() or n == 0) {
        return;
    }

    int i = n, j = nums.size() - n, p = n;
    while (i != j) {
        if (i > j) {
            mSwap(nums, p - i, p, j);
            i -= j;
        } else {
            mSwap(nums, p - i, p + j - i, i);
            j -= i;
        }
    }

    mSwap(nums, p - i, p, i);
}
int main() {
    vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> nums2 = nums;
    for (int n = 0; n < 10; ++n) {
        vector<int> nums1 = nums;
        vector<int> nums2 = nums;
        vector<int> nums3 = nums;
        cout << "n: " << n << endl;

        vector_rotate_withReverse(nums1, n);
        cout << "result1: ";
        inspect<vector<int>>(nums1);

        vector_rotate_withJuggling(nums2, n);
        cout << "result2: ";
        inspect<vector<int>>(nums2);

        vector_rotate_withGCD(nums3, n);
        cout << "result3: ";
        inspect<vector<int>>(nums3);

        if (nums1 != nums2) {
            cout << "incorrect rotation for n=" << n << "\n";
        }
    }
    return 0;
}
