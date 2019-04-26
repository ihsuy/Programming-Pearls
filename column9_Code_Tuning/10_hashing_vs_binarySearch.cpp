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
D. B. Lomet observes that hashing may solve the 1000-integer
search problem more efficiently than the tuned binary search.
Implement a fast hashing program and compare it to the tuned
binary search; how do they compare in terms of
speed and space?
*/

int binarySearch(const vector<int>& nums, const int& target)
{
    int low = 0;
    int i = (nums.size() - 1) >> 1;
    for (; i > 0; i >>= 1)
    {
        cout << i << '\n';
        cout << "n: " << nums[low + i] << " low: " << low <<  '\n';
        if (nums[low + i] < target)
        {
            low = low + i + 1;
        }
    }

    if (low < nums.size() and nums[low] == target)
    {
        return low;
    }
    else if(nums[low+1] == target)
    {
        return low+1;
    }

    return -1;
}

unordered_map<int, int> locations;
int hashingSearch(const vector<int>& nums, const int& target)
{
    if (locations.empty())
    {
        locations[nums[0]] = 0;
        int sz = nums.size();
        for (int i = 1; i < sz; ++i)
        {
            if (nums[i] != nums[i - 1])
            {
                locations[nums[i]] = i;
            }
        }
    }

    return locations.count(target) ? locations[target] : -1;
}

int main()
{
    // create test vector
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    const int sz = 100;
    const int n_lower = -sz / 10;
    vector<int> nums;

    for (int i = 0, n = n_lower; i < sz; ++i)
    {
        if (rand() % 2)
        {
            n++;
        }
        // if (rand() % 4)
        // {   // occasionally introduce big gaps
        //     n += 1000;
        // }
        nums.push_back(n);
    }
    assert(nums.size() == sz);
    //vector<int> nums {0 , 1 , 2 , 2 , 3 , 3 , 4 , 4, 4 , 4};
    inspect<vector<int>>(nums);

    int tar = rand() % (sz + sz / 3) - sz / 5;
    //int tar = 4;
    cout << "tar: " << tar << '\n';
    auto res1 = binarySearch(nums, tar);
    auto res2 = hashingSearch(nums, tar);
    assert(res1 == -1 or nums[res1] == tar);
    assert(res1 == -1 or nums[res2] == tar);
    assert(res1 == res2);
    cout << res1 << " " <<  res2 << '\n';
    return 0;
}
