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
