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
I assigned the problem of generating sorted subsets
twice in an undergraduate course on algorithms.
Before the unit on sorting and searching,
students had to write a program for m = 20 and n = 400;
the primary grading criterion was a short, clean program
run time was not an issue. After the unit on sorting
and searching they had to solve the problem again
with m = 5,000,000 and n = 1,000,000,000, and the
grade was based primarily on run time.
*/

// clean program
// my interpretation to "clean" is that it doesn't involve
// advanced data structures and fancy library functions
const int clean_select = 20, clean_remain = 400;
vector<int> clean_randgen(int select = clean_select,
                          int remain = clean_remain)
{
    vector<int> res;
    for (int i = 0; i < remain and select > 0; ++i)
    {
        if (rand() % (remain - i) < select)
        {
            res.push_back(i);
            select--;
        }
    }
    return res;
}

// fast program
// I assume, for now, the set-based method is fast enough
// completed in 10s on my laptop
const int fast_select = 5000000, fast_remain = 1000000000;
vector<int> fast_randgen(int select = fast_select,
                         int remain = fast_remain)
{
    set<int> nums;
    while(nums.size()!=select)
    {
        nums.insert(rand()%fast_remain);
    }
    return vector<int>{nums.begin(), nums.end()};
}


int main()
{
    auto res = fast_randgen();
    //inspect<vector<int>> (res);
    return 0;
}
