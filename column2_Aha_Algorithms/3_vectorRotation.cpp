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
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }
template<typename T>
inline void inspect(T& t){typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

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
void vector_rotate1(vector<int>& nums, int n)
{	// rotate nums to the right by n
	n %= nums.size();
	reverse(nums.begin(), nums.end());
	reverse(nums.begin(), nums.begin()+n);
	reverse(nums.begin()+n, nums.end());
}


int main()
{
	vector<int> nums {1,2,3,4,5,6,7,8};
	vector_rotate1(nums, 3);
	inspect<vector<int>>(nums);

	return 0;
}
