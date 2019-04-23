#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <math.h>
/////////////////////////////////////////////////////////////
using namespace std;

/*
Write and prove the correctness of a recursive binary search
function in C or C++ with this declaration:

int binarysearch(DataType x[], int n)

Use this function alone; do not call any other recursive functions.
*/

// recursive function that doesn't depend on any other function
int binarysearch(const vector<int>& x, const int& n)
{
    // static variable that keeps track of the real
    // begin position of the original input vector
    // as we are going to trim it
    static int begin_pos = 0;

    if (x.empty())
    {    
        begin_pos = 0;
        return -1;
    }

    int low = 0, high = x.size() - 1;
    int mid = (low + high) / 2;

    if (x[mid] == n)
    {   // note: return the "true index", not the relative index
        // in the current x since it may have been trimmed
        int res = mid + begin_pos;
        begin_pos = 0;
        return res;
    }

    if (x[mid] < n)
    {   // if n is on the second half of x
        // the begin_pos should be moved forward
        begin_pos += mid + 1;
        return binarysearch(vector<int> {x.begin() + mid + 1, x.end()}, n);
    }
    else
    {
        return binarysearch(vector<int> {x.begin(), x.begin() + mid}, n);
    }
}

int main()
{
    vector<int> v{2, 2, 3, 5, 6, 7, 8, 12, 129};
    for (int i = -2; i < 13; ++i)
    {
        cout << "found " << i << " at: " << binarysearch(v, i) << '\n';
    }

    return 0;
}
