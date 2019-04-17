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
How would you implement bit vectors using bitwise logical operations
implement: set, clr, test
*/

// size of int
#define SIZEPERWORD 32
// 2^5 is 32 and shifting int by 5 to the right is to divide it by 32
// which will be helpful when converting bit index to index in the int array
#define SHIFT 5
// 0x1f is 111111 is 31
#define MASK 0x1f
#define N 1000
struct bitVector
{
	// storage
	int * a;
	size_t size;
	bitVector(const size_t& sz): size((sz>>SHIFT)+1)
	{
		// sz>>SHIFT+1 converts number of bits to number of int
		a = new int[size];
		memset(a, 0, sz);
	}

	void set(const size_t& i)
	{
		// first find the index in a (integer index) using i (number of bits)
		// a[i>>SHIFT+1] is the location of integer that contains the i-th bit
		// second find the bit inside of this integer, we mod i by 32
		// i&MASK will get the last 5 bits in i which is equvalent to moding it by 32
		// Now we have the mask and the correct location to place the mask
		// we move the mask to the right int slot where i-th bit belongs
		// and do binary OR to set bit

		a[(i>>SHIFT)] |= 1<<(i&MASK);
	}

	void clr(const size_t& i)
	{
		// pretty much the same as set
		// but this time we get the opposite value and do bitwise AND to clear bits
		a[(i>>SHIFT)] &= ~1<<(i&MASK);
	}

	int test(const size_t& i)
	{
		// see if the ith bit is turned on
		return a[(i>>SHIFT)] & (1<<(i&MASK));
	}

	~bitVector()
	{
		cout << "removing bitVector...\n"; 
		delete a;
	}

	void show()
	{
		for (int i = 0; i < size; ++i)
		{
			cout << a[i] << ' ';
		}
		cout << '\n';
	}
};

int main()
{
	bitVector bv(N);
	bv.show();
	bv.set(32);
	bv.show();

	cout << bv.test(32) << '\n';

	std::bitset<10> b(63);
	cout << b << '\n';
	std::bitset<10> b2(63&0x1f);
	cout << b2 << '\n';


	return 0;
}
