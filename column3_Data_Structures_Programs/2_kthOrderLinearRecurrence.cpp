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

double kthLinearRecurrence(const vector<double>& a, const vector<double>& c,
                           const double& k, const double& m)
{	// note this program doesn't do exactly what the problem asks
	// instead of returning the ouput a_1 through a_m
	// i just return am.
	// since if m is less than or equal to k, the result is already provided
	// I dont see the point why I have to fill those information into a
	// different container again
	// only a_m will be the new information (if m is k+1)
	if (m <= k)
	{
		return a[m];
	}
	else if (m == k + 1)
	{
		double result = 0.0;
		for (int i = 0; i < a.size(); ++i)
		{
			result += c[i] * a[a.size() - 1 - i];
		}
		return result + c.back();
	}
	else
	{
		throw runtime_error("no enough information about c to produce the result");
	}
}

// a program that calculates the fifth order recurrence without using array
double fifthOcurrence(const double& a1, const double& a2,
                      const double& a3, const double& a4,
                      const double& c1, const double& c2,
                      const double& c3, const double& c4,
                      const double& c5)
{
	return c1 * a4 + c2 * a3 + c3 * a2 + c4 * a1 + c5;
}
// the program above may looks simple(??)
// but its actually horribly unfriendly to its users
// imagine when you got this function and have to insert all nine parameters
// using your hand like this:
// fifthOccurence(12.24, 219.12, 9.89, 82.48, 12.24, 219.12, 55.9, 2.8, 19.24)
// do you still remember where begins your first c1 ?
// ok if you say you will use named variables but then you will need 9 new lines
// just initialize your variables...
// also what if your boss want you to make it a function that calculates
// the 100th ocurrence? you will have 201 variables to create then

// below is a function does the job calculating occurence of any order using array
double nthLinearRecurrence(const vector<double>& a, const vector<double>& c)
{
	assert(a.size() == (c.size()-1));

	double result = 0.0;
	for (int i = 0; i < a.size(); ++i)
	{
		result += c[i] * a[a.size() - 1 - i];
	}
	return result + c.back();
}

int main()
{
	vector<double> a {1, 5, 6, 7, 12, 3};
	vector<double> c {2, 5, 1, 1, 11, 1, 4};
	cout << kthLinearRecurrence(a, c, 6, 7) << endl;

	return 0;
}
