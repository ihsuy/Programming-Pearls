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
Counting the member tests in the set-based program leads
to many interesting problems in combinatorics and probability theory.
How many member tests does the program make on the average as
a function of m and n?
How many does it make when m = n?
When is it likely to make more than m tests?
*/

// the set-based program
vector<int> RandomSelect(const int& select, const int& remain, int& counter)
{
    set<int> nums;
    while (nums.size() < select)
    {
        nums.insert(rand() % remain);
        counter++;
    }
    return vector<int> {nums.begin(), nums.end()};
}

// I provided a test program that creates a 2d tensor
// where its 1st dimention represent the value of n (remain) 
// and its 2nd dimention represent the value of m (select)
// if interested, the parameters can be modified and the result 
// matrix could be exported and can be plot in 3d using ploting libraries
// for example Plotly and etc.
const int select_lower = 1;
const int select_upper = 100;
const int remain_lower = select_upper;
const int remain_upper = 300;
vector<vector<int>> test()
{
    vector<vector<int>> records(remain_upper - remain_lower + 1,
                                vector<int>(select_upper - select_lower + 1, 0));
    for (int remain = remain_lower; remain <= remain_upper; ++remain)
    {
        int remain_i = remain - remain_lower;
        for (int select = select_lower; select <= select_upper; ++select)
        {
            int select_i = select - select_lower;
            RandomSelect(select, remain, records[remain_i][select_i]);
        }
    }
    return records;
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    auto records = test();

    for (int i = 0; i < records.size(); ++i)
    {
        cout << "remain: " << remain_lower + i << '\n';
        for (int j = 0; j < records[i].size(); ++j)
        {
            cout << records[i][j] << ',';
        }
        cout << '\n';
    }

    return 0;
}
