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
Compress an online dictionary of English
to be as small as possible. When counting space,
measure both the data file and the program
that interprets the data.
*/

const string dict_addr = "/Users/ihsuy/programming_pearls/engWords.txt";
const string decoded_addr = "/Users/ihsuy/programming_pearls/decoded_engWords.txt";
const string output_addr = "/Users/ihsuy/programming_pearls/compressed_engWords.txt";

// my method is to squeeze 1 alphabet into 5 bits
// and squeeze 8 char into 5 bytes
// 5 bytes             00000000 00000000 00000000 00000000 00000000
// squeeze in 8 chars  xxxxxppp ppxxxxxp ppppxxxx xpppppxx xxxppppp

#define BITS_IN_BYTE 8
#define BITS_IN_TOKEN 5
#define ALPHA_BASE 97

char sep_token = '|';
void CompressDict(const string& from_file = dict_addr,
                  const string& to_file = output_addr)
{
    ifstream dict(from_file);
    ofstream compressed_dict(to_file);
    // error checking omitted

    string word;
    int c = 0;
    char token = 0;

    while (dict >> word)
    {
        word += sep_token;
        auto word_len = word.length();

        for (int i = 0; i < word_len; ++i)
        {
            char compressed_char = word[i] - ALPHA_BASE;
            token |= (compressed_char << c);

            c += BITS_IN_TOKEN;
            if (c >= BITS_IN_BYTE)
            {
                compressed_dict << token;
                token = 0;

                c -= BITS_IN_BYTE;
                token |= (compressed_char >> (BITS_IN_TOKEN - c));
            }
        }
    }
}

bitset<8> token_mask("00011111");
void DecodeDict(const string& from_file = output_addr,
                const string& to_file = decoded_addr)
{
    ifstream compressed_dict(from_file);
    ofstream decoded_dict(to_file);

    //string res;
    int shift = 0;
    char token = compressed_dict.get();
    bitset<8> btoken(token);
    while(compressed_dict)
    {
        bitset<8> decoded_char = (btoken & (token_mask << shift)) >> shift;

        if (BITS_IN_TOKEN + shift > BITS_IN_BYTE)
        {
            token = compressed_dict.get();
            btoken = bitset<8>(token);

            int offset = BITS_IN_BYTE - shift;

            shift += BITS_IN_TOKEN - BITS_IN_BYTE;

            bitset<8> extra_mask((1 << shift) - 1);
            decoded_char |= ((btoken & extra_mask) << offset);
        }
        else
        {
            shift += BITS_IN_TOKEN;
        }

        if (decoded_char.to_ulong() == sep_token - ALPHA_BASE)
        {
            decoded_dict << '\n';
        }
        else
        {
            decoded_dict << (char)(decoded_char.to_ulong() + ALPHA_BASE);
        }
    }
}

void test()
{
    ifstream original(dict_addr);
    ifstream decoded(decoded_addr);

    string token1, token2;
    while(original >> token1 and decoded >> token2)
    {
        if(token1 != token2)
        {
            cout << token1 << " != " << token2 << endl;
        }
    }
}

int main()
{

    // CompressDict();
    // DecodeDict();
    test();
    return 0;
}
