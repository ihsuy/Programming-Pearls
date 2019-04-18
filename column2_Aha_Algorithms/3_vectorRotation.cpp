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
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

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
void vector_rotate_withReverse(vector<int>& nums, int n)
{	// rotate nums to the right by n
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
// To rotate a vector to the right we just need to find all the cycles and swap every
// entry in the cycle with the value on its right in the same cycle
void vector_rotate_withJuggling(vector<int>& nums, int n)
{
	int swap_count = 0;
	int i = 0;
	while (swap_count < nums.size())
	{	// we know that there's only nums.size() swaps 
		// we keep proceeding with step size = n until
		// we return back to the beginning point
		int begin = i;
		int prev = nums[begin];
		do
		{
			i = (i + n) % nums.size();
			// keep a record of the value thats going to be 
			// replaced by the previous value
			// since we are going to assign the next value in 
			// the cycle to this value
			int temp = nums[i];
			nums[i] = prev;
			prev = temp;

			swap_count++;
		}
		while (i != begin);
		// if we didn't swap enough times in this cycle
		// we shift our beginning point to the right by 1
		i++;
	}
}

int main()
{
	vector<int> nums {1, 2, 3, 4, 5, 6, 7, 8, 9};
	vector<int> nums2 = nums;
	for (int n = 0; n < 10; ++n)
	{
		vector<int> nums1 = nums;
		vector<int> nums2 = nums;
		cout << "n: " << n << endl;

		vector_rotate_withReverse(nums1, n);
		cout << "result1: ";
		inspect<vector<int>>(nums1);

		vector_rotate_withJuggling(nums2, n);
		cout << "result2: ";
		inspect<vector<int>>(nums2);

		if(nums1 != nums2)
		{
			cout << "incorrect rotation for n=" << n << "\n";
		}
	}
	return 0;
}
