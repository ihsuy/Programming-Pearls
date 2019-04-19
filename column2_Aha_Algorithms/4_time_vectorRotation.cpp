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
Several readers pointed out that while all three rotation
algorithms require time proportional to n, the juggling
algorithm is apparently twice as fast as the reversal algorithm:
it stores and retrieves each element of the array just once, while
the reversal algorithm does so twice. Experiment with the functions
to compare their speeds on real machines; be especially sensitive
to issues surrounding the locality of memory references.
*/

// copy paste from problem 3
void vector_rotate_withReverse(vector<int>& nums, int n)
{
	n %= nums.size();

	reverse(nums.begin(), nums.end());
	reverse(nums.begin(), nums.begin() + n);
	reverse(nums.begin() + n, nums.end());
}

void vector_rotate_withJuggling(vector<int>& nums, int n)
{
	int swap_count = 0;
	int i = 0;
	while (swap_count < nums.size())
	{
		int begin = i;
		int prev = nums[begin];
		do
		{
			i = i + n;

			if(i >= nums.size())
			{
				i -= nums.size();
			}

			int temp = nums[i];

			nums[i] = prev;

			prev = temp;

			swap_count++;
		}
		while (i != begin);
		i++;
	}
}

int gcd(int a, int b)
{
	while (a != b)
	{
		if (a > b)
		{
			a -= b;
		}
		else
		{
			a += b;
		}
	}
	return a;
}

void vector_rotate_withJuggling2(vector<int>& nums, int n)
{	// rotate backward
	if(n == 0 or n == nums.size())
	{
		return;
	}
	n %= nums.size();

	int number_of_cycle = gcd(nums.size(), n);

	// int cycle_size = nums.size()/number_of_cycle;

	for(int i = 0; i < number_of_cycle; ++i)
	{
		int prev = nums[i];
		int j = i;
		for(;;)
		{
			int next = j + n;

			if(next >= nums.size())
			{
				next-=nums.size();
			}

			if(next == i)
			{
				break;
			}

			nums[j] = nums[next];

			j = next;
		}

		nums[j] = prev;
	}
}

void mSwap(vector<int>& nums, const int& a, const int& b, const int& m)
{
	for (int i = 0; i < m; ++i)
	{
		swap(nums[a + i], nums[b + i]);
	}
}

void vector_rotate_withGCD(vector<int>& nums, const int& n)
{
	if (n == nums.size() or n == 0)
	{
		return;
	}

	int i = n, j = nums.size() - n, p = n;
	while (i != j)
	{
		if (i > j)
		{
			mSwap(nums, p - i, p, j);
			i -= j;
		}
		else
		{
			mSwap(nums, p - i, p + j - i, i);
			j -= i;
		}
	}

	mSwap(nums, p - i, p, i);
}

// end of copy paste from problem 3


int main()
{
	// const int kDataSize = 10000000;

	// vector<int> vo;
	// for (int i = 0; i < kDataSize; ++i)
	// {
	// 	vo.push_back(i);
	// }
	// vector<int> v;
	// cout << "experimenting on a number array of size " << kDataSize << endl;
	// for (int shift = 1; shift < kDataSize; shift *= 10)
	// {
	// 	cout << "shifting by " << shift << '\n';
	// 	v = vo;
	// 	auto t1 = chrono::high_resolution_clock::now();
	// 	vector_rotate_withReverse(v, shift);
	// 	auto t2 = chrono::high_resolution_clock::now() - t1;
	// 	cout << "reverse method  : " << chrono::duration_cast<chrono::microseconds>(t2).count() << endl;
	// 	v = vo;
	// 	t1 = chrono::high_resolution_clock::now();
	// 	vector_rotate_withJuggling(v, shift);
	// 	t2 = chrono::high_resolution_clock::now() - t1;
	// 	cout << "juggling method : " << chrono::duration_cast<chrono::microseconds>(t2).count() << endl;
	// 	v = vo;
	// 	t1 = chrono::high_resolution_clock::now();
	// 	vector_rotate_withJuggling2(v, shift);
	// 	t2 = chrono::high_resolution_clock::now() - t1;
	// 	cout << "juggling method2: " << chrono::duration_cast<chrono::microseconds>(t2).count() << endl;
	// 	v = vo;
	// 	t1 = chrono::high_resolution_clock::now();
	// 	vector_rotate_withGCD(v, shift);
	// 	t2 = chrono::high_resolution_clock::now() - t1;
	// 	cout << "mSwap method    : " << chrono::duration_cast<chrono::microseconds>(t2).count() << endl;
	// }
	
	vector<int> to{1,2,3,4,5,6,7,8};

	for(int i = 0; i < 10; ++i)
	{
		vector<int> t = to;
		vector_rotate_withJuggling2(t, i);
		vector_rotate_withJuggling(t, i);
		inspect<vector<int>>(t);
	}
	return 0;
}
