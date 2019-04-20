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
inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n >> b) & 1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while (n && ++res) n -= n & (-n); return res; }
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Write a “banner” function that is given
a capital letter as input and produces as output
an array of characters that graphically depicts that letter.
*/

// draw ascii art for each letter...
// thats a lot of work so i only didnt for A~I
const vector<string> letters_ascii_art
{
	"\
  #######   \n\
##       ## \n\
##       ## \n\
##       ## \n\
########### \n\
##       ## \n\
##       ## \n\
##       ## \n\
##       ## \n\
",
	"\
##########  \n\
#         # \n\
#         # \n\
#         # \n\
##########  \n\
#         # \n\
#         # \n\
#         # \n\
##########  \n\
",
	"\
   ######## \n\
 #           \n\
#           \n\
#           \n\
#           \n\
#           \n\
#           \n\
 #           \n\
  ######### \n\
",
	"\
######### \n\
#        # \n\
#         # \n\
#         # \n\
#         # \n\
#         # \n\
#         # \n\
#        # \n\
######### \n\
",
	"\
########### \n\
#           \n\
#           \n\
#           \n\
########### \n\
#           \n\
#           \n\
#           \n\
########### \n\
",
	"\
########### \n\
#           \n\
#           \n\
#           \n\
########### \n\
#           \n\
#           \n\
#           \n\
#           \n\
",
	"\
 ##########  \n\
#            \n\
#            \n\
#            \n\
#    ######  \n\
#         #  \n\
#         #  \n\
#         #  \n\
 ##########  \n\
",
	"\
##       ## \n\
##       ## \n\
##       ## \n\
##       ## \n\
########### \n\
##       ## \n\
##       ## \n\
##       ## \n\
##       ## \n\
",
	"\
########## \n\
########## \n\
    ##      \n\
    ##      \n\
    ##      \n\
    ##      \n\
    ##      \n\
########## \n\
########## \n\
"
};

string depict_letters(const char& letter)
{
	assert(letter >= 'A' and letter <= 'I');

	return letters_ascii_art[letter-'A'];
}

int main()
{
	for(char ch = 'A'; ch <= 'I'; ++ch)
	{
		cout << ch << ": \n" << depict_letters(ch) << '\n'; 
	}

	return 0;
}
