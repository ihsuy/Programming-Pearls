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
Use the techniques of this column to implement other
sorting algorithms. Selection sort first places the
smallest value in x[0], then the smallest remaining
value in x[1], and so forth. Shell sort (or “diminishing
increment sort”) is like Insertion Sort, but moves
elements down h positions rather than just one position.
The value of h starts large, and shrinks.
*/

/*
Not sure what's the exact definition of ShellSort
but only implemented following the hint:
"like Insertion Sort, but moves elements down h positions 
rather than just one position.
"*/
void ShellSort(vector<int>& nums)
{
    int nums_len = nums.size();
    for (int step = nums_len / 2; step > 0;  step >>= 1)
    {
        for (int i = step; i < nums_len; i += step)
        {
            for (int j = i; j >= step and nums[j - step] > nums[j]; j -= step)
            {
                swap(nums[j - step], nums[j]);
            }
        }
    }

}

const size_t rand_upper_bound = 10;
vector<int> RandomVector(const size_t& n)
{
    vector<int> nums;
    nums.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        nums.push_back(rand() % rand_upper_bound);
    }
    return nums;
}

int main()
{
    // const int& vec_size = 20;
    // auto nums = RandomVector(vec_size);
    // inspect<vector<int>>(nums);
    // ShellSort(nums);
    // inspect<vector<int>>(nums);
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int i = 0; i < 1000; ++i)
    {
        vector<int> nums;
        for (int j = 0; j < 100; ++j)
        {
            nums.push_back(rand() % 100);
        }
        vector<int> cp = nums;
        sort(cp.begin(), cp.end());
        ShellSort(nums);
        assert(cp == nums);
        //cout << "good\n";
    }
    return 0;
}
