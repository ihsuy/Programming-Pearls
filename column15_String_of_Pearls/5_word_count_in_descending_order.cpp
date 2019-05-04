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
#include <iomanip>

typedef long long ll;
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
When we looked at the output of the word frequency programs in Section 15.1,
it was most interesting to print the words in decreasing frequency.
How would you modify the C and C++ programs to accomplish this task?
How would you print only the M most common words, where M is a
constant such as 10 or 1000?
*/

void WordWasher(string& word, const string ignore = "[]{}_-',.;:<>?!@*()\\\'\"")
{
    string new_word;
    int wordlen = word.length();
    for (int i = 0; i < wordlen; ++i)
    {
        if (ignore.find(word[i]) == string::npos)
        {
            new_word += tolower(word[i]);
        }
    }
    word = new_word;
}

vector<pair<string, int>> WordRank(const string& file_path, const int& rank_length = 10)
{
    ifstream text_file(file_path);
    if (not text_file)
    {
        throw runtime_error("Can't open file");
    }

    unordered_map<string, int> word_counter;
    string word;
    while (text_file >> word)
    {
        WordWasher(word);
        if (word == "")
        {
            continue;
        }

        if (word_counter.count(word))
        {
            word_counter[word]++;
        }
        else
        {
            word_counter[word] = 1;
        }
    }

    vector<pair<string, int>> rankings;
    rankings.resize(word_counter.size());

    transform(word_counter.begin(), word_counter.end(), rankings.begin(),
    [](pair<string, int> p) {
        return p;
    });

    sort(rankings.begin(), rankings.end(),
    [](const pair<string, int>& p1, const pair<string, int>& p2) {
        return p1.second > p2.second;
    });

    return {rankings.begin(), rankings.begin() + rank_length};
}


int main()
{
    const string path = "/Users/ihsuy/programming_pearls/shakespeare.txt";
    const int rank_length = 1000;
    auto res = WordRank(path, rank_length);
    for (int i = 0; i < rank_length; ++i)
    {
        cout << "rank " << i + 1 << ": " << setw(12) << left << res[i].first
             << setw(12) << left << " ct: " << res[i].second << '\n';
    }

    return 0;
}
