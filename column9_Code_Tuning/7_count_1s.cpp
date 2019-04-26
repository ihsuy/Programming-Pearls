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
Given a very long sequence (say, billions or trillions) of bytes,
how would you efficiently count the total number of one bits?
(That is, how many bits are turned on in the entire sequence?)
*/
// this problem boil down to calculating how many 32 bits it has
// and for each 32 bits consider it an 32 bit integer and count its
// set bit. finally add them up
// I've implemented multiple different method for counting set bit
// in a 32 bit integer

// naive method
// simply shift to right while extracting rightmost bit
// and increment count if its on
inline int countOnes1(int i)
{
    int count = 0;
    while (i)
    {
        count += i & 1;
        i >>= 1;
    }
    return count;
}

// skip 0 method
// this method removes the leftmost 1 bit
// one by one, therefore skipping any 0s in between 1s
// for example
// for number n = 0b00100000000000000000100000000001
// the while loop in this function only runs 3 times
// until n becomes 0
inline int countOnes2(int i)
{
    int count = 0;
    while (i)
    {
        count ++;
        i &= i - 1;
    }
    return count;
}

// hardcoded method
// method only works for 32bit int
// it goes like :
// count number of bits in every 2 bits
// and represent them in 2 bits
// count number of bits in every 4 bits
// and represent them in 4 bits
// and so on
// finally we trim the 26 bits on the left
// since we can have at most 32 bits set
// and that only requires 6 bits to store
inline int countOnes3(int i)
{   // only works for 32 bit
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}

// count set bit in each nibble
// add them up
// key is to prepare a lookup table
// calculate number of bits in each nibble in advance
int nibbleBits[16]
{
    0, 1, 1, 2,
    1, 2, 2, 3,
    1, 2, 2, 3,
    2, 3, 3, 4
};

inline int countOnes4(int i)
{
    int count = 0;
    while(i)
    {
        count += nibbleBits[i&0xf]; // get nibble then retrieve number of set bit
        i>>=4; // next nibble
    }
    return count;
}

pair<ll, int> profiler(int(count)(int), int i)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res = count(i);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    return {t, res};
}

/*
result after 10000000 tests
avg t1: 63 nanoseconds
avg t2: 58 nanoseconds
avg t3: 39 nanoseconds // sometimes becomes slower than t4 but usually the fastest
avg t4: 41 nanoseconds // very stable
*/

int main()
{
    //int n = 0b00001111000011110000111100001111;
    const int nTest = 1000000;
    ll t1_sum = 0, t2_sum = 0, t3_sum = 0, t4_sum = 0;
    for (int n = 0; n < nTest; ++n)
    {
        auto res1 = profiler(countOnes1, n);
        auto res2 = profiler(countOnes2, n);
        auto res3 = profiler(countOnes3, n);
        auto res4 = profiler(countOnes4, n);

        assert(res1.second == res2.second);
        assert(res1.second == res3.second);
        assert(res1.second == res4.second);
        // cout << "res1: " << res1.second << " t: " << res1.first << '\n';
        // cout << "res2: " << res2.second << " t: " << res2.first << '\n';
        t1_sum += res1.first;
        t2_sum += res2.first;
        t3_sum += res3.first;
        t4_sum += res4.first;
    }
    cout << "avg t1: " << t1_sum / nTest << '\n';
    cout << "avg t2: " << t2_sum / nTest << '\n';
    cout << "avg t3: " << t3_sum / nTest << '\n';
    cout << "avg t4: " << t4_sum / nTest << '\n';
    return 0;
}
