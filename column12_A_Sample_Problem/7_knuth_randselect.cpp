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
Algorithms for generating combinatorial objects are
often profitably expressed as recursive functions.
Knuth’s algorithm can be written as:

void randselect(m, n)
        pre   0 <= m <= n
        post  m distinct integers from 0..n-l are
              printed in decreasing order
    if m > 0
        if (bigrand() % n) < m
            print n-1
            randselect(m-1, n-1)
        else
            randselect(m, n-1)

This program prints the random integers in decreasing order;
how could you make them appear in increasing order?
Argue the correctness of the resulting program.
How could you use the basic recursive structure of
this program to generate all m-element subsets of 0.. n – 1?
*/

// generate m random numbers from [0, n) in descending order
void randselect(const int& m, const int& n)
{
    if (m > 0)
    {
        if (rand() % n < m)
        {
            cout << (n - 1) << endl;
            randselect(m - 1, n - 1);
        }
        else
        {
            randselect(m, n - 1);
        }
    }
}
// the iterative version of the code above basically goes like
// instead of implicitly decrementing the parameters using a
// loop, the code above uses a recursion structure that calls itself
// with decremented parameters.
void randselect_iterative(int m, int n)
{
    for (int i = n - 1; i >= 0; --i)
    {
        if (rand() % (i + 1) < m)
        {
            cout << i << '\n';
            m--;
        }
    }
}

// ...in ascending order
// as I've mentioned above, the recursive code is equivalent to
// using a for loop and decrementing the paramters
// and in order to print numbers in ascending order,
// we only need to think about how to reverse the loop
void randselect2(const int& m, const int& n)
{
    if (m > 0)
    {
        if (rand() % n < m)
        {
            randselect(m - 1, n - 1);
            cout << (n - 1) << endl;
        }
        else
        {
            randselect(m, n - 1);
        }
    }
}

// How could you use the basic recursive structure of
// this program to generate all m-element subsets of 0.. n – 1?
void subsetsGen_helper(const int& m, const int& n,
                       vector<int>& subset, vector<vector<int>>& subsets)
{
    if(n<m)
    {   // no enough numbers left to complete subset of m size
        return;
    }

    if (m > 0 and n > 0)
    {   // include n at this time step or do not include
        subsetsGen_helper(m, n - 1, subset, subsets);
        subset.push_back(n);
        subsetsGen_helper(m - 1, n - 1, subset, subsets);
        subset.pop_back();
    }
    if (m == 0)
    {
        subsets.push_back(subset);
    }
}

// calculate n choose k
long long choose(const int& n, const int& k)
{
    if(k == 0)
    {
        return 1;
    }
    return n*choose(n-1, k-1)/k;
}
vector<vector<int>> subsetsGen(const int& m, const int& n)
{
    vector<vector<int>> subsets; subsets.reserve(choose(n, m));
    vector<int> subset;
    subsetsGen_helper(m, n, subset, subsets);
    return subsets;
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    randselect(10, 20);
    cout << "done" << '\n';
    randselect_iterative(10, 20);
    cout << "done" << '\n';
    randselect2(10, 20);

    auto sets = subsetsGen(5, 10);
    for (auto& s : sets)
    {
        cout << "[";
        for (auto& n : s)
        {
            cout << n << ' ';
        }
        cout << "]\n";
    }
    cout << sets.size() << endl;
    return 0;
}
