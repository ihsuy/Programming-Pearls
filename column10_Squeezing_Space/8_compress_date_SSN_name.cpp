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
Obvious data representations allocate eight bytes
for a date (MMDDYYYY), nine bytes for a social
security number (DDD-DD-DDDD), and 25 bytes for
a name (14 for last, 10 for first, and 1 for
middle initial). If space is critical, how far
can you reduce those requirements?
*/

// date:
//                MMDDYYYY
// lower bound  : 00000000
// upper bound  : 19399999
// bits required: 14244444 = 27 bits
// according to the observation above
// we only need 27 bits to a store date datum
// for example, today's date is 04292019
// encoded_date: 100100010000001010011001000
//                  9   1   0   2   9 2   40

// note that more error checkings are needed for all the implementations below
// though i didn't

// the following implementation returns a size 27 bitset as encoded result
// meaning only 27 bits is required to represent a date
// input will be a string of size 8 that theoriotically uses 8 bytes
int mask_positions[9] = {0, 1, 5, 7, 11, 15, 19, 23/*end of meaningful values*/,
                         23/*sentinel value*/
                        };
bitset<27> EncodeDate(const string& date)
{
    assert(date.length() == 8);

    bitset<27> encoded_date;
    for (int i = 0; i < 8; ++i)
    {
        encoded_date |= ((date[i] - '0') << mask_positions[i]);
    }
    return encoded_date;
}

bitset<27> masks[8] = {1, 15, 3, 15, 15, 15, 15, 15};
string DecodeDate(bitset<27> encoded_date)
{
    string date;
    date.reserve(8);

    for (int i = 0; i < 8; ++i)
    {
        date += ((encoded_date & masks[i]).to_ulong() + '0');
        encoded_date >>= (mask_positions[i + 1] - mask_positions[i]);
    }

    return date;
}

// for social security number in the US until current time 2019,
// the format is AAA-GG-SSSS
// where A stands for Area, G stands for Group, S stands for Serial number
// each field can contain an integer from 0-9
// though due to many historical and cultural reasons, some special numbers
// 666 or 000 are never assigned for certain field
// we'll ignore these and assume all 000000000 to 999999999 will be assigned
// and we are gonna represent them using fewer bytes
// my method is based on the fact that a 30 bits (max 1073741823)
// are enough to represent all these numbers
bitset<30> EncodeSSN(string ssn)
{
    assert(ssn.length() == 11);
    // remove hyphens
    ssn.erase(3, 1);
    ssn.erase(5, 1);

    return stol(ssn);
}

string DecodeSSN(const bitset<30>& encoded_ssn)
{
    string ssn = to_string(encoded_ssn.to_ulong());
    // padding
    int pad_len = 9 - ssn.length();
    for (int i = 0; i < pad_len; ++i)
    {
        ssn = '0' + ssn;
    }
    // reformat
    ssn.insert(ssn.begin() + 3, '-');
    ssn.insert(ssn.begin() + 6, '-');
    return ssn;
}


int main()
{
    const string today = "04292019";

    auto encoded_date = EncodeDate(today);
    cout << "encoded_date: " << encoded_date << '\n';
    cout << "decoded_date: " << DecodeDate(encoded_date) << '\n';

    const string ssn = "347-78-9235"; // a person from IL
    auto encoded_ssn = EncodeSSN(ssn);
    cout << "encoded_ssn: " << encoded_ssn << '\n';
    cout << "decoded_ssn: " << DecodeSSN(encoded_ssn) << '\n';
    return 0;
}
