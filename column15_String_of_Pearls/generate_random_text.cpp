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

*/
const string special_characters = ",. !?";
char ToChar(const int& n, const string special_char = special_characters)
{
    assert(n >= 0 and n < 26 + special_char.length());
    if (n >= 0 and n < 26)
    {
        return char(n + 'a');
    }
    else
    {
        return special_char[n - 26];
    }
}

string PureRandomText(const int& len)
{
    string randText; 
    randText.reserve(len);
    int total_nchar = 26+special_characters.length();
    for(int i = 0; i < len; ++i)
    {
        randText+=ToChar(rand()%(total_nchar));
    }
    return randText;
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    cout << PureRandomText(200) << '\n';

    return 0;
}
