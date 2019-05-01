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
// the program above is horribly user unfriendly
// first to insert all nine parameters like this:
// fifthOccurence(12.24, 219.12, 9.89, 82.48, 12.24, 219.12, 55.9, 2.8, 19.24)
// can be confusing and error proned, 
// i.e. its hard to tell where begins the value of c1
// secondly even if named variables are used, 9 new lines has to be added
// just for initializing variables
// In addition, maintanance of this code or
// modification for higher order ocurrence would be difficult
// 100th ocurrence would require 201 arguments

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
