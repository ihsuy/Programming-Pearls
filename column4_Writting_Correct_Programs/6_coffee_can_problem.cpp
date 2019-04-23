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

// simulate the process described in this problem
// return value indicates the color of the last bean
// true: black ; false: white
// analysis for why this program terminates will be after
// the code
bool CoffeeCanProblem_simulation(int nBlack_bean, int nWhite_bean)
{
    int bean_pool_size = nBlack_bean + nWhite_bean;
    while (bean_pool_size != 1)
    {
        bool isBlack1 = ((rand() % bean_pool_size) < nBlack_bean);
        bool isBlack2 = ((rand() % bean_pool_size) < nBlack_bean);

        if (nWhite_bean < 2 and not isBlack1 and not isBlack2)
        {   // when there're fewer than 2 white beans left
            // we can't draw 2 white beans, so one of them has
            // to be black
            isBlack1 = true;
            if (nWhite_bean == 0)
            {   // if there was no white beans at all
                // then we can only choose black beans
                // Note: we know that we have at least 2 black beans left
                // at this point, because the while loop condition
                isBlack2 = true;
            }
        }
        else if (nBlack_bean < 2 and isBlack1 and isBlack2)
        {   // similar to above
            isBlack1 = false;
            if (nBlack_bean == 0)
            {
                isBlack2 = false;
            }
        }

        if (not isBlack1 ^ isBlack2)
        {   // same bean
            if (isBlack1)
            {
                cout << "Two black beans, throw 2 black beans and add 1 black bean\n";
                nBlack_bean--;
            }
            else
            {
                cout << "Two white beans, throw 2 white beans and add 1 black bean\n";
                nWhite_bean -= 2;
                nBlack_bean++;
            }
        }
        else
        {
            cout << "different beans, throw black bean and return white bean\n";
            nBlack_bean--;
        }

        bean_pool_size = nBlack_bean + nWhite_bean;
    }
    cout << "black: " << nBlack_bean << " white: " << nWhite_bean << '\n';
    return nBlack_bean == 1;
}
// Review of the process:
// Randomly select two beans from the can. If they are the same
// color, throw them both out and insert an extra black bean.
// If they are different colors, return the white bean to the
// can and throw out the black.

// Note the termination will happen when there's only 1 bean left in the can
// that means, we want to carefully inspect how this process throw out our beans

// First, let's look at what happens to white beans.
// note that there're only 1 cases when white beans are removed,
// namely, when we draw 2 white beans together. this will cause both of them
// to be removed. This is a huge hint, since the number of white beans can only
// decrease by even number, if we had an odd number of white beans in the can
// then we will absolutely have at least 1 white bean left doesn't
// matters what happens.

// Next, let's look at Black beans. Notice that, black beans are always removed
// except when 2 white beans are drew together which, however, will add 1 black
// bean back. in all other cases i.e. When we draw 2 black beans or
// 1 white 1 black, in total, only 1 black bean will be removed.
// note that, there are only 3 possiblilties for drawing 2 beans
// (white, black) (white, white) (black, black), all of them will result in
// a decrease of the total number of beans in the can by 1

// now we know,
// 1. each step in the process will decrease number of black beans by at most 1
// 2. if we are to throw out white beans, we always throw 2 together
// 3. every step (if there're enough beans left),
//    total number of beans in the can will decrease by 1

// after knowing 3, we are confident that total number of beans left will
// always be reduced to 0 or 1 (if we don't have 2 beans left at the end).
// and now we prove it will only be reduced to 1

// since to remove white beans, we don't need any information about black beans
// but only to know we had at least 2 white beans left,
// we can isolate this process:
// for initial number of white beans in the can, it can only be either odd or
// even
// when its odd, the number of white beans will be reduced to 1 and no further
// when its even, the number of white beans will be reduced to 0
// note: both of the cases produce nWhite_beans/2 black beans

// for black beans
// when total number of black beans in the can (initial + later produced) is
// odd or even(non zero), we are always left with 1 black beans
// because when current number of black beans is even, we do nBlack_bean/2
// and otherwise nBlack_bean/2 +1, this will reduce any positive integer to 1

// so now we know this process will always reach at the point
// 1 black bean, 0 or 1 white bean
// i.e. case 1(black, white) or case2(black, none)
// the first case will yield after one step (none, white) and terminates
// and the second case terminates directly
// therefore this process will always terminate

// 1. (black, none) 2. (none, white)
// 1 will happen whenever number of white is even (include 0)
// 2 will happen whenever number of white is odd
int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    CoffeeCanProblem_simulation(56, 7);

    return 0;
}
