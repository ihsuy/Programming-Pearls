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
This problem deals with a small part of the problem of
hyphenating English words. The following list of
rules describes some legal hyphenations of words that
end in the letter “c”:
et-ic al-is-tic s-tic p-tic -lyt-ic ot-ic an-tic
n-tic c-tic at-ic h-nic n-ic m-ic l-lic b-lic -clic
l-ic h-ic f-ic d-ic -bic a-ic -mac i-ac
The rules must be applied in the above order;

thus the hyphenations “eth-nic” (which is caught by the rule “h-nic”)
and “clinic” (which fails that test and falls through to “n-ic”).
How would you represent such rules in a function that is
given a word and must return suffix hyphenations?
*/

const vector<string> hyphenation_matches
{
    "etic", "alistic", "stic", "ptic", "lytic",
    "otic", "antic", "ntic", "ctic", "atic",
    "hnic", "nic", "mic", "llic", "blic", "clic",
    "lic", "hic", "fic", "dic", "bic", "aic",
    "mac", "iac"
};

const vector<string> hyphenation_patterns
{
    "et-ic", "al-is-tic", "s-tic", "p-tic", "-lyt-ic",
    "ot-ic", "an-tic", "n-tic", "c-tic", "at-ic",
    "h-nic", "n-ic", "m-ic", "l-lic", "b-lic",
    "-clic", "l-ic", "h-ic", "f-ic", "d-ic",
    "-bic", "a-ic", "-mac", "i-ac"
};

string hyphenation(string word)
{   // find the shortest and longest suffix match
    int shortest_match_length = INT_MAX;
    int longest_match_length = 0;

    for (auto& match : hyphenation_matches)
    {
        if (match.length() < shortest_match_length)
        {
            shortest_match_length = match.length();
        }
        if (match.length() > longest_match_length)
        {
            longest_match_length = match.length();
        }
    }

    // since the suffix we are going to match will have length
    // range from [shortest_match_length, longest_match_length]
    // we only match in this range
    int match_end = word.length() - shortest_match_length;


    int i = word.length() - longest_match_length;
    if (i < 0)
    {   // when the input word is shorter than the longest match length
        // we match from beginning
        i = 0;
    }

    for (int suffix_len = longest_match_length; i <= match_end; ++i, suffix_len--)
    {   // extract suffix
        string suffix = word.substr(i, suffix_len);
        // match suffix
        auto pos = find(hyphenation_matches.begin(),
                        hyphenation_matches.end(), suffix);
        // match successfully?
        if (pos == hyphenation_matches.end())
        {   // no match
            continue;
        }
        // found match
        // calculate index to retrieve hypenation pattern
        int pattern_index = distance(hyphenation_matches.begin(), pos);
        // hypenate
        word.replace(i, suffix_len, hyphenation_patterns[pattern_index]);

        return word;
    }
    // no available hypenation pattern
    return word;
}

int main()
{
    string word = "realistic";
    cout << hyphenation(word) << endl;

    word = "ethnic";
    cout << hyphenation(word) << endl;

    word = "clinic";
    cout << hyphenation(word) << endl;

    word = "periodic";
    cout << hyphenation(word) << endl;

    word = "gigantic";
    cout << hyphenation(word) << endl;

    return 0;
}
