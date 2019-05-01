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
    while (i < x.size())
    {
        if (x[i] > max_val)
        {
            max_val = x[i];
        }
        i = i + 1;
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

// First look at i's range
// i begin with value 0 and will be only incremented in the while loop
// since we perform the check (i < x.size()) before accessing x[i]
// i will not exceed the boundary of x

// Next check logical parts' behaviour
// the result is determined by the last if statement
// if(i >= x.size()) then we claim there's no such value exists
// by returning -1
// otherwise we claim that we found it and return i
// note the value of i that at this point
// must violates the while loop's condition
// namely, i must be either
// no smaller than x.size() or
// pointing at t in x
// we know that if i>=x.size() is false then x[i] == t must true
// and vise versa
// and that's why we can conclude the result only after one check

// check correctness of the result
// as concluded above, i>=x.size() implies x[i] != t was true
// in the whole process, that means we've never seen t in x
// and returning -1 is correct

// for the case when x[i] == t and we return i
// lets assume this is incorrect, i.e. x[j] == t for some j < i
// j belongs to the range [0, i)
// however, since we've checked, at this point, x[i] for i in [0, i)
// none of x[i] == t. this is a contradiction.
// therefore the result is correct

int FirstOccurenceOf(const int& t, const vector<int>& x)
{
    int i = 0;
    while (i < x.size() and x[i] != t)
    {
        i = i + 1;
    }

    if (i >= x.size())
    {
        return -1;
    }
    else
    {
        return i;
    }
}

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

// the assertion guarantee n is a positive integer
// then the case 0 is handled correctly
// we are left with n in the range [1, max]
// of course this program if x and n gets large enough
// it will cause data type to overflow quickly
// but thats not going to be solved unless we create a mechanism for
// extra large numbers, so lets put that aside.
// observe the behavior of the last 2 code blocks
// the function is actually probing 1 value for n at a time
// until n becomes even, it cuts size of n by half then continue probing
// since there're roughly half odd and half even in any range of
// consecutive integers with size >= 2, the cutting off by half will happens
// at least roughly half of the time and this makes the algorithm logn
// the correctness is obvious because
// x^n is equal to (x^(n/2))^2 if n is even and
// x^n is always equal to x*x^(n-1)
// either division by 2 or substraction by 1 will cause n to be smaller
// and finally reaches 0 which is our termination condition for the recursion
int Exp(const int& x, const int& n)
{
    assert(n >= 0);

    if (n == 0)
    {
        return 1;
    }
    else if (n % 2 == 0)
    {
        auto v = Exp(x, n >> 1);
        return v * v;
    }
    else
    {
        return x * Exp(x, n - 1);
    }
}

// Addtional problem:
// implement an iterative version of the Exp function
int Exp_iterative(const int& x, int n)
{
    assert(n >= 0);
    // use stacks since we have to do every thing backward later
    stack<int> will_square;
    stack<int> will_mul_x;

    while (n != 0)
    {   // find and save exactly what to do at each point
        // where the value of n will be used as a key
        // to later identify which operation should
        // be performed earlier
        // since dividing n by 2 and substract by 1 always produce
        // different results unless n is 1 or 0
        // but a positive n has to be 1 before becoming 0 in either case
        // and the while loop terminates when n is 1 we we are good
        if (n % 2 == 0)
        {   
            will_square.push(n);
            n >>= 1;
        }
        else
        {
            will_mul_x.push(n);
            n--;
        }
    }

    // now we have the a detailed manual called 
    // "How to perform exponential in log n time for x and n"
    // we just follow it
    // smaller top of 2 stacks will be handled first
    // since it came later in the process above
    // we keep performing 2 different operation until
    // there's not more number left in both stacks
    int result = 1;
    while (not will_square.empty() or not will_mul_x.empty())
    {
        if (not will_mul_x.empty() and
                (will_square.empty() or will_mul_x.top() < will_square.top()))
        {
            result *= x;
            will_mul_x.pop();
        }
        else if (not will_square.empty() and
                 (will_mul_x.empty() or will_mul_x.top() > will_square.top()))
        {
            result *= result;
            will_square.pop();
        }
    }
    // done
    return result;
}


int main()
{
    cout << Exp(5, 11) << '\n';
    cout << Exp_iterative(5, 11) << '\n';
    return 0;
}11
