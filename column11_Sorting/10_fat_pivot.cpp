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
Write a “fat pivot” partitioning function with the postcondition
*--------*--------*--------*
|   <t   |  ==t   |   >t   |
*--------*--------*--------*
How would you incorporate the function into a Quicksort program?
*/

pair<int, int> FatPivotPartition(vector<int>& nums,
                                 const int& low, const int& high)
{
    int pivot = nums[low];
    int p_left = low, p_right = low;

    for (int i = low + 1; i <= high;++i)
    {
        if (nums[i] < pivot)
        {
            swap(nums[++p_left], nums[i]);
            swap(nums[++p_right], nums[i]);
        }
        else if (nums[i] == pivot)
        {
            swap(nums[++p_right], nums[i]);
        }
    }
    swap(nums[low], nums[p_left]);
    return {p_left, p_right};
}

int main()
{
    vector<int> nums {3, 2, 1, 0, 3, 3, 9, 4, 3, 0, 7, 8, 3, 1, 3};
    FatPivotPartition(nums, 0, nums.size()-1);
    inspect<vector<int>>(nums);

    return 0;
}
