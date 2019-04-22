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
Prove that this program terminates when its input x is a positive integer.
while x != 1 do
    if even(x)
        x = x/2
    else
        x = 3*x+1

*/

// not sure how to prove this
void simulate(int n)
{
    int i = n;
    int step = 0;
    while(n != 1)
    {
        if(n%2 == 0)
        {
            n/=2;
        }
        else
        {
            n = 3*n+1;
        }
        step++;
    }
    cout << "number: " << i << " step: " << step << "\n"; 
}

int main()
{
    for(int i = 1; i < 1000; ++i)
    {
        simulate(i);
    }

	return 0;
}
