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
Write functions for the following date problems:
given two dates, compute the number of days between them;
given a date, return its day of the week; given a month and year,
produce a calendar for the month as an array of characters.
*/

// index starting from 1 (days in jan),
// 0 index shouldn't be accessed
const vector<int> day_in_month /*common year*/
{
    -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

constexpr int days_in_common_year = 365;
constexpr int days_in_leap_year = 366;

// algorithem for determining leap year and common year (from wikipedia)
// if (year is not divisible by 4) then (it is a common year)
// else if (year is not divisible by 100) then (it is a leap year)
// else if (year is not divisible by 400) then (it is a common year)
// else (it is a leap year)
bool isLeapYear(const int& year)
{
    if (year % 4 != 0)
    {
        return false;
    }
    else if (year % 100 != 0)
    {
        return true;
    }
    else if (year % 400 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

struct Date
{
    int day, month, year;
    Date(const int& d, const int& m, const int& y)
        : day(d), month(m), year(y) {}

    bool operator>(const Date& another_date) const
    {
        if (year > another_date.year
                or (year == another_date.year
                    and month > another_date.month)
                or (year == another_date.year and month == another_date.month
                    and day > another_date.day))
        {
            return true;
        }
        return false;
    }
};

// return number of days in month within year
int DayInMonth(const int& m, const int& y)
{
    if (m != 2)
    {
        return day_in_month[m];
    }
    else
    {
        return isLeapYear(y) ?
               day_in_month[m] + 1 : day_in_month[m];
    }
}

// compute number of days between date1 exclusive and date2
int DistanceBetweenDays(const Date& date1, const Date& date2)
{
    if (date1 > date2)
    {   // make sure date1 is an earlier day than date2
        return DistanceBetweenDays(date2, date1);
    }

    int whole_year_difference_in_days = 0;
    for (int y = date1.year + 1; y < date2.year; ++y)
    {
        whole_year_difference_in_days += isLeapYear(y) ?
                                         days_in_leap_year
                                         : days_in_common_year;
    }

    // first calculate days until the end of date1.month
    int days_left_in_date1_month = DayInMonth(date1.month, date1.year) - date1.day;

    // check if two days are in different years
    if (date1.year != date2.year)
    {   // calculate days from date1.day to end of date1.year

        // then count days in full month left in date1.year
        int days_left_in_date1_year = days_left_in_date1_month;
        for (int m = date1.month + 1; m <= 12/*number of month in year*/; ++m)
        {
            days_left_in_date1_year += DayInMonth(m, date1.year);
        }

        // next calculate dats from first day of date2.year
        // to date2.day

        // first count days in full month before date2.month
        int days_before_date2_month = 0;
        for (int m = 1; m < date2.month; ++m)
        {
            days_before_date2_month += DayInMonth(m, date2.year);
        }

        // then add date2.day
        int days_before_date2_day = days_before_date2_month + date2.day;

        return days_left_in_date1_year + days_before_date2_day
               + whole_year_difference_in_days;
    }
    else if (date1.month != date2.month)
    {   // if date1 and date2 are within the same year but not same month

        // calculate days in whole months between them
        int days_between_date1_and_date2_month = 0;
        for (int m = date1.month + 1; m < date2.month; ++m)
        {
            days_between_date1_and_date2_month += DayInMonth(m, date1.year);
        }

        return days_left_in_date1_month + date2.day
               + days_between_date1_and_date2_month;

    }
    else
    {   // same year same month
        return date2.day-date1.day;
    }
}

int main()
{
    Date begin_of_20century(1, 1, 2000);
    Date begin_of_21century(1, 1, 2000);

    cout << DistanceBetweenDays(begin_of_20century, begin_of_21century) << endl;

    return 0;
}
