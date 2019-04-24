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
Appel found that changing from double-precision arithmetic
to single-precision arithmetic doubled the speed of his program. 
Choose an appropriate test and measure that speedup on your system.
*/

float add_single(const int& n)
{
    float f = 3.3;
    for(int i = 0; i < n; i++)
    {
        f += f;
    }
    return f;
}

double add_double(const int& n)
{
    double f = 3.3;
    for(int i = 0; i < n; i++)
    {
        f += i;
    }
    return f;
}

float mul_single(const int& n)
{
    float f = 1.0;
    for(float i = 0; i < n; i+=0.1)
    {
        f *= i;
    }
    return f;
}

double mul_double(const int& n)
{
    double f = 1.0;
    for(double i = 0; i < n; i+=0.1)
    {
        f *= i;
    }
    return f;
}

float div_single(const int& n)
{
    float f = 1.0;
    for(float i = 0; i < n; i+=0.1)
    {
        f /= i;
    }
    return f;
}

double div_double(const int& n)
{
    double f = 1.0;
    for(double i = 0; i < n; i+=0.1)
    {
        f /= i;
    }
    return f;
}

template<typename T>
long run(T(operation)(const int&), const int& nTest)
{
    auto t1 = chrono::high_resolution_clock::now();
    operation(nTest);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    return chrono::duration_cast<chrono::nanoseconds>(t2).count();
}

/*
Result of the program:

time spent after 2000000 operations
add single precision: 6403169 nanoseconds
add double precision: 6170642 nanoseconds

mul single precision: 97105994 nanoseconds
mul double precision: 50260581 nanoseconds

div single precision: 85367696 nanoseconds
div double precision: 90495442 nanoseconds

using the c++ implementation on my system
double precision data type addition and multiplication
is double as fast as for single precision data type

however, single precision slight out performed double on
division 
*/
int main()
{
    const int nTest = 2000000;

    auto t_add_single = run<float>(add_single, nTest);
    auto t_add_double = run<double>(add_double, nTest);

    auto t_mul_single = run<float>(mul_single, nTest);
    auto t_mul_double = run<double>(mul_double, nTest);

    auto t_div_single = run<float>(div_single, nTest);
    auto t_div_double = run<double>(div_double, nTest);

    cout << "time spent after " << nTest << " operations\n";

    cout << "add single precision: " << t_add_single << " nanoseconds\n";
    cout << "add double precision: " << t_add_double << " nanoseconds\n\n";

    cout << "mul single precision: " << t_mul_single << " nanoseconds\n";
    cout << "mul double precision: " << t_mul_double << " nanoseconds\n\n";

    cout << "div single precision: " << t_div_single << " nanoseconds\n";
    cout << "div double precision: " << t_div_double << " nanoseconds\n";
	return 0;
}
