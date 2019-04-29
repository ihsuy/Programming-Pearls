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

const string original_addr = "/Users/ihsuy/programming_pearls/engWords.txt";
const string decoded_addr = "/Users/ihsuy/programming_pearls/decoded_engWords.txt";
const string compressed_addr = "/Users/ihsuy/programming_pearls/compressed_engWords.txt";

// My method squeezes 1 alphabet into 5 bits
// and squeeze 8 such alphabet into 5 bytes
// 5 bytes             00000000 00000000 00000000 00000000 00000000
// squeeze in 8 chars  xxxxxppp ppxxxxxp ppppxxxx xpppppxx xxxppppp
//
// result from compressing 370100 English words:
// compressing time     : 37 milliseconds
// decoding time        : 86 milliseconds
// original file size   : 4.2 MB
// compressed file size : 2.4 MB
// compression ratio    : 0.57 (almost halved the size)

// Note: 
// A minor bug: since the last byte is sometimes uncompleted
// sometimes the last character in the whole file isn't 
// decoded properly for some reason... I'll think about it!

// the code is a little bit hard to read and explain so I will be
// adding more detailed explaination and comments when i got time!

#define BITS_IN_BYTE 8
#define BITS_IN_TOKEN 5
#define ALPHA_BASE 97

const char sep_token = '|';
const int compressed_sep = sep_token - ALPHA_BASE;
bitset<8> token_mask("00011111");


void CompressDict()
{
    ifstream dict(original_addr);
    ofstream compressed_dict(compressed_addr);
    // error checking omitted here
    char c = 0, encoded_token = 0;
    for (string word; dict >> word;)
    {
        word += sep_token;
        auto word_len = word.length();

        for (int i = 0; i < word_len; ++i)
        {
            char compressed_char = word[i] - ALPHA_BASE;
            encoded_token |= (compressed_char << c);

            c += BITS_IN_TOKEN;

            if (c >= BITS_IN_BYTE)
            {
                compressed_dict << encoded_token;

                c -= BITS_IN_BYTE;
                encoded_token = (compressed_char >> (BITS_IN_TOKEN - c));
            }
        }
    }
}

void DecodeDict()
{
    ifstream compressed_dict(compressed_addr);
    ofstream decoded_dict(decoded_addr);

    bitset<8> encoded_byte(compressed_dict.get());

    for (int shift = 0; compressed_dict;)
    {
        bitset<8> decoded_key = (encoded_byte >> shift) & token_mask;

        if (BITS_IN_TOKEN + shift > BITS_IN_BYTE)
        {
            encoded_byte = bitset<8>(compressed_dict.get());

            int offset = BITS_IN_BYTE - shift;
            shift += BITS_IN_TOKEN - BITS_IN_BYTE;
            decoded_key |= ((encoded_byte & bitset<8>((1 << shift) - 1)) << offset);
        }
        else
        {
            shift += BITS_IN_TOKEN;
        }

        decoded_dict << ((decoded_key.to_ulong() == compressed_sep) ?
                         '\n' : (char)(decoded_key.to_ulong() + ALPHA_BASE));
    }
}

long long profiler(void(f)())
{
    auto t1 = chrono::high_resolution_clock::now();
    f();
    auto t2 = chrono::high_resolution_clock::now() - t1;
    return chrono::duration_cast<chrono::milliseconds>(t2).count();
}

void test()
{
    ifstream original(original_addr);
    ifstream decoded(decoded_addr);

    string token1, token2;
    int count = 0;
    while (original >> token1 and decoded >> token2)
    {
        count ++;
        if (token1 != token2)
        {
            cout << token1 << " != " << token2 << endl;
        }
    }
    cout << "total words tested: " << count << '\n';
}

int main()
{   
    cout << "Compressing 370100 words...\n";
    auto compress_time = profiler(CompressDict);
    cout << "Completed\n";
    cout << "Decoding...\n";
    auto decode_time = profiler(DecodeDict);
    cout << "Completed\n";
    cout << "Testing...\n";
    test();
    cout << "Completed\n";
    cout << "result:\n";
    cout << "compress time : " << compress_time << " milliseconds\n";
    cout << "decode time   : " << decode_time << " milliseconds\n";
    return 0;
}
