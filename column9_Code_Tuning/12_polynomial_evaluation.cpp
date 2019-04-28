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
One sometimes tunes programs by thinking about mathematics rather than code.
To evaluate the polynomial
y = anxn + an–1xn –1 + ... + a1x1 + a0

the following code uses 2n multiplications. Give a faster function.
y = a[0]
xi = 1
for i = [1, n]
    xi = x * xi
    y = y + a[i]*xi
*/

// naive approach
double PolynomialEvaluation1(const vector<double>& coefficients,
                             const double& x)
{
    double result = coefficients[0];
    double current_x = 1;
    auto nCoefficients = coefficients.size();
    for (int i = 1; i < nCoefficients; ++i)
    {
        current_x *= x;
        result += coefficients[i] * current_x;
    }

    return result;
}

// known as Hornor's method
// refactor polynomial before multiplying and 
// reduces its number of multiplication by factor of 2
// i.e. 4*x^4 + 3*x^3 + 2*x^2 + x + 1
// if evaluated using the first method, will require 8 multiplications
// however, if we knew the ploynomial can be transformed into
//      x*(x*(x*(x*(4)+3)+2)+1)+1
// we only need 4 multiplications, bravo
double PolynomialEvaluation2(const vector<double>& coefficients,
                             const double& x)
{
    double result = 0.0;

    auto nCoefficients = coefficients.size();
    for (int i = nCoefficients - 1; i >= 0; --i)
    {
        result = result * x + coefficients[i];
    }
    return result;
}

pair<long long, double> profiler
(double(pe)(const vector<double>&, const double& x),
 vector<double>& coefficients, const double& x)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = pe(coefficients, x);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    int nCoefficients = 10000;
    vector<double> coefficients;
    coefficients.reserve(nCoefficients);

    for (int i = 0; i < nCoefficients; ++i)
    {
        coefficients.push_back((double)(rand() % 10) / 100);
    }

    double error_epsilon = 0.0001;

    const double x = 0.88;
    auto res1 = profiler(PolynomialEvaluation1, coefficients, x);
    auto res2 = profiler(PolynomialEvaluation2, coefficients, x);

    assert(abs(res1.second - res2.second) < error_epsilon);

    cout << "method 1 result: " << res1.second
         << " time spent: " << res1.first << '\n';
    cout << "method 2 result: " << res2.second
         << " time spent: " << res2.first << '\n';
    return 0;
}
