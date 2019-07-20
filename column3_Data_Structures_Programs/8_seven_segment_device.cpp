#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

typedef long long ll;
template <typename T>
inline void inspect(T& t) {
    typename T::iterator i1 = t.begin(), i2 = t.end();
    while (i1 != i2) {
        std::cout << (*i1) << ' ';
        i1++;
    }
    std::cout << '\n';
}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Seven-segment devices provide an inexpensive
display of the ten decimal digits
Write a program that displays a 16-bit positive
integer in five seven-segment digits.
The output is an array of five bytes; bit i
of byte j is one if and only if the ith segment of
digit j should be on.
for example:
8 looks like
 _
|_|
|_|
*/

// sevenSegmentDevice input number upper limit
const int kupper_bound = (1 << 17) - 1;

// pattern to use when printing digits
// segment_fill and blank_fill must have same length
const string segment_fill = "##";
const string blank_fill = ". ";

// number of segment_fill used to draw a segment line
const int segment_width = 6;

// digit cavas height and width
const int digit_height = segment_width * 2 + 3;
const int digit_width = segment_width + 2;

// hard coded rules for number display
// 0 ~ 9 inclusive
vector<int> seven_segment_digits{
    0b1011111,  // 0
    0b0000101, 0b1110110, 0b1110101, 0b0101101,
    0b1111001, 0b1111011, 0b0010101, 0b1111111,
    0b0111101  // 9
};

void CreateSegmentBoundary(
    const int& s,
    int& upper,
    int& lower,
    int& left,
    int& right) {  // set block depends on which segment to draw
    // indiciated by s
    switch (s) {
        case 0: {
            upper = digit_height - 1;
            lower = upper;
            left = 1;
            right = left + segment_width - 1;
            break;
        }
        case 1: {
            upper = digit_height / 2;
            lower = upper;
            left = 1;
            right = left + segment_width - 1;
            break;
        }
        case 2: {
            upper = 0;
            lower = upper;
            left = 1;
            right = left + segment_width - 1;
            break;
        }
        case 3: {
            upper = 1;
            lower = upper + segment_width - 1;
            left = 0;
            right = left;
            break;
        }
        case 4: {
            upper = 1;
            lower = upper + segment_width - 1;
            left = digit_width - 1;
            right = left;
            break;
        }
        case 5: {
            upper = digit_height / 2 + 1;
            lower = digit_height - 2;
            left = 0;
            right = left;
            break;
        }
        case 6: {
            upper = digit_height / 2 + 1;
            lower = digit_height - 2;
            left = digit_width - 1;
            right = left;
            break;
        }
    }
}

void PaintSegment(
    vector<vector<bool>>& digit,
    const int& s) {  // paint(set) a block of values in "digit" to "true"
    assert(s >= 0 and s <= 6);

    // block is bounded by 4 values below
    int upper = 0, lower = 0, left = 0, right = 0;

    CreateSegmentBoundary(s, upper, lower, left, right);

    // paint
    for (int r = upper; r <= lower; ++r) {
        for (int c = left; c <= right; ++c) {
            digit[r][c] = true;
        }
    }
}

vector<vector<bool>> GenerateDigit(int d) {  // paint segments for digit d
    assert(d >= 0 and d <= 9);

    vector<vector<bool>> digit(digit_height, vector<bool>(digit_width, 0));

    bitset<7 /*problem defined*/> bit_d(seven_segment_digits[d]);

    for (int i = 0; i <= 6 /*7 segments*/; ++i) {
        if (bit_d[i]) {  // bitset index from right to left
            PaintSegment(digit, 6 - i);
        }
    }

    return digit;
}

void DisplaySevenSegmentDigits(
    vector<vector<vector<bool>>>& digits) {  // draw each digit on the screen
    assert(segment_fill.length() == blank_fill.length());

    for (int i = 0; i < digits.size(); ++i) {
        for (int r = 0; r < digit_height; ++r) {
            for (int c = 0; c < digit_width; ++c) {
                if (digits[i][r][c]) {
                    cout << segment_fill;
                } else {
                    cout << blank_fill;
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }
}

void SevenSegmentDevice(
    int n) {  // seperate n into multiple digits and draw them
    // using seven segment device
    assert(n <= kupper_bound);

    vector<vector<vector<bool>>> digits;

    for (; n; n /= 10) {
        digits.push_back(GenerateDigit(n % 10));
    }

    reverse(digits.begin(), digits.end());

    DisplaySevenSegmentDigits(digits);
}

int main() {
    const int num = 31415;
    SevenSegmentDevice(num);

    return 0;
}
