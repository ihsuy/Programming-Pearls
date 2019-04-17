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
Generating k integers less than n without duplicates
*/

vector<int> uniqueRandom(const int& k, const int& n)
{	// create k unique random integer 
	// ranging from 0 to n-1 inclusive
	if(k > n)
	{
		throw runtime_error("invalid k value: k has to be less than n");
	}

	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	vector<int> nums;
	nums.reserve(n);

	for(int i = 0; i < n; ++i)
	{	// first initialize full range of integers in a vector
		nums.push_back(i);
	}

	for(int i = 0; i < k; ++i)
	{	// while moving forward in the vector,
		// randomly swap ith number with another
		// integer in nums[i+1, n)
		int j = rand()%(n-i);
		swap(nums[i], nums[i+j]);
	}
	// only return the first k elements
	return vector<int>(nums.begin(), nums.begin()+k);
}

int main()
{
	vector<int> r = uniqueRandom(10, 100);
	inspect<vector<int>>(r);

	return 0;
}
