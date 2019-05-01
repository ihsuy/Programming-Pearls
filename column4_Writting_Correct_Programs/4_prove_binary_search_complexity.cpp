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
Add fictitious “timing variables” to your binary search program
to count the number of comparisons it makes,
and use program verification techniques to prove
that its run time is indeed logarithmic.
*/

int BinarySearch(const vector<int>& nums, const int& val, int& comparison_counter)
{
    int low = 0, high = nums.size() - 1;

    while (low <= high)
    {
        long long mid = (low + high) / 2;

        comparison_counter++;

        if (nums[mid] == val)
        {
            return mid;
        }

        if (nums[mid] > val)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    return -1;
}

vector<int> test_array;
// to avoid creating new array
// continue inserting element
// from where it left in the previous test
int prev_end = 0;
int prev_num = 0;

void GenerateSortedArray(const int& array_size)
{
    int i = prev_end, num = prev_num;
    for (; i < array_size; ++i)
    {
        if (rand() & 1)
        {
            num++;
        }

        test_array.push_back(num);
    }
    prev_end = i;
    prev_num = num;
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int& nTest = 30;
    const int& init_size = 2;

    vector<int> comparisons;
    vector<double> log_values;

    int size = init_size;
    test_array.reserve(1 << nTest);

    for (int i = 0; i < nTest; ++i)
    {
        cout << "<<<<<<<< TEST #" << i + 1 << " <<<<<<<<\n";
        cout << "creating sorted array with " << size << " elements\n";

        GenerateSortedArray(size);

        int target = rand() % size;
        int comparison_counter = 0;

        cout << "searching " << target << "...\n";
        auto res = BinarySearch(test_array, rand() % size, comparison_counter);
        cout << (res == -1 ? "not found" : "found")
             << " after " << comparison_counter << " comparisons\n";

        comparisons.push_back(comparison_counter);
        log_values.push_back(log(size));
        size <<= 1;
        cout << "<<<<<<<< END <<<<<<<<\n";
    }

    for (int i = 0; i < comparisons.size(); ++i)
    {
        cout << "comparisons: " << comparisons[i] << " log: " << log_values[i]
             << " comparisons/log: " << ((double)comparisons[i] / log_values[i])
             << '\n';
    }

    /*
    TEST (nTest = 30) RESULT: 
    comparisons: 1  log: 0.69314 comparisons/log: 1.4427
    comparisons: 2  log: 1.38629 comparisons/log: 1.4427
    comparisons: 3  log: 2.07944 comparisons/log: 1.4427
    comparisons: 3  log: 2.77259 comparisons/log: 1.08202
    comparisons: 6  log: 3.46574 comparisons/log: 1.73123
    comparisons: 7  log: 4.15888 comparisons/log: 1.68314
    comparisons: 4  log: 4.85203 comparisons/log: 0.824397
    comparisons: 9  log: 5.54518 comparisons/log: 1.62303
    comparisons: 8  log: 6.23832 comparisons/log: 1.2824
    comparisons: 9  log: 6.93147 comparisons/log: 1.29843
    comparisons: 9  log: 7.62462 comparisons/log: 1.18039
    comparisons: 8  log: 8.31777 comparisons/log: 0.961797
    comparisons: 12 log: 9.01091 comparisons/log: 1.33172
    comparisons: 13 log: 9.70406 comparisons/log: 1.33965
    comparisons: 15 log: 10.3972 comparisons/log: 1.4427
    comparisons: 15 log: 11.0904 comparisons/log: 1.35253
    comparisons: 18 log: 11.7835 comparisons/log: 1.52756
    comparisons: 19 log: 12.4766 comparisons/log: 1.52284
    comparisons: 17 log: 13.1698 comparisons/log: 1.29083
    comparisons: 15 log: 13.8629 comparisons/log: 1.08202
    comparisons: 22 log: 14.5561 comparisons/log: 1.51139
    comparisons: 23 log: 15.2492 comparisons/log: 1.50827
    comparisons: 24 log: 15.9424 comparisons/log: 1.50542
    comparisons: 22 log: 16.6355 comparisons/log: 1.32247
    comparisons: 26 log: 17.3287 comparisons/log: 1.5004
    comparisons: 25 log: 18.0218 comparisons/log: 1.38721
    comparisons: 26 log: 18.7150 comparisons/log: 1.38926
    comparisons: 29 log: 19.4081 comparisons/log: 1.49422
    comparisons: 25 log: 20.1013 comparisons/log: 1.2437
    comparisons: 31 log: 20.7944 comparisons/log: 1.49078
    */

    return 0;
}
