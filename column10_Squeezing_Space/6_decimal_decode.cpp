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
The discussion of Data Compression in Section 10.3
mentioned decoding 10×a + b with / and % operations.
Discuss the time and space tradeoffs involved in
replacing those operations by logical operations
or table lookups.
*/

// the encoding and decoding method mentioned in the book
int encode1(const int& a, const int& b)
{
    assert(a >= 0 and a <= 9 and b >= 0 and b <= 9);

    return a * 10 + b;
}

pair<int, int> decode1(const int& c)
{
    return {c / 10, c % 10};
}

//decode using logical operation
pair<int, int> decode1_2(const int& c)
{   // 205/2048 is 0.10009765625; roughly 1/10
    // but i couldn't figure out how to mod 10 using shift
    return {(c * 205) >> 11, c % 10};
}

// decode using lookup table
vector<int> mod10;
vector<int> div10;
void BuildTables()
{
    mod10.clear();
    div10.clear();

    for (int i = 0; i < 100; ++i)
    {
        mod10.push_back(i % 10);
        div10.push_back(i / 10);
    }
}
// table has to be built first
pair<int, int> decode1_3(const int& c)
{
    return {div10[c], mod10[c]};
}

// Encoding and decoding method only uses bit shifting
// since a decimal digit ranges from 0000 to 1001, a nibble is enough
// for storing it, we store 2 digits in 8 bits by storing them in
// 1 nibble each
int encode2(const int a, const int& b)
{
    assert(a >= 0 and a <= 9 and b >= 0 and b <= 9);

    return (a << 4) | b;
}
// get the 1st and 2nd nibble
pair<int, int> decode2(const int& c)
{
    auto mask = (1 << 4) - 1;
    return {(c >> 4)&mask, c & mask};
}

pair<int, int> profiler(pair<int, int>(dec)(const int&),
                        const int& c, long long& tsum)
{
    auto t1 = chrono::high_resolution_clock::now();
    auto res1 = dec(c);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::nanoseconds>(t2).count();
    tsum += t;
    return res1;
}

int main()
{
    BuildTables();

    // test
    /*
    result after 100 tests
    avg t1: 69
    avg t2: 67
    avg t3: 64
    avg t4: 62
    */
    const int nTest = 100;
    long long t1 = 0, t2 = 0, t3 = 0, t4 = 0;
    for (int i = 0; i < nTest; ++i)
    {
        for (int a = 0; a <= 9; ++a)
        {
            for (int b = 0; b <= 9; ++b)
            {
                auto c = encode1(a, b);
                auto c2 = encode2(a, b);

                auto d1 = profiler(decode1, c, t1);
                auto d1_2 = profiler(decode1_2, c, t2);
                auto d1_3 = profiler(decode1_3, c, t3);
                auto d2 = profiler(decode2, c2, t4);
                assert(d1.first == d1_2.first and d1.first == d1_3.first and d1.first == d2.first);
                assert(d1.second == d1_2.second and d1.second == d1_3.second and d1.second == d2.second);
            }
        }
    }

    cout << "avg t1: " << t1 / (100 * nTest) << '\n';
    cout << "avg t2: " << t2 / (100 * nTest) << '\n';
    cout << "avg t3: " << t3 / (100 * nTest) << '\n';
    cout << "avg t4: " << t4 / (100 * nTest) << '\n';
    return 0;
}
