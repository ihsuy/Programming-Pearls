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
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
David Gries calls this the “Coffee Can Problem”
in his Science of Programming. You are initially given
a coffee can that contains some black beans and some white
beans and a large pile of “extra” black beans. You then repeat
the following process until there is a single bean left in the can.

Randomly select two beans from the can. If they are the same
color, throw them both out and insert an extra black bean.
If they are different colors, return the white bean to the
can and throw out the black.

Prove that the process terminates. What can you say about
the color of the final remaining bean as a function
of the numbers of black and white beans originally in the can?
*/

bool CoffeeCanProblem_simulation(int nBlack_bean, int nWhite_bean)
{
    int bean_pool_size = nBlack_bean + nWhite_bean;
    while (bean_pool_size != 1)
    {
        cout << "black: " << nBlack_bean << " white: " << nWhite_bean << '\n';
        bool isBlack1 = ((rand() % bean_pool_size) < nBlack_bean);
        bool isBlack2 = ((rand() % bean_pool_size) < nBlack_bean);

        if(nWhite_bean < 2 and not isBlack1 and not isBlack2)
        {
            isBlack1 = true;
            if(nWhite_bean == 0)
            {
                isBlack2 = true;
            }
        }
        else if(nBlack_bean < 2 and isBlack1 and isBlack2)
        {
            isBlack1 = false;
            if(nBlack_bean == 0)
            {
                isBlack2 = false;
            }
        }
        
        if (not isBlack1 ^ isBlack2)
        {   // same bean
            cout << "same beans\n";
            if (isBlack1)
            {
                nBlack_bean--;
            }
            else
            {
                nWhite_bean -= 2;
                nBlack_bean++;
            }
        }
        else
        {
            cout << "different beans\n";
            nBlack_bean--;
        }

        bean_pool_size = nBlack_bean + nWhite_bean;
    }
    cout << "black: " << nBlack_bean << " white: " << nWhite_bean << '\n';
    return nBlack_bean == 1;
}
int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    CoffeeCanProblem_simulation(101, 101);

    return 0;
}
