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
“Consider the problem of finding all the anagrams of a
given input word. How would you solve this problem
given only the word and the dictionary? What if you
could spend some time and space to process the dictionary
before answering any queries?”
*/

const string dict_addr = "/Users/ihsuy/programming_pearls/engWords.txt";

vector<pair<string, vector<string>>> preprocess_dictionary(const string& dict_path)
{
	cout << "preprocessing dictionary...\n";
	unordered_map<string, vector<string>> table;
	ifstream input(dict_path);
	if (not input)
	{
		throw runtime_error("can't open file");
	}

	cout << "loading words and generating signatures...\n";
	string word;
	while (input >> word)
	{
		string signature = word;
		sort(signature.begin(), signature.end());
		table[signature].push_back(word);
	}

	vector<pair<string, vector<string>>> dict {table.begin(), table.end()};
	cout << "puting words in their correct locations...\n";
	sort(dict.begin(), dict.end(), [](const pair<string, vector<string>>& p1, const pair<string, vector<string>>& p2)
	{
		return p1.first < p2.first;
	});

	cout << "completed preprocessing " << dict.size() << " words\n";

	return dict;
}

vector<string> searchInDict(const string& signature, const vector<pair<string, vector<string>>>& dict)
{
	int low = 0;
	int high = dict.size() - 1;
	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (dict[mid].first == signature)
		{
			return dict[mid].second;
		}
		else if (dict[mid].first < signature)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	return {};
}

void anagram_finder()
{
	const size_t nResult_per_row = 4;
	const string terminate_command = "quit()";

	auto dict = preprocess_dictionary(dict_addr);

	while (true)
	{
		string target;
		cout << ">> ";
		getline(cin, target);
		stringstream washer(target);
		washer >> target;

		// input "quit()" to end the program
		if(target == terminate_command)
		{
			break;
		}

		// sort to get signature
		string signature = target;
		sort(signature.begin(), signature.end());

		auto search_result = searchInDict(signature, dict);

		cout << "Anagrams for " << target << " are:\n";

		if (search_result.empty())
		{
			cout << "Word not found.";
		}
		else
		{
			cout << '{';

			for (int i = 0; i < search_result.size(); ++i)
			{
				cout << search_result[i];

				if (i != search_result.size() - 1)
				{
					cout << ", ";
				}

				if (i != 0 and i != search_result.size() - 1 and i % (nResult_per_row - 1) == 0)
				{
					cout << '\n';
				}
			}
			cout << '}';
		}
		cout << '\n';
	}

}

int main()
{
	anagram_finder();

	return 0;
}
