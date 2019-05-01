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
Build a “form-letter generator” that can prepare a customized document
for each record in a database (this is often referred to as a
“mail-merge” feature). Design small schemas and input files to
test the correctness of your program.
*/

const string schema_path = "/Users/ihsuy/programming_pearls/column3_Data_Structures_Programs/schema_for_problem_6.txt";

// look for field indicator $1 ~ $N in a schema file
// and replace them with field values
string form_letter_generator(const vector<string>& field_values,
                             const string schema_addr = schema_path)
{
    ifstream schema_file(schema_addr);
    if (not schema_file)
    {
        throw runtime_error("Can't find schema file at " + schema_addr);
    }
    // read the schema file into a string
    string schema{istreambuf_iterator<char>(schema_file), istreambuf_iterator<char>()};

    for (int i = 0; i < schema.length(); ++i)
    {   // find field_values
        if (schema[i] == '$')
        {
            int field_begin = i;

            i++;
            // extract field index by reading in every
            // numerical character after '$'
            string field_index_str;
            while (isnumber(schema[i]))
            {
                field_index_str += schema[i];
                i++;
            }

            int field_index = stoi(field_index_str);
            // field index should not be less than 1
            // and has to be less than number of input field values provided
            assert(field_index > 0 and field_index <= field_values.size());
            // fill in field value
            schema.replace(field_begin,
                           field_index_str.length() + 1,
                           field_values[field_index - 1]);

            i = field_begin + field_index_str.length();
        }
    }

    return schema;
}

int main()
{
    string recipient = "Bob";
    string sender = "ihsuy";
    string event = "MY ABSOLUTELY AWESOME PARTY";
    string date = "April 22th 2019";

    vector<string> field_values {recipient, sender, event, date};

    cout << form_letter_generator(field_values) << '\n';

    return 0;
}
