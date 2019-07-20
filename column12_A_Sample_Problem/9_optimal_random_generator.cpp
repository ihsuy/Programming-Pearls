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
When m is near n, the set-based algorithm generates
many random numbers that are discarded because they
are already present in the set. Can you find an algorithm
that uses only m random numbers, even in the worst case?
*/

// naive set-based random set generator
vector<int> RandomSet_naive(const int& m, const int& n) {
    set<int> s;
    while (s.size() < m) {
        s.insert(rand() % n);
    }
    return {s.begin(), s.end()};
}

// First let's define the denotation. Let
// rand{a,b} be a random variable following
// the discrete uniform distribution over the set {a, a+1, ..., b-1, b}.
// This algorithm can be better understood if an example is provided
// let m = 5 and n = 10, we know
// j ∈ [5,6,7,8,9]
// and thus t ∈ [rand{0,5}, rand{0,6}, rand{0,7}, rand{0,8}, {0,9}]
// Let's look at what happens in every step
// First, when the set s is empty, whatever value t is chosen from {0,5},
// will be inserted in to s.
// Why? isn't this a bias toward certain set of numbers?
// Not really, because we only have 10 numbers, and if we don't choose any
// number from 0-5, we are only left with 4 available numbers!
// it's impossible to form a subset of size 5.
// Thus we choose the first element with probability equal to 1/5
// the first step was legit, let's continue.

// Next will happen is that we're getting the number rand{0, 6} when j = 6
// now note that we have 2 chances to pick 6, namely when we select the number
// that we selected previously, or we select 6 itself.
// and for 7 we have 3 chances, and 6 also get another chance...

// After carefully examining the whole process, its not hard to find that
// every number had 5 chances to be selected.
vector<int> RandomSet_optimal(const int& m, const int& n) {
    set<int> s;
    for (int j = n - m; j < n; j++) {
        int t = rand() % (j + 1);
        if (s.count(t)) {
            s.insert(j);
        } else {
            s.insert(t);
        }
    }
    return {s.begin(), s.end()};
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    vector<int> counter(20, 0);

    for (int i = 0; i < 1000000; ++i) {
        auto res = RandomSet_optimal(10, 20);
        for (auto& n : res) {
            counter[n]++;
        }
    }

    inspect<vector<int>>(counter);

    return 0;
}
