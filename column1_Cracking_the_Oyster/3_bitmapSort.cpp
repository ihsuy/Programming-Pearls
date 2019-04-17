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
“Run-time efficiency was an important part of the design goal,
and the resulting program was efficient enough.
Implement the bitmap sort on your system and measure its run time;
how does it compare to the system sort and to the sorts in Problem 1?
Assume that n is 10,000,000, and that the input file contains 1,000,000 integers.”
*/

#define N 10000000 // number of bits required
#define M 1000000  // number of integers in input

void bitmapSort(vector<int>& nums)
{
	bitset<N> bitmap;
	for (int i = 0; i < nums.size(); ++i)
	{
		bitmap[i] = 1;
	}

	for (int i = 0, j = 0; j < nums.size() and i < N; ++i)
	{
		if (bitmap[i])
		{
			nums[j++] = i;
		}
	}
}

bool isSortedAscend(const vector<int>& nums)
{	// check if its sorted in ascending
	for (int i = 1; i < nums.size(); ++i)
	{
		if (nums[i] < nums[i - 1])
		{
			return false;
		}
	}
	return true;
}

void timeIt(void (*sortAlgorithm)(vector<int>&), const string& name, vector<int>& v)
{
	cout << "<<<<<<<<timeIt<<<<<<<<\n";
	int n = v.size();
	cout << "Sorting " << n << " integers...\n";

	auto t1 = chrono::high_resolution_clock::now();
	sortAlgorithm(v);
	auto t2 = chrono::high_resolution_clock::now() - t1;

	auto time_in_nano = chrono::duration_cast<chrono::nanoseconds>(t2).count();
	auto time_in_micro = chrono::duration_cast<chrono::microseconds>(t2).count();

	cout << "Completed\n";
	cout << "Sorted " << n << " integers using \"" << name << "\"\n";
	cout << "Time elapsed:\n" << time_in_micro / 1000 << " milliseconds\n";
	cout << time_in_micro << " microseconds\n";
	cout << time_in_nano << " nanoseconds\n";
}

void sys_sort(vector<int>& nums)
{	// system sort wrapper
	sort(nums.begin(), nums.end());
}

int main()
{
	srand(chrono::high_resolution_clock::now().time_since_epoch().count());

	vector<int> input;
	input.reserve(M);
	for (int i = 0; i < M; ++i)
	{
		input.push_back(rand() % N);
	}
	vector<int> input_cp = input;

	timeIt(bitmapSort, "bitmap sort", input);
	timeIt(sys_sort, "system sort", input_cp);

	cout << "input is sorted:    " << isSortedAscend(input) << '\n';
	cout << "input_cp is sorted: " << isSortedAscend(input_cp) << '\n';
	return 0;
}
