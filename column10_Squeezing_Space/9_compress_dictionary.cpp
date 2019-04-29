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
const string output_addr = "/Users/ihsuy/programming_pearls/compressed_engWords.txt";

// my method is to squeeze 1 alphabet into 5 bits
// and squeeze 8 char into 5 bytes
// 5 bytes             00000000 00000000 00000000 00000000 00000000
// squeeze in 8 chars  xxxxxppp ppxxxxxp ppppxxxx xpppppxx xxxppppp

#define BITS_IN_BYTE 8
#define BITS_IN_TOKEN 5
#define ALPHA_BASE 97

// void CompressDict(const string& from_file = dict_addr,
//                   const string& to_file = output_addr)
// {
//     ifstream dict(from_file);

//     // error checking omitted

//     vector<char> tokens;

//     string word;
//     while(dict >> word)
//     {
//         auto word_len = word.length();

//         int c = 0, ;
//         char token = 0;
//         for (int i = 0; i < word_len; ++i)
//         {
//             char compressed_char = word[i] - ALPHA_BASE;

//             token |= (compressed_char << c);
//             c += BITS_IN_TOKEN;
//             if (c > BITS_IN_BYTE)
//             {
//                 tokens.push_back(token);
//                 token = 0;
//                 c -= BITS_IN_BYTE;
//                 token |= (compressed_char>>(BITS_IN_TOKEN-c));
//             }

//         }
//     }
// }

bitset<8> sep_token("11111111");
vector<char> test(const string& text)
{
    stringstream dict(text);

    // error checking omitted

    vector<char> tokens;

    string word;
    while (dict >> word)
    {
        word += char(0b00011111 + ALPHA_BASE);
        auto word_len = word.length();
        cout << word << endl;
        int c = 0;
        char token = 0;
        for (int i = 0; i < word_len; ++i)
        {
            char compressed_char = word[i] - ALPHA_BASE;
            token |= (compressed_char << c);

            c += BITS_IN_TOKEN;
            if (c >= BITS_IN_BYTE)
            {
                tokens.push_back(token);
                token = 0;

                c -= BITS_IN_BYTE;
                token |= (compressed_char >> (BITS_IN_TOKEN - c));
            }
        }
        tokens.push_back(token);
        //tokens.push_back(sep_token.to_ulong());
    }
    tokens.pop_back();
    // ofstream outfile(output_addr);
    // for(auto t : tokens)
    // {
    //     outfile << t;
    // }
    return tokens;
}

bitset<8> token_mask("00011111");
string decodetest(const vector<char>& tokens)
{
    string res;
    int shift = 0;
    bitset<8> btoken(tokens[0]);
    for (int i = 0; i < tokens.size();)
    {
        bitset<8> decoded_char = (btoken & (token_mask << shift)) >> shift;

        if (BITS_IN_TOKEN + shift > BITS_IN_BYTE)
        {
            i++;
            btoken = bitset<8>(tokens[i]);
            // if (tokens[i] == (char)sep_token.to_ulong())
            // {
            //     shift = 0;
            //     btoken = bitset<8>(tokens[++i]);
            //     res += ' ';
            //     continue;
            // }

            int offset = BITS_IN_BYTE - shift;
            shift += BITS_IN_TOKEN - BITS_IN_BYTE;

            bitset<8> extra_mask((1 << shift) - 1);
            decoded_char |= ((btoken & extra_mask) << offset);
        }
        else
        {
            shift += BITS_IN_TOKEN;
        }
        cout << decoded_char << endl;
        res += decoded_char==bitset<8>("00011111")?' ':(decoded_char.to_ulong() + ALPHA_BASE);
    }
    res.pop_back();
    return res;
}

int main()
{
    string text = "yushi q";
    auto res = test(text);
    for (int i = 0; i < res.size(); ++i)
    {
        string bs = bitset<8>(res[i]).to_string();
        reverse(bs.begin(), bs.end());
        cout << bs << ' ';
    }
    cout << '\n';

    for (int i = 0; i < text.length(); ++i)
    {
        if (text[i] != ' ')
        {
            string bs = bitset<5>(text[i] - 'a').to_string();
            reverse(bs.begin(), bs.end());
            cout << bs << ' ';
        }
    }
    cout << '\n';

    for (int i = 0; i < res.size(); ++i)
    {
        cout << (int)res[i] << endl;
    }

    cout << decodetest(res) << '\n';
    cout << bitset<8>(26) << endl;
    return 0;
}
