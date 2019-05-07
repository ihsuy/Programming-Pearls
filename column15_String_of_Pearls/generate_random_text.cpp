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
Different random text generating schemes
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
    int total_nchar = 26 + special_characters.length();
    for (int i = 0; i < len; ++i)
    {
        randText += ToChar(rand() % (total_nchar));
    }
    return randText;
}

#define ALPHA_BASE 'a'
#define N_CHAR 27
vector<unordered_map<string, vector<int>>> LearnPatternMap(const string& source_path,
        const int& N)
{
    ifstream source(source_path);
    if (not source)
    {
        throw runtime_error("Can't load source file");
    }

    vector<unordered_map<string, vector<int>>> patternMaps(N, unordered_map<string, vector<int>>());
    patternMaps[0][" "] = vector<int>(N_CHAR, 0);

    string word;
    while (source >> word)
    {   // learn initials
        if (not isalpha(word[0]))
        {
            continue;
        }
        patternMaps[0][" "][tolower(word[0]) - ALPHA_BASE]++;
        // learn 1~N grams
        for (int i = 0; i < N; ++i)
        {
            int token_len = i + 1, word_len = word.length(),
                upper = word_len - token_len;

            for (int j = 0; j < upper; ++j)
            {
                string token;
                for (int r = j; r < j + token_len; ++r)
                {
                    if (isalpha(word[r]))
                    {
                        token += tolower(word[r]);
                    }
                }

                if (token.length() < i + 1)
                {
                    continue;
                }

                if (patternMaps[i][token].size() == 0)
                {
                    patternMaps[i][token] = vector<int>(N_CHAR, 0);
                }

                int next_i = j + token_len;
                char next_ch = N_CHAR - 1; // termination (word end)
                if (isalpha(word[next_i]))
                {
                    next_ch = tolower(word[next_i]) - ALPHA_BASE;
                }

                patternMaps[i][token][next_ch]++;
            }
        }
    }
    return patternMaps;
}

string Order2RandomText(const int& nWords, const string& source_path)
{
    auto patternMaps = LearnPatternMap(source_path, 2);

    vector<int> initial_dist(patternMaps[0][" "]);
    for (int i = 0, upper = 0; i < N_CHAR; ++i)
    {
        upper += initial_dist[i];
        initial_dist[i] = upper;
    }

    vector<vector<int>> sec_letter_dist;
    for (int i = 0; i < N_CHAR - 1; ++i)
    {
        vector<int> temp = patternMaps[0][string(1, ALPHA_BASE + i)];
        int upper = 0;
        for (int j = 0; j < N_CHAR; ++j)
        {
            upper += temp[j];
            temp[j] = upper;
        }
        sec_letter_dist.push_back(temp);
    }

    vector<vector<vector<int>>> other_letters_dist(N_CHAR - 1,
            vector(N_CHAR - 1, vector<int>()));
    for (int i = 0; i < N_CHAR - 1; ++i)
    {
        for (int j = 0; j < N_CHAR - 1; ++j)
        {
            string key = string(1, ALPHA_BASE + i) + string(1, ALPHA_BASE + j);
            vector<int> temp = patternMaps[1][key];
            for (int c = 0, upper = 0; c < temp.size(); ++c)
            {
                upper += temp[c];
                temp[c] = upper;
            }
            other_letters_dist[i][j] = temp;
        }
    }



    string text;
    for (int i = 0; i < nWords; ++i)
    {   // generate initial letter
        string word;
        int key = rand() % (initial_dist.back()), j = 0;
        while (key >= initial_dist[j++]);
        word += ALPHA_BASE + j;
        cout << word << endl;

        // gets second letter
        vector<int> sec_dist = sec_letter_dist[j];
        key = rand() % (sec_dist.back());
        j = 0;
        while (key >= sec_dist[j++]);
        if (j >= N_CHAR - 1)
        {
            text += ' ';
            continue;
        }
        else
        {
            word += ALPHA_BASE + j;
        }

        int pos = 1;
        // get the rest
        while (true)
        {
            int a = word[pos - 1] - ALPHA_BASE, b = word[pos] - ALPHA_BASE;
            vector<int> other_dist = other_letters_dist[a][b];
            if (other_dist.empty())
            {
                text += ' ';
                break;
            }
            key = rand() % (other_dist.back());
            j = 0;
            while (key >= other_dist[j++]);

            if (j >= N_CHAR - 1)
            {
                text += ' ';
                break;
            }
            else
            {
                word += ALPHA_BASE + j;
            }
            pos++;
        }

        text += word;
    }
    text.pop_back();
    return text;
}

int main()
{
    const string source_path = "/Users/ihsuy/programming_pearls/shakespeare_small.txt";
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    //LearnPatternMap(source_path, 2);
    cout << Order2RandomText(200, source_path) << endl;
    return 0;
}
