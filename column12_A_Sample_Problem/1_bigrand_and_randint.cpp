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
The C library rand() function typically returns
about fifteen random bits. Use that function to implement
a function bigrand() to return at least 30 random bits,
and a function randint(l, u) to return a random integer
in the range [l, u].
*/

// since c++ rand() function generate 32 bit integer random numbers
// i had to trim it to create this artificial 15 bit rand function
// random number of 15 bits
const int mask15 = (1 << 15) - 1;
int rand15bit() {
    return rand() & mask15;
}

// random number of 30 bits
// create 2 15 bits rand numbers and glue them head to tail
int bigrand() {
    return rand15bit() | ((rand15bit()) << 15);
}

// the bigrand function introduced in its solution
// doesn't quit working when implemented in c++...
//
// int bigrand2()
// {
//     cout << RAND_MAX*rand15bit() << endl;
//     return (unsigned)RAND_MAX*rand15bit()+(unsigned)rand15bit();
// }

// random number from the range [l, u]
int randint(const int& l, const int& u) {
    assert(l <= u);
    return rand() % (u - l + 1) + l;
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    cout << bitset<32>(rand15bit()) << '\n';
    cout << bitset<32>(bigrand()) << '\n';
    //cout << bitset<32>(bigrand2()) << '\n';
    cout << randint(9, 10) << endl;
    return 0;
}
