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
Like any other powerful tool, sorting is often used when
it shouldn’t be and not used when it should be.
Explain how sorting could be overused or underused
when calculating the following statistics of
an array of n floating point numbers:
minimum, maximum, mean, median and mode.
*/

// Finding Minimum
// would only require a function like code below
// which runs in O(N) where N is the size of the input array.
// We absolutely should not apply Sorting to solve this problem:
// We could, of course, do something like this:
// sort(nums)
// return nums[0]
//
// To find the smallest is equivalent to
// putting 1 element to its correct position,
// or say "to sort 1 element".
// However, if we sort the array as we did above
// then we actually sorted N element just for completing the job
// to sort 1 element which is highly inefficient
// and our runtime indeed raised from strictly O(N) to at least O(NlogN)
double MinimumElement(vector<double>& nums)
{
    double min_val = nums[0];
    int nums_len = nums.size();
    nums.push_back(nums[0]);

    for (int i = 1; i < nums_len; ++i)
    {
        while (nums[i] > min_val)
        {
            ++i;
        }
        min_val = nums.back() = nums[i];
    }
    nums.pop_back();
    return min_val;
}

// Finding Maximum
// We can apply identical logic as in the explaination for finding
// the minimum, and conclude that there's absolutely no need to sort

// Finding mean
// naive approach doesn't involve sorting:
// simply add up everything and divide by size
double GetMean(const vector<double>& nums)
{
    return accumulate(nums.begin(), nums.end(), 0.0) / nums.size();
}

// Find median
// naive approach:
// sort the array and return the center element 
// or the avg of the center 2 elements when array is of even size
// I know a better aproach that involves binary search but
// its seems that this problem wil show up again later in the problems
// I'll wait until then

// Find Mode
// naive approach doesn't use sort:
// interatively count occurence for each element in the array
// and store the maximum occured element
// this algorithm runs in O(n^2)

// naive approach that uses sort:
// first sort the array, then all identical elements will be
// group together, we then only need to interate the sorted array
// once to find the maximum ocurring element. O(nlogn) will do

// An alternative method that uses more space but the fastest will be 
// to use a hashtable or an array of counter to count the 
// occurence of each element in one run, 
// and this will run in O(N) and uses O(N) space

double GetMode(const vector<double>& nums)
{
    unordered_map<double, int> counters;
    int nums_len = nums.size();
    for(int i = 0; i < nums_len; ++i)
    {
        if(counters.count(nums[i])==0)
        {
            counters[nums[i]] = 1;
        }
        else
        {
            counters[nums[i]]++;
        }
    }
    double mode = 0;
    int max_count = 0;    
    for(auto& item: counters)
    {
        if(item.second > max_count)
        {
            max_count = item.second;
            mode = item.first;
        }
    }
    return mode;
}

const int& array_value_upper = 20;
vector<double> GenerateArray(const int& n)
{
    vector<double> nums;
    for (int i = 0 ; i < n; ++i)
    {
        //auto num = double(rand() % (array_value_upper)) / 10;
        auto num = double(rand() % (array_value_upper));
        nums.push_back(num);
    }
    return nums;
}

double epsilon = 0.0001;
int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    auto nums = GenerateArray(20);
    inspect<vector<double>> (nums);
    auto min_ele = MinimumElement(nums);
    assert(min_ele - *min_element(nums.begin(), nums.end()) < epsilon);
    cout << "min : " << min_ele << '\n';
    cout << "mean: " << GetMean(nums) << '\n';
    cout << "mode: " << GetMode(nums) << '\n';
    return 0;
}
