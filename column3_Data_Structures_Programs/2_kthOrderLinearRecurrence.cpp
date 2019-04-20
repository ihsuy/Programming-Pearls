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
A kth-order linear recurrence with constant coefficients defines a series as
a_n = c_1*a_(n – 1) + c_2*a_(n – 2) + ... + c_k*a_(n–k) + c_(k + 1),

where c1, ..., ck + 1 are real numbers.
Write a program that with input k, a1 ..., ak, c1, ..., ck+1,
and m produces the output a1 through am. How difficult is
that program compared to a program that evaluates one particular
fifth-order recurrence, but does so without using arrays?
*/

// can use array
vector<int> kthLinearRecurrence(const vector<int>& a, const vector<int>& c,
                                const int& k, const int& m)
{
	if(m <= k)
	{
		return {a.begin(), a.begin()+m};
	}

	
}

int main()
{


	return 0;
}
