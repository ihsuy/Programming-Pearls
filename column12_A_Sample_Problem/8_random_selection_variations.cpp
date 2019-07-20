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
How would you generate a random selection of m integers
from 0..n – 1 with the constraint that the final output
must appear in random order? How would you generate a
sorted list if duplicate integers were allowed in the list?
What if both duplicates and random order were desired?
*/

// in random order
vector<int> RandomOrderNumbers(const int& m, const int& n) {
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i) {
        nums.push_back(i);
    }

    // shuffle it
    for (int i = 0; i < n; ++i) {
        int idx = i + rand() % (n - i);
        auto tmp = nums[idx];
        nums[idx] = nums[i];
        nums[i] = tmp;
    }

    return vector<int>{nums.begin(), nums.begin() + m};
}

// a sorted list of random integers where duplicates are allowed
vector<int> RandomNumbersWithDuplicates(const int& m, const int& n) {
    multiset<int> nums;
    while (nums.size() < m) {
        nums.insert(rand() % n);
    }
    return vector<int>{nums.begin(), nums.end()};
}

// if both duplicates and random order were desired
vector<int> RandomOrderWithDuplicates(const int& m, const int& n) {
    vector<int> nums;
    nums.reserve(m);
    for (int i = 0; i < m; ++i) {
        nums.push_back(rand() % n);
    }
    return nums;
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    auto random_order = RandomOrderNumbers(10, 20);
    inspect<vector<int>>(random_order);
    auto random_with_dup = RandomNumbersWithDuplicates(10, 20);
    inspect<vector<int>>(random_with_dup);
    auto randomOrder_with_dup = RandomOrderWithDuplicates(10, 20);
    inspect<vector<int>>(randomOrder_with_dup);
    return 0;
}
