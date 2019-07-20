#include <math.h>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
/////////////////////////////////////////////////////////////
using namespace std;

/*
Write and prove the correctness of a recursive binary search
function in C or C++ with this declaration:

int binarysearch(DataType x[], int n)

Use this function alone; do not call any other recursive functions.
*/

// recursive function that doesn't depend on any other function
int binarysearch(const vector<int>& x, const int& n) {
    // static variable that keeps track of the real
    // begin position of the original input vector
    // as we are going to trim it
    static int begin_pos = 0;

    if (x.empty()) {
        begin_pos = 0;
        return -1;
    }

    int low = 0, high = x.size() - 1;
    int mid = (low + high) / 2;

    if (x[mid] == n) {  // note: return the "true index", not the relative index
        // in the current x since it may have been trimmed
        int res = mid + begin_pos;
        begin_pos = 0;
        return res;
    }

    if (x[mid] < n) {  // if n is on the second half of x
        // the begin_pos should be moved forward
        begin_pos += mid + 1;
        return binarysearch(vector<int>{x.begin() + mid + 1, x.end()}, n);
    } else {
        return binarysearch(vector<int>{x.begin(), x.begin() + mid}, n);
    }
}

/*
comment

This is pretty much the same problem, but with a tricky declaration restriction
I tackle this problem using a static variable and use a trimmed version of the
current array as the input array feed to the next recursion.

I could, as well, use couple of global variables to keep track of low and high,
but that approach would have been equavalent to adding more parameters to the
function which makes this problem less interesting.

a static variable, however, exists inside of the function and belongs to it
i guess i can use it
*/

int main() {
    vector<int> v{2, 2, 3, 5, 6, 7, 8, 12, 129};
    for (int i = -2; i < 13; ++i) {
        cout << "found " << i << " at: " << binarysearch(v, i) << '\n';
    }
    return 0;
}
