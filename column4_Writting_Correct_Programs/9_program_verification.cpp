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
As exercises in program verification,
precisely specify the input/output behavior of each
of the following program fragments and show that the
code meets its specification. The first program
implements the vector addition a = b + c.

i = 0
while i < n
    a[i] = b[i] + c[i]
    i = i+1

(This code and the next two fragments expand the “for i = [0, n)”
loop to a while loop with an increment at the end.)
*/

// range of i:
// i starts from 0 and will be incremented
// every time after one round in the loop
// and the loop breaks immediently after i >= a.size()
// i precisely controls number of loops as it ranges in [0, a.size())
// i will have exactly a.size() available values which then
// allow the while loop to run for a.size() times
// if we assert the size of b and c to be no smaller than a
// then i will not exceed any of their bounds.
// and a will hold the sum of b[i] and c[i] where i belonges to [0, a.size()]
void VectorAddition(const vector<int>& b, const vector<int>& c, vector<int>& a)
{
    assert(a.size() <= b.size() and a.size() <= c.size());
    int i = 0;
    while (i < a.size())
    {
        a[i] = b[i] + c[i];
        i = i + 1;
    }
}

/*
The next fragment computes the maximum value in the array x.
max = x[0]
i = 1
while i < n do
    if x[i] > max
        max = x[i]
    i = i+1
*/

// first lets look at the range that this function
// is examining. it starts with a default value x[0] as max_val
// then check for i from 1 to x.size()-1
// which is total of x.size() checks so we did check every value in x
// However, this function assumes x.size() > 0 and won't handle empty
// inputs. 
// next lets look at whether if the return value is really the maximum
// value in x. since we begin with the first value and will examine 
// every value in the array and compare it with the current max
// assume this is incorrect, i.e. there's a value M in x thats larger than
// return value max_val, M > max_val and M is the true max value in x.
// we also know if M, at one point of time, occupied the value of max_val
// then it's impossible to later assign max_val to a value thats smaller than M.
// 
// then since we've seen M before in the loop, then comparison M > max_val is
// performed, but M never successfully replaced max_val which means max_val
// at that point was larger than M but M is said to be the true max,
// a contradiction.
// so max_val is the true max
int MaxumumValue(const vector<int>& x)
{
    int max_val = x[0];
    int i = 1;
    while(i < x.size())
    {
        if(x[i] > max_val)
        {
            max_val = x[i];
        }
        i = i+1;
    }
    return max_val;
}


/*
This sequential search program returns the position of the
first occurrence of t in the array x[0..n–1].
i = 0
while i < n && x[i] != t
    i = i+1
if i >= n
    p = -1
else
    p = i
*/

/*
This program computes the nth power of x in time proportional
to the logarithm of n. This recursive program is straightforward
to code and to verify; the iterative version is subtle, and is
left as an additional problem.

function exp(x, n)
        pre  n >= 0
        post result = x^n
    if n = 0
        return 1
    else if even(n)
        return square(exp(x, n/2))
    else
        return x*exp(x, n-1)”

*/



int main()
{


    return 0;
}
