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
compare speed of modulo operation and a if statement alternative
namely, compare:

n%mod

and

if(n>=mod) n -= mod;


*/

void modulo(int& n, const int& mod)
{
    n %= mod;
}

// result:
// (assume n < 2*mod)
// avg normal modulo function: 41.0139 nano
// avg ifmodulo              : 35.2428
// a bit faster than %
void ifmodulo(int& n, const int& mod)
{
    if (n >= mod)
    {
        n -= mod;
    }
}

// result
// generic
// avg normal modulo function: 65.93 nano
// avg ifmodulo2             : 80.49 nano
// this function is slower than the % operation
void ifmodulo2(int& n, const int& mod)
{
    while (n >= mod)
    {
        n -= mod;
    }
}

ll profiler(void(modulo_func)(int&, const int&), int& n, const int& mod)
{
    auto t1 = chrono::high_resolution_clock::now();
    modulo_func(n, mod);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    //cout << "result: " << n << '\n';
    //cout << "func time: " << t << "nanoseconds\n";
    return t;
}


int main()
{
    //int nn = 100;
    int mod = 1000000;

    ll t1_sum = 0;
    ll t2_sum = 0;
    // ll t3_sum = 0;
    for (int n = 0; n < 2 * mod; ++n)
    {
        int n1 = n, n2 = n/*, n3 = n*/;

        auto t1 = profiler(modulo, n1, mod);
        auto t2 = profiler(ifmodulo, n2, mod);
        // auto t3 = profiler(ifmodulo2, n3, mod);
        assert(n1 == n2);

        t1_sum += t1;
        t2_sum += t2;
        // t3_sum += t3;
    }

    cout << "avg t1: " << (double)t1_sum / (2 * mod) << '\n';
    cout << "avg t2: " << (double)t2_sum / (2 * mod) << '\n';

    return 0;
}
