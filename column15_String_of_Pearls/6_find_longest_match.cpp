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

template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Given a new input string, how would you search a
suffix array to find the longest match in the
stored text?
*/

// Warning: "shakespear.txt" is huge so the preprocessing
// may take long (20s on my mac pro).
// But once the preprocessing is done, searching is very fast.


long long LoadFile(const string& file_path, char*& buffer)
{
    FILE * pFile = fopen ( file_path.c_str() , "rb" );
    if (pFile == NULL)
    {
        fputs ("File error", stderr);
        exit (1);
    }
    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    auto lSize = ftell (pFile);
    rewind (pFile);
    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char) * lSize);
    if (buffer == NULL)
    {
        fputs ("Memory error", stderr);
        exit (2);
    }
    // copy the file into the buffer:
    auto result = fread (buffer, 1, lSize, pFile);
    if (result != lSize)
    {
        fputs ("Reading error", stderr);
        exit (3);
    }
    cout << "Completed loading file to the buffer of size " << result << '\n';
    fclose (pFile);
    return result;
}

char const** PreprocessBuffer(char*& buffer, const long long& fsize)
{
    char const** index_arr = new char const*[fsize];
    cout << "Creating index array...\n";
    for (int i = 0; i < fsize; ++i)
    {
        index_arr[i] = &buffer[i];
    }
    cout << "Sorting index array...\n";
    sort(index_arr, index_arr + fsize,
    [](char const * lhs, char const * rhs) {
        return strcmp(lhs, rhs) < 0;
    });
    cout << "Sorting completed\n";
    return index_arr;
}

long long SearchInitial(char const** index_arr, const long long& fsize,
                        const char& target_initial)
{
    cout << "Searching...\n";
    int low = -1, high = fsize;
    while (low + 1 != high)
    {
        int mid = (low + high) >> 1;
        if (index_arr[mid][0] < target_initial)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }
    if (high >= fsize or index_arr[high][0] != target_initial)
    {
        return -1;
    }
    cout << "Found starting point\n";
    return high;
}

pair<long long, long long> MatchPattern(char const** index_arr,
                                        const long long& pos,
                                        const long long& fsize,
                                        const string& pattern)
{
    char target_initial = pattern[0];
    long long lhs = pos, maxlen = 0;
    for (int i = pos; i < fsize and index_arr[i][0] == target_initial; ++i)
    {
        int j = 0, len = 0;
        while (pattern[j] == index_arr[i][j])
        {
            j++; len++;
        }
        if (len > maxlen)
        {
            maxlen = len;
            lhs = i;
        }
    }
    return {lhs, maxlen};
}

pair<string, long long> GetString(const pair<long long, long long>& pattern_pos,
                                  const char* buffer,
                                  char const** index_arr, const long long& fsize,
                                  const int& extra_range)
{
    long long lhs = index_arr[pattern_pos.first] - buffer;
    long long rhs = lhs + pattern_pos.second;

    long long range_lhs = lhs - extra_range;
    if (range_lhs < 0)
    {
        range_lhs = 0;
    }
    long long range_rhs = rhs + extra_range;
    if (range_rhs >= fsize)
    {
        range_rhs = fsize - 1;
    }

    string prefix(buffer + range_lhs, buffer + lhs),
           stem(buffer + lhs, buffer + rhs),
           affix(buffer + rhs, buffer + range_rhs);

    return {"{..." + prefix + "---->>>[" + stem + "]<<<----" + affix + "...}", stem.length()};
}

vector<pair<string, long long>> LongestMatch(const string& file_path, const vector<string>& queries, const int extra_range = 150)
{
    char * buffer;
    auto fsize = LoadFile(file_path, buffer);

    char const** index_arr = PreprocessBuffer(buffer, fsize);

    const int query_size = queries.size();
    vector<pair<string, long long>> responses;
    responses.reserve(query_size);

    cout << "producing output...\n\n";

    for (int i = 0; i < query_size; ++i)
    {
        char target_initial = queries[i][0];
        auto pos = SearchInitial(index_arr, fsize, target_initial);
        if (pos < 0)
        {
            responses.push_back({"-->{NOT FOUND}<--", 0});
            continue;
        }

        // found starting point, begin matching
        pair<long, long> pattern_pos = MatchPattern(index_arr, pos, fsize, queries[i]);
        responses.push_back(GetString(pattern_pos, buffer, index_arr, fsize, extra_range));
    }

    free (index_arr);
    free (buffer);

    return responses;
}

void LongestMatch_app(const string& file_path, const int extra_range = 200)
{
    char * buffer;
    auto fsize = LoadFile(file_path, buffer);

    char const** index_arr = PreprocessBuffer(buffer, fsize);

    cout << "Ready\n";

    for (;;)
    {
        cout << "Query>>";
        string q;
        getline(cin, q);

        if(q == "quit()")
        {
            break;
        }

        auto pos = SearchInitial(index_arr, fsize, q[0]);
        if (pos < 0)
        {
            cout << "-->{NOT FOUND}<--\n";
            continue;
        }

        pair<long, long> pattern_pos = MatchPattern(index_arr, pos, fsize, q);

        auto response = GetString(pattern_pos, buffer, index_arr, fsize, extra_range);

        // report result
        cout << ">>>Query: \"" << q << "\"<<<\n";
        cout << "Match Length: " << response.second << '\n';
        cout << "Response: \n";
        cout << response.first << '\n';
        cout << ">>>Query End<<<" << "\n\n";
    }

    free (index_arr);
    free (buffer);
}

int main()
{
    const string path = "/Users/ihsuy/programming_pearls/shakespeare.txt";

    LongestMatch_app(path);

    // vector<string> queires{
    //     "you are",
    //     "hello",
    //     "wondering",
    //     "maybe not",
    //     "however",
    //     "math",
    //     "forever",
    //     "eternity",
    //     "hard work",
    //     "perhaps you are right"
    //     "I doubt",
    //     "swag",
    //     "interesting idea",
    //     "yogurt",
    //     "clown",
    //     "science",
    //     "computer"
    // };

    // auto responses = LongestMatch(path, queires);

    // for (int i = 0; i < responses.size(); ++i)
    // {
    //     cout << ">>>Query: \"" << queires[i] << "\"<<<\n";
    //     cout << "Match Length: " << responses[i].second << '\n';
    //     cout << "Response: \n";
    //     cout << responses[i].first << '\n';
    //     cout << ">>>Query End<<<" << "\n\n";
    // }



    return 0;
}
