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
inline int two(int n) {
    return 1 << n;
}
inline int test(int n, int b) {
    return (n >> b) & 1;
}
inline void set_bit(int& n, int b) {
    n |= two(b);
}
inline void unset_bit(int& n, int b) {
    n &= ~two(b);
}
inline int last_bit(int n) {
    return n & (-n);
}
inline int ones(int n) {
    int res = 0;
    while (n && ++res)
        n -= n & (-n);
    return res;
}
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
Write functions for the following date problems:
given two dates, compute the number of days between them;
given a date, return its day of the week; given a month and year,
produce a calendar for the month as an array of characters.
*/

// index starting from 1 (days in jan),
// 0 index shouldn't be accessed
const vector<int> day_in_month /*common year*/
    {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

constexpr int days_in_common_year = 365;
constexpr int days_in_leap_year = 366;

// algorithem for determining leap year and common year (from wikipedia)
// if (year is not divisible by 4) then (it is a common year)
// else if (year is not divisible by 100) then (it is a leap year)
// else if (year is not divisible by 400) then (it is a common year)
// else (it is a leap year)
bool isLeapYear(const int& year) {
    if (year % 4 != 0) {
        return false;
    } else if (year % 100 != 0) {
        return true;
    } else if (year % 400 != 0) {
        return false;
    } else {
        return true;
    }
}

struct Date {
    int day, month, year;
    Date(const int& d, const int& m, const int& y)
        : day(d),
          month(m),
          year(y) {  // some date format checking (no rigirous)
        assert(d > 0 and d <= 31);
        assert(m > 0 and m <= 12);
        assert(y >= 0 and y <= 9999);
    }

    bool operator>(const Date& another_date) const {
        if (year > another_date.year or
            (year == another_date.year and month > another_date.month) or
            (year == another_date.year and month == another_date.month and
             day > another_date.day)) {
            return true;
        }
        return false;
    }
};

// return number of days in month within year
int DayInMonth(const int& m, const int& y) {
    if (m != 2) {
        return day_in_month[m];
    } else {
        return isLeapYear(y) ? day_in_month[m] + 1 : day_in_month[m];
    }
}

int WholeYearDifferenceInDays(const Date& date1, const Date& date2) {
    int whole_year_difference_in_days = 0;
    for (int y = date1.year + 1; y < date2.year; ++y) {
        whole_year_difference_in_days +=
            isLeapYear(y) ? days_in_leap_year : days_in_common_year;
    }
    return whole_year_difference_in_days;
}

int DaysLeftInYear(const Date& date) {
    // first calculate days until the end of date.month
    int days_left_in_month = DayInMonth(date.month, date.year) - date.day;

    // calculate days from date.day to end of date1.year

    // then count days in full month left in date.year
    int days_left_in_year = days_left_in_month;
    for (int m = date.month + 1; m <= 12 /*number of month in year*/; ++m) {
        days_left_in_year += DayInMonth(m, date.year);
    }

    return days_left_in_year;
}

int DaysPastInYear(const Date& date) {  // next calculate number days from first
                                        // day of date.year
    // to date.day
    int days_before_month = 0;
    for (int m = 1; m < date.month; ++m) {
        days_before_month += DayInMonth(m, date.year);
    }

    return days_before_month + date.day;
}

// problem 1:
// given two dates, compute the number of days between them

// computes number of days between date1 exclusive and date2
int DistanceBetweenDays(const Date& date1, const Date& date2) {
    if (date1 > date2) {  // make sure date1 is an earlier day than date2
        return DistanceBetweenDays(date2, date1);
    }

    // checks if two days are in different years
    if (date1.year != date2.year) {
        int days_after_date1_day = DaysLeftInYear(date1);
        int days_before_date2_day = DaysPastInYear(date2);

        return days_after_date1_day + days_before_date2_day +
               WholeYearDifferenceInDays(date1, date2);
    } else if (date1.month !=
               date2.month) {  // if date1 and date2 are within the same year
                               // but not the same month
        // calculates days in whole months between them
        int days_between_date1_and_date2_month = 0;
        for (int m = date1.month + 1; m < date2.month; ++m) {
            days_between_date1_and_date2_month += DayInMonth(m, date1.year);
        }

        // add days left in the earlier date's month and later date's day
        return DayInMonth(date1.month, date1.year) - date1.day + date2.day +
               days_between_date1_and_date2_month;
    } else {  // same year same month
        return date2.day - date1.day;
    }
}

// problem 2
// given a date, return its day of the week

/*
Zeller's Rule (cited from http://mathforum.org/dr.math/faq/faq.calendar.html)
Only work for the Gregorian calendar
"f = k + [(13*m-1)/5] + D + [D/4] + [C/4] - 2*C,

k is the day of the month. Let's use January 29,
2064 as an example. For this date, k = 29.

m is the month number. Months have to be counted specially
for Zeller's Rule: March is 1, April is 2, and so on to February,
which is 12. (This makes the formula simpler, because on leap years
February 29 is counted as the last day of the year.) Because of
this rule, January and February are always counted as the 11th and
12th months of the previous year. In our example, m = 11.

D is the last two digits of the year. Because in our example we are
using January (see previous bullet) D = 63 even though
we are using a date from 2064.

C stands for century: it's the first two digits of the year.
In our case, C = 20.

Once we have found f, we divide it by 7 and take the remainder."
*/

int DayOfTheWeek(const Date& date) {
    int k = date.day;
    int m = (date.month - 2 <= 0) ? date.month + 12 : date.month - 2;
    int D = date.year % 100 - ((m == 11 or m == 12) ? 1 : 0);
    int C = date.year / 100;
    return (k + (13 * m - 1) / 5 + D + D / 4 + C / 4 - 2 * C) % 7;
}

// given a month and year,
// produce a calendar for the month as an array of characters
vector<int> calendar(
    const int& m,
    const int& y) {  // this function only returns a vector of days in the month
    // if more information is needed (i.e. day of the week)
    // you can easily use methods implemented above to get them
    // and maybe change vector<int> to vector<pair<int, string>> or
    // any thing you prefer
    vector<int> output;

    int days_in_month = DayInMonth(m, y);
    for (int d = 1; d <= days_in_month; ++d) {
        output.push_back(d);
    }

    return output;
}

int main() {
    Date begin_of_20century(1, 1, 1900);
    Date begin_of_21century(1, 1, 2000);

    cout << DistanceBetweenDays(begin_of_20century, begin_of_21century) << endl;

    Date date1(22, 4, 2019);
    cout << DayOfTheWeek(date1) << endl;
    return 0;
}
