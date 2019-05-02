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
inline void inspect(T& t){typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
When m is near n, the set-based algorithm generates 
many random numbers that are discarded because they
are already present in the set. Can you find an algorithm 
that uses only m random numbers, even in the worst case?
*/

// naive set-based random set generator
vector<int> RandomSet_naive(const int& m, const int& n)
{
    set<int> s;
    while(s.size() < m)
    {
        s.insert(rand()%n);
    }
    return {s.begin(), s.end()};
}

// I understand why this code runs

vector<int> RandomSet_optimal(const int& m, const int& n)
{
    set<int> s;
    for(int j = n-m; j < n; j++)
    {
        int t = rand()%(j+1);
        if(s.count(t))
        {
            s.insert(j);
        }
        else
        {
            s.insert(t);
        }
    }
    return {s.begin(), s.end()};
}



int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
        
    vector<int> counter(20, 0);

    for (int i = 0; i < 1000000; ++i)
    {
        auto res = RandomSet_optimal(10, 20); 
        for(auto& n : res)
        {
            counter[n]++;
        }
    }
    
    inspect<vector<int>> (counter);

	return 0;
}
