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
Modify siftdown to have the following specification.
void siftdown(l, u)
        pre   heap(l+1, u)
        post  heap(l, u)

What is the run time of the code? Show how it can be used to
construct an n-element heap in O(n) time and thereby a faster
Heapsort that also uses less code.
*/

void siftdown0_min(int* nums, const int& n)
{
    int i = 1;
    auto temp = nums[i];
    for (int j = i; (j *= 2) <= n; i = j)
    {
        if (j + 1 <= n and nums[j + 1] < nums[j])
        {
            j++;
        }
        if (nums[j] >= temp)
        {
            break;
        }
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void siftdown_min(int* nums, const int& l, const int& u)
{
    int i = l;
    auto temp = nums[l];
    for (int j = i; (j *= 2) <= u; i = j)
    {
        if (j + 1 <= u and nums[j + 1] < nums[j])
        {
            j++;
        }
        if (nums[j] >= temp)
        {
            break;
        }
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void siftup_min(int* nums, const int& n)
{
    int i = n;
    auto temp = nums[n];
    for (int j = i; i > 1 and nums[j /= 2] > temp; i = j)
    {
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void HeapSort1(int* nums, const int& size)
{   // build the heap
    for (int i = 1; i <= size; ++i)
    {
        siftup_min(nums, i);
    }
    // build array
    for (int i = size; i > 1; --i)
    {
        swap(nums[1], nums[i]);
        siftdown0_min(nums, i-1);
    }
}

void HeapSort2(int* nums, const int& size)
{   // build the heap
    for (int i = size / 2; i >= 1; --i)
    {
        siftdown_min(nums, i, size);
    }
    // build array
    for (int i = size; i > 1; --i)
    {
        auto temp = nums[1];
        nums[1] = nums[i];
        nums[i]=temp;
        siftdown_min(nums, 1, i-1);
    }
}

int main()
{
    int nums[11] = {0, 0, 1, 2, 3, 4, 5, 6, 7, 9, 1};
    //siftdown(nums, 2, 10);
    // siftup(nums, 10);
    HeapSort2(nums, 10);
    for (int i = 1; i < 11; ++i)
    {
        cout << nums[i] << ' ';
    }
    cout << '\n';

    return 0;
}
