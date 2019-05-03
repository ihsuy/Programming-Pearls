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
Implement heap-based priority queues to run as quickly as
possible; at what values of n are they faster
than sequential structures?
*/

template<typename T>
class PriorityQueue
{
    int capacity, actual_size;
    T* heap;

public:
    PriorityQueue(const int& cap):
        capacity(cap), actual_size(0),
        heap(new T[cap + 1])
    {}

    void insert(const T& obj)
    {
        heap[++actual_size] = obj;
        for (int i = actual_size, j = i; i > 1 and heap[i] < heap[j = i / 2]; i = j)
        {
            swap(heap[i], heap[j]);
        }
    }

    T extractmin()
    {
        if (actual_size == 0)
        {
            throw runtime_error("Can't extractmin from an empty PriorityQueue.");
        }

        auto min_val = heap[1];

        heap[1] = heap[actual_size--];

        for (int i = 1, next = i; (next *= 2) <= actual_size; i = next)
        {
            if (next + 1 <= actual_size and heap[next + 1] < heap[next])
            {
                next++;
            }

            if (heap[next] >= heap[i])
            {
                break;
            }

            swap(heap[next], heap[i]);
        }
        return min_val;
    }

    int size()
    {
        return actual_size;
    }

};

int main()
{
    PriorityQueue<int> pq(30);

    for (int i = 30; i > 0; --i)
    {
        pq.insert(i);
    }

    while (pq.size() != 0)
    {
        cout << pq.extractmin() << ' ';
    }
    cout << '\n';

    return 0;
}
