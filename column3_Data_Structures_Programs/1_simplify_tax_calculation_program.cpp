#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
As the second edition of this book goes to press,
individual income in the United States is taxed at
five different rates, the maximum of which is around
forty percent. The situation was formerly more complicated,
and more expensive. A programming text gave the following twenty-five
if statements as a reasonable approach for calculating the 1978 United
States Federal Income Tax. The rate sequence .14, .15, .16, .17, .18, ...
exhibits jumps larger than .01 later in the sequence. Any comments?

if income <= 2200
    tax = 0
else if income <= 2700
    tax =         .14 * (income – 2200)
else if income <= 3200
    tax =    70 + .15 * (income – 2700)
else if income <= 3700
    tax =   145 + .16 * (income – 3200)
else if income <= 4200
    tax =   225 + .17 * (income – 3700)
    ...
else
    tax = 53090 + .70 * (income – 102200)
*/

// if there's no gap an implementation like this will work
#define BASE_INCOME 2200
#define INCOME_GAP 500
#define BASE_TAX_RATE 0.14
#define TAX_RATE_GAP 0.01
#define INIT_TAX_GAP 70
#define INIT_TAX_GAP_GAP \
    5  // sequence: 70 75 80 85 .. which is 5(14+15+16+17...)
double CalculateTax(const double& income) {
    int income_level = 0;

    while (BASE_INCOME + income_level * INCOME_GAP < income) {
        income_level++;
    }

    if (income_level == 0) {
        return 0;
    }

    double prefix_tax = 5 * ((income_level - 1) * (28 + income_level - 2) / 2);
    double tax_percentage = BASE_TAX_RATE + TAX_RATE_GAP * (income_level - 1);
    double affix_tax =
        tax_percentage *
        (income - (BASE_INCOME + INCOME_GAP * (income_level - 1)));
    return prefix_tax + affix_tax;
}

// if there's gap and there's no patter for the the sequence
// we can store the values in multiple arrays for each coefficient in the
// formula for example base_income{2200, 2700, 3200 ...} and so on then use a
// similar approach in the method above to first decide which income level the
// input has and use that income level as the key to retrieve all the
// coefficients the calculate the result there's no complicated conditional
// statement code block exists

int main() {
    for (int income = 2000; income < 32000; income += 100) {
        printf("income: %d tax: %f\n", income, CalculateTax(income));
    }

    return 0;
}
