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
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
In the maximum subarray problem we are given an n×n array of reals,
and we must find the maximum sum contained in any rectangular subarray.
What is the complexity of this problem?
*/

struct window
{
    const string repr = "(%d, %d) height: %d, width: %d, sum: %d";

    pair<int, int> pos;

    int height;
    int width;
    int sum;

    window(): pos{0, 0}, height(0), width(0), sum(0) {}
    void update(const pair<int, int>& p, const int& h, const int& w, const int& s)
    {
        pos = p;
        height = h;
        width = w;
        sum = s;
    }
};

ostream& operator<<(ostream& os, const window& w)
{
    char* out = new char[w.repr.length()];
    sprintf(out, w.repr.c_str(), w.pos.first, w.pos.second, w.height, w.width, w.sum);
    return os << out;
}

// naive solution
// formidable 6 for loops
window maxWindow(const vector<vector<int>>& m)
{
    int n_row = m.size(), n_col = m[0].size();
    window max_window;
    // for every possible window size
    for (int r = 1; r <= n_row; ++r)
    {
        for (int c = 1; c <= n_col; ++c)
        {   // move window to every possible position
            for (int wr = 0; wr < n_row - r + 1; ++wr)
            {
                for (int wc = 0; wc < n_col - c + 1; ++wc)
                {   // calculate sum of the window
                    int window_sum = 0;
                    for (int i = wr; i < wr + r; ++i)
                    {
                        for (int j = wc; j < wc + c; ++j)
                        {
                            window_sum += m[i][j];
                        }
                    }
                    if (window_sum > max_window.sum)
                    {
                        max_window.update({wr, wc}, r, c, window_sum);
                    }
                }
            }
        }
    }
    return max_window;
}

int main()
{
    vector<vector<int>> m
    {
        { -1,  1,  2,  3},
        { 2, -2,  3, -1},
        { 0,  2,  1,  1},
        { 1,  2, -3,  -4}
    };

    cout << maxWindow(m) << '\n';

    return 0;
}
