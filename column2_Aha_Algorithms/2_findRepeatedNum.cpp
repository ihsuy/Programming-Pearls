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
Rotate a one-dimensional vector of n elements left by i positions.
For instance, with n=8 and i=3, the vector abcdefgh is rotated to defghabc.
Simple code uses an n-element intermediate vector to do the job in n steps.
Can you rotate the vector in time proportional to n using only a few dozen
extra bytes of storage?
*/

/*
Couldn't understand how exactly the method described below works:

“Binary search finds an element that occurs at least twice by
recursively searching the subinterval that contains more than
half of the integers. My original solution did not guarantee that
the number of integers is halved in each iteration, so the worst-case
 run time of its log2 n passes was proportional to n log n. Jim Saxe
 reduced that to linear time by observing that the search can avoid
 carrying too many duplicates. When his search knows that a duplicate
 must be in a current range of m integers, it will only store m +1 integers
 on its current work tape; if more integers would have gone on the tape,
 his program discards them. Although his method frequently ignores input
 variables, its strategy is conservative enough to ensure that it finds at
 least one duplicate.”
*/

// method1
// narrowing down the range by utilizing pigeon hole principle
// by checking 4 bits at a time for each 32 bits integer inputs

int getBits(int n, const int& len, const int& i)
{	// from the ith least significant digit, get the value
	// of bits in n of length "len"
	int mask = (1 << len) - 1;
	n >>= i;
	return mask & n;
}

int findDubplicate(int* nums, const long& n)
{
	const int mask_size = 4;
	const int sz = 1<<(mask_size);
	int counter[sz];

	int range = n / sz;
	vector<int> signatures;
	for (int b = 0; b <= 32-mask_size; b += mask_size)
	{
		memset(counter, 0, sizeof(int)*sz);
		for (int i = 0; i < n; ++i)
		{
			bool valid = true;

			for (int bb = 0; not signatures.empty() and bb < b; bb += mask_size)
			{
				int temp = getBits(nums[i], mask_size, bb);
				if (temp != signatures[bb / mask_size])
				{
					valid = false;
					break;
				}
			}

			if (not valid)
			{
				continue;
			}

			int signature = getBits(nums[i], mask_size, b);

			counter[signature]++;
			if (counter[signature] > range)
			{
				signatures.push_back(signature);
				break;
			}

		}
		range /= sz;
	}

	int result = 0;
	for (int i = 0 ; i < signatures.size(); ++i)
	{
		result |= (signatures[i]<<(i*mask_size));
	}

	return result;
}

long maxn = 43000000;
int* nums = new int[maxn];
int main()
{	
	cout << "creating numbers...\n";
	for (int i = 0; i < maxn; ++i)
	{
		nums[i] = i;
	}
	nums[4000000] = 3141592; // explicitly create a duplicate of value
	cout << "searching for duplicates...\n";
	cout << "duplicate: " << findDubplicate(nums, maxn) << '\n';
	return 0;
}
