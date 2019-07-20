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
Prove that this program terminates when its input x is a positive integer.
while x != 1 do
    if even(x)
        x = x/2
    else
        x = 3*x+1

*/

// not sure how to prove this
// this is an well known open problem
// please check the jupyter note book in this repository
// for some visualization
void simulate(int n) {
    int i = n;
    int step = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        step++;
    }
    cout << "number: " << i << " step: " << step << "\n";
}

int main() {
    for (int i = 1; i < 1000; ++i) {
        simulate(i);
    }

    return 0;
}
