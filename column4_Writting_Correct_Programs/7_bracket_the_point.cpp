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
A colleague faced the following problem in a program
to draw lines on a bitmapped display.
An array of n pairs of reals (ai,bi) defined the n lines yi = aix + bi.
The lines were ordered in the x-interval [0,1] in the sense
that yi < yi+1 for all values of i between 0 and n – 2
and all values of x in [0,1]
Less formally, the lines don’t touch in the vertical slab.
Given a point (x,y), where 0≤x≤1, he wanted to determine
the two lines that bracket the point. How could he solve
the problem quickly?
*/

// linear function y = a*x+b find y given a x b
double linear(const double& a, const double& x, const double& b)
{
    return a * x + b;
}

// solve the problem states above using binary search
pair<pair<double, double>, pair<double, double>>
        BracketThePoint(const vector<pair<double, double>>& lines,
                        const pair<double, double>& point)
{
    int low = 0, high = lines.size() - 1;
    // loop until low and high are next to each other
    // our invariant is that if "point" is on a line in lines,
    // that line must be between low and high
    // when low and high (two lines) are adjacent, we know
    // there are no more lines in between
    // then lines[low] and lines[high] are indeed the lines
    // that brackets the "point"
    while (high - low > 1)
    {
        int mid = (low + high) / 2;
        double a = lines[mid].first;
        double b = lines[mid].second;
        double y = linear(a, point.first, b);

        if (y == point.second)
        {   // "point" is on lines[mid], then return that line
            // and any one of two lines next to it

            // but be careful if mid is a boundary value
            if ((mid == 0 and mid != lines.size() - 1)
                    or (mid != lines.size() - 1 and mid != 0))
            {   
                return {lines[mid], lines[mid + 1]}
            }
            else if (mid == lines.size() - 1 and mid != 0)
            {
                return {lines[mid - 1], lines[mid]}
            }
            else
            {   // there's only 1 line in lines, then no answer
                throw runtime_error("no answer exists");
            }
        }

        if (y < point.second)
        {   // point is higher than current line mid, 
            // search in higher lines
            low = mid + 1;
        }
        else
        {   
            high = mid - 1;
        }
    }
    return {lines[low], lines[high]};
}

int main()
{


    return 0;
}
