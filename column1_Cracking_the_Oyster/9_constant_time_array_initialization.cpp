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
“One problem with trading more space to use less time is
that initializing the space can itself take a great deal of
time. Show how to circumvent this problem by designing a
technique to initialize an entry of a vector to zero the
first time it is accessed. Your scheme should use constant
time for initialization and for each vector access, and use
extra space proportional to the size of the vector. Because
this method reduces initialization time by using even more space,
it should be considered only when space is cheap, time is dear and
the vector is sparse.”
*/

struct defaultArray
{	// data structure with every value set to a specific value
	// but requires constant initialization time
	defaultArray(const int& sz, const int& default_val):
		default_value(default_val), top(0), size_(sz),
		data(new int[sz]), from(new int[sz]), to(new int[sz])
	{}

	int& operator[](const size_t& i)
	{
		if (from[i] >= top or to[from[i]] != i)
		{	// if this value has never been seen before
			// having from[i] < top makes sure that its possible
			// for i to be already in array "to"
			// but from[i] can also be < top by chance since part of it is jumbled
			// thats why we need to try "to[from[i]] == i" to make sure that this i
			// really exists in to

			from[i] = top;	
			to[top] = i;
			data[i] = default_value;
			top++;
		}
		return data[i];
	}

	int size() const
	{
		return size_;
	}

	~defaultArray()
	{
		delete[] data;
		delete[] from;
		delete[] to;
	}

private:
	int default_value; // the value ith position should hold if its never touched by user
	int top;	// number of user set value
	int size_;	// total data size
	int* data;	// actual data
	int* from;	// maps from input index to array: "to"'s index
	int* to;	// an array where its 0~top th position stores indices for all user touch datum in "data"
};

int main()
{
	defaultArray da(10000000, 5);
	for(int i = 0; i < 1000; i += 3)
	{
		da[i] = 20190101;
	}

	// get an arbitrary range
	int low = 523;
	int high = 623;
	// observe that once every 3 element, da's value is set to 20190101
	// and all other values are set to default: 5
	for(int i = low; i < high; ++i)
	{
		cout << da[i] << " ";
	}
	cout << '\n';

	return 0;
}
