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
Show how to use Lomuto’s partitioning scheme to sort
varying-length bit strings in time proportional to
the sum of their lengths.
*/

vector<string> BitStringGenerator(const int& n,
                                  const int& min_len = 10,
                                  const int& max_len = 25,
                                  const int& sparsity = 3/*number of bit average that has 1 bit set*/)
{
    vector<string> bit_strings;
    for (int i = 0; i < n; ++i)
    {
        int len = rand() % max_len + min_len;
        string bs;
        bs.reserve(len);
        for (int i = 0; i < len; ++i)
        {
            if (rand() % sparsity)
            {
                bs += '1';
            }
            else
            {
                bs += '0';
            }
        }
        bit_strings.push_back(bs);
    }
    return bit_strings;
}

// I was confused by the problem statement and ended up
// writting code the task below...

// sort elements in an array of varying-length bit strings
#define SETBIT_CHAR '1'
void BitStringSort(vector<string>& bit_strings)
{
    for (int i = 0; i < bit_strings.size(); ++i)
    {
        int high = bit_strings[i].length();
        for (int h = high - 1; h >= 0; --h)
        {
            if (bit_strings[i][h] == SETBIT_CHAR)
            {
                swap(bit_strings[i][--high], bit_strings[i][h]);
            }
        }
    }
}

/*
However, after reading the solution, I realize I was
supposed to sort the whole array considering each bitstring as a number
and the code is provided below (copy from the book)
void bsort(l, u, depth)
    if 1 >= u
        return
    for i = [1, u]
        if x[i].length < depth
            swap(i, 1++)
    m = 1
    for i = [1, u]
        if x[i].bit[depth] == 0
            swap(i, m++)
    bsort(l, m-1, depth+1)
    bsort(m, u, depth+1)

“The function is originally called by bsort(0, n -l, 1). 
Beware that this program assigns values to parameters 
and to variables defining for loops. 
The linear running time depends strongly on 
the fact that the swap operation moves pointers to 
the bit strings and not the bit strings themselves.”
*/

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    auto bit_strings = BitStringGenerator(20);
    for (auto& s : bit_strings)
    {
        cout << s << '\n';
    }
    BitStringSort(bit_strings);
    cout << "after\n";
    for (auto& s : bit_strings)
    {
        cout << s << '\n';
    }
    return 0;
}
