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

// naive brute force solution
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

// improved brute force solution
// doesn't re-calculate the window sum from scratch
// but subtract the removed part and add the new part of the window
window maxWindow2(const vector<vector<int>>& m)
{
    int n_row = m.size(), n_col = m[0].size();

    window max_window;
    // for every possible window size
    for (int r = 1; r <= n_row; ++r)
    {
        for (int c = 1; c <= n_col; ++c)
        {   // move window to every possible position
            // calculate initial sum of the window
            int window_sum = 0;
            for (int i = 0; i < r; ++i)
            {
                for (int j = 0; j < c; ++j)
                {
                    window_sum += m[i][j];
                }
            }

            for (int wr = 0; wr < n_row - r + 1; ++wr)
            {
                int pre_window = window_sum;

                for (int wc = 0; wc < n_col - c + 1; ++wc)
                {
                    if (window_sum > max_window.sum)
                    {
                        max_window.update({wr, wc}, r, c, window_sum);
                    }
                    if (wc != n_col - c)
                    {   // substract first column from window
                        // (how: iterate vertically alone rows)
                        int col_remove = 0;
                        for (int i = 0; i < r; ++i)
                        {
                            col_remove += m[wr + i][wc];
                        }
                        window_sum -= col_remove;
                        // add next column of window
                        int col_add = 0;
                        for (int i = 0; i < r; ++i)
                        {
                            col_add += m[wr + i][wc + c];
                        }
                        window_sum += col_add;
                    }
                }
                // reset window to left most position
                window_sum = pre_window;

                if (wr != n_row - r)
                {   // substract first row from the initial window
                    int row_remove = 0;
                    for (int i = 0; i < c; ++i)
                    {
                        row_remove += m[wr][i];
                    }
                    window_sum -= row_remove;

                    // add the new row to the initial window
                    int row_add = 0;
                    for (int i = 0; i < c; ++i)
                    {
                        row_add += m[wr + r][i];
                    }
                    window_sum += row_add;
                }
            }
        }
    }
    return max_window;
}

// an improved version on maxWindow2
// which reduced redundant logic
// and improved speed for calculating
// sum of the leftmost initial window
window maxWindow3(const vector<vector<int>>& m)
{
    int n_row = m.size(), n_col = m[0].size();

    window max_window;

    vector<vector<int>> initial_sums{m.size() + 1, vector<int>(m[0].size(), 0)};

    // for every possible window size
    for (int r = 1; r <= n_row; ++r)
    {
        initial_sums[r][0] = initial_sums[r - 1][0] + m[r - 1][0];
        for (int i = 1; i < initial_sums[0].size(); ++i)
        {
            initial_sums[r][i] = m[r - 1][i]
                                 + initial_sums[r - 1][i]
                                 + initial_sums[r][i - 1]
                                 - initial_sums[r - 1][i - 1];
        }

        for (int c = 1; c <= n_col; ++c)
        {   // move window to every possible position
            // and calculate initial sum of the window
            int window_sum = initial_sums[r][c - 1];

            for (int wr = 0; wr < n_row - r + 1; ++wr)
            {
                int pre_window = window_sum;

                for (int wc = 0; wc < n_col - c + 1; ++wc)
                {
                    if (window_sum > max_window.sum)
                    {
                        max_window.update({wr, wc}, r, c, window_sum);
                    }

                    if (wc != n_col - c)
                    {   // substract first column from window
                        // add next column of window
                        for (int i = 0; i < r; ++i)
                        {
                            window_sum -= m[wr + i][wc] - m[wr + i][wc + c];

                        }
                    }
                }
                // reset window to left most position
                window_sum = pre_window;

                if (wr != n_row - r)
                {   // substract first row from the initial window
                    for (int i = 0; i < c; ++i)
                    {
                        window_sum -= m[wr][i] -  m[wr + r][i];
                    }
                }
            }
        }
    }
    return max_window;
}

vector<vector<int>> TestCaseGenerator(const int& h, const int& w, const int& n)
{
    vector<vector<int>> test_case;
    for (int r = 0; r < h; ++r)
    {
        vector<int> row;
        for (int c = 0; c < w; ++c)
        {
            row.push_back(rand() % n - n / 2);
        }
        test_case.push_back(row);
    }
    return test_case;
}

void run(window(f)(const vector<vector<int>>&), const vector<vector<int>>& m)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = f(m);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::microseconds>(t2).count();
    cout << "------------\n";
    cout << "result: " << res << '\n';
    printf("time spent: %lld microseconds\n", t);
    cout << "------------\n";
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int h = 40;
    const int w = 60;
    const int n = 100;
    auto m = TestCaseGenerator(h, w, n);

    run(maxWindow, m);
    run(maxWindow2, m);
    run(maxWindow3, m);

    /*
    test result: 
    
    ------------
    maxWindow
    result: (8, 1) height: 26, width: 17, sum: 1179
    time spent: 2072725 microseconds
    ------------

    ------------
    maxWindow2
    result: (8, 1) height: 26, width: 17, sum: 1179
    time spent: 214410 microseconds
    ------------
    
    ------------
    maxWindow3
    result: (8, 1) height: 26, width: 17, sum: 1179
    time spent: 189274 microseconds
    ------------
    */
    return 0;
}

