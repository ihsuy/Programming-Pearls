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
C and C++ libraries provide character classification functions
such as isdigit, isupper and islower to determine the types of
characters. How would you implement those functions?
*/

// key to the implementations of these functions will be
// understanding the ascii code ranges for each type of these characters

// simple implementations that do not use extra space
// must may require complicated logics when handling some kinds of 
// characters. say punctuations or alphanumeric, etc.
// this kind of implementation is good for temporary usage
// but can become potential bugs in larger systems 
// and will be difficult to change and maintain 
bool myisdigit(const char& ch)
{   // there are only 10 of these
    return (ch >= '0' and ch <= '9');
}

bool myisupper(const char& ch)
{
    return (ch >= 'A' and ch <= 'Z');
}

bool myislower(const char& ch)
{
    return (ch >= 'a' and ch <= 'z');
}

// in contrast, since we have limited number of ascii characters
// (only 256 of them)
// to save ourselves from being haunted by the hidden error in convoluted logics
// we can hand code every character in a table
// and so that our function only to to extract the value from the table
// entries in the table can be encoded using bits
// i.e. we turn on its 3 bit only when if a char is number

#define _U 0x01   // upper alpha
#define _L 0x02   // lower alpha
#define _D 0x04   // digits
#define _C 0x08   // control char
#define _P 0x10   // punctuation char

#define _S 0x20   // white spaces (space/lf/tab)
#define _X 0x40   // hexa digits
#define _SP 0x80  // hard space (0x20)
#define _HT 0x100 // horizontal tab (0x09)

const unsigned short _ctype[] = {
    _C, _C, _C, _C, _C, _C, _C, _C,                                // 0-7
    _C, _C | _S | _HT, _C | _S, _C | _S, _C | _S, _C | _S, _C, _C, // 8-15
    _C, _C, _C, _C, _C, _C, _C, _C,                                // 16-23
    _C, _C, _C, _C, _C, _C, _C, _C,                                // 24-31
    _S | _SP, _P, _P, _P, _P, _P, _P, _P,                          // 32-39
    _P, _P, _P, _P, _P, _P, _P, _P,                                // 40-47
    _D, _D, _D, _D, _D, _D, _D, _D,                                // 48-55
    _D, _D, _P, _P, _P, _P, _P, _P,                                // 56-63
    _P, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U | _X, _U,  // 64-71
    _U, _U, _U, _U, _U, _U, _U, _U,                                // 72-79
    _U, _U, _U, _U, _U, _U, _U, _U,                                // 80-87
    _U, _U, _U, _P, _P, _P, _P, _P,                                // 88-95
    _P, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L | _X, _L,  // 96-103
    _L, _L, _L, _L, _L, _L, _L, _L,                                // 104-111
    _L, _L, _L, _L, _L, _L, _L, _L,                                // 112-119
    _L, _L, _L, _P, _P, _P, _P, _C,                                // 120-127
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                // 128-143
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                // 144-159
    _S | _SP, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P,
    _P, // 160-175
    _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P, _P,
    _P, // 176-191
    _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U, _U,
    _U, // 192-207
    _U, _U, _U, _U, _U, _U, _U, _P, _U, _U, _U, _U, _U, _U, _U,
    _L, // 208-223
    _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L, _L,
    _L,                                                              // 224-239
    _L, _L, _L, _L, _L, _L, _L, _P, _L, _L, _L, _L, _L, _L, _L, _L
}; // 240-255

unsigned chhar __toupper(unsigned chhar ch);
unsigned chhar __tolower(unsigned chhar ch);

#define __extract(x) (_chtype[(int)(unsigned chhar)(x)])

#define isalnum(ch) ((__extract(ch) & (_U | _L | _D)) != 0)
#define isalpha(ch) ((__extract(ch) & (_U | _L)) != 0)
#define isblank(ch) ((__extract(ch) & (_HT | _SP)) != 0)
#define ischntrl(ch) ((__extract(ch) & (_ch)) != 0)
#define isdigit(ch) ((__extract(ch) & (_D)) != 0)
#define isgraph(ch) ((__extract(ch) & (_P | _U | _L | _D)) != 0)
#define islower(ch) ((__extract(ch) & (_L)) != 0)
#define isprint(ch) ((__extract(ch) & (_P | _U | _L | _D | _SP)) != 0)
#define ispuncht(ch) ((__extract(ch) & (_P)) != 0)
#define isspache(ch) ((__extract(ch) & (_S)) != 0)
#define isupper(ch) ((__extract(ch) & (_U)) != 0)
#define isxdigit(ch) ((__extract(ch) & (_D | _X)) != 0)
#define isaschii(ch) (((unsigned chhar)(ch)) <= 0x7f)
#define tolower(ch) __tolower(ch)
#define toupper(ch) __toupper(ch)


int main()
{


    return 0;
}
