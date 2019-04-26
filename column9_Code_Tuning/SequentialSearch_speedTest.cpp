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
try to speed up sequential search function
*/

// original sequential search function, straightforward
int ssearch1(vector<int>& nums, const int& target, const int& size)
{
    for (int i = 0; i < size; ++i)
    {
        if (nums[i] == target)
        {
            return i;
        }
    }
    return -1;
}

// 10% speed up compare to the original ssearch
// at the cost of having to modify nums
// result after applying 10000 search for 10000 different value
// in a size 10000 jumble of numbers
// ssearch1 avg func time: 12430 nano
// ssearch2 avg func time: 11021 nano
int ssearch2(vector<int>& nums, const int& target, const int& size)
{   // append the target value at the end of nums
    // so to combine the "out of bound" and "found the target"
    // 2 conditions into 1 condition
    // then apply one extra check after the loop is terminated

    // hold the size+1 value and modify it to a terminating value
    // int prev = nums[size];

    nums[size] = target;

    int i = 0;

    for (;; i++)
    {
        if (nums[i] == target)
        {   // this does 2 jobs: check "out of bound" and "found the target"
            break;
        }
    }
    
    // put the size+1 value back
    // nums[size] = prev;

    if (i == size)
    {   // for loop terminated because of out of bound?
        return -1;
    }
    // found
    return i;
}

template<typename container_type>
pair<long long, int> profiler(int(ss)(container_type, const int&, const int&),
                              container_type nums, const int& target, const int& size)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = ss(nums, target, size);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    // cout << "result: " << res << '\n';
    // cout << "func time: " << t << " nanoseconds\n";
    return {t, res};
}


int main()
{
    int sz = 10000;
    vector<int> nums;
    for (int i = 10; i < sz+10; ++i)
    {
        nums.push_back(i);
    }
    nums.push_back(0);

    shuffle(nums.begin(), nums.end(), default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count()));
    // search
    long long t1_sum = 0, t2_sum = 0;
    for (int i = 0; i < sz; ++i)
    {
        auto res1 = profiler<vector<int>&>(ssearch1, nums, i, sz);
        auto res2 = profiler<vector<int>&>(ssearch2, nums, i, sz);
        assert(res1.second == res2.second);

        t1_sum += res1.first;
        t2_sum += res2.first;
    }

    cout << "ssearch1 avg func time: " << t1_sum / sz << '\n';
    cout << "ssearch2 avg func time: " << t2_sum / sz << '\n';

    return 0;
}
