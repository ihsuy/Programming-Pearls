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
#include <iomanip>

typedef long long ll;
template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
In the early 1960’s,
Vic Vyssotsky worked with a programmer who had to
transpose a 4000-by-4000 matrix stored on magnetic
tape (each record had the same format in several dozen bytes).
The original program his colleague suggested would have
taken fifty hours to run; how did Vyssotsky reduce
the run time to half an hour?
*/

void matrix_show(const vector<int>& tape, const int& n_row)
{	// display a flat matrix(1d vector) in 2D
	if (tape.size() % n_row != 0)
	{
		cout << "Can't display. Wrong row number\n";
	}

	int n_col = tape.size() / n_row;
	for (int i = 0; i < n_row; ++i)
	{
		int base = n_col*i;
		for(int j = 0; j < n_col; ++j)
		{
			cout << setw(4) << left << tape[base+j] << ' ';
		}
		cout << '\n';
	}
}

void transpose(vector<int>& matrix_tape, const int& n_row)
{	// transpose a matrix stored in format of 1d tape
	if (matrix_tape.size() % n_row != 0)
	{
		cout << "Can't display. Wrong row number\n";
	}

	int n_col = matrix_tape.size() / n_row;
	// mark every entry using its column and row number 
	// note this process generate "marked_matrix_tape" 
	// with its row numbers sorted in ascending order
	vector<pair<int, pair<int, int>>> marked_matrix_tape;
	for (int i = 0; i < n_row; ++i)
	{
		int base = n_col*i;
		for(int j = 0; j < n_col; ++j)
		{
			marked_matrix_tape.push_back({matrix_tape[base+j], {i, j}});
		}
	}

	// stable sort with respect to column number
	stable_sort(marked_matrix_tape.begin(), marked_matrix_tape.end(), [](const pair<int, pair<int, int>>& p1,const pair<int, pair<int, int>>& p2)
	{
		return p1.second.second < p2.second.second;
	});

	// remove nrow ncol markers and write back to the original tape
	for(int i = 0; i < matrix_tape.size(); ++i)
	{
		matrix_tape[i] = marked_matrix_tape[i].first;
	}
}

int main()
{
	int n_row = 4000;
	int n_entry_in_matrix = n_row*n_row;
	cout << "creating a matrix in tape\n";
	vector<int> matrix_tape;
	for(int i = 1; i <= n_entry_in_matrix; ++i)
	{
		matrix_tape.push_back(i);
	}

	//cout << "original matrix:\n";
	//matrix_show(matrix_tape, n_row);

	cout << "transposing...\n";
	transpose(matrix_tape, n_row);
	cout << "completed\n";
	//matrix_show(matrix_tape, n_row);
	return 0;
}
