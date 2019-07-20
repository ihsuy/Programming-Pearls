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
Implement heap-based priority queues to run as quickly as
possible; at what values of n are they faster
than sequential structures?
*/

template <typename T>
class PriorityQueue {
    int capacity, actual_size;
    T* heap;

   public:
    PriorityQueue(const int& cap)
        : capacity(cap), actual_size(0), heap(new T[cap + 1]) {}

    void insert(const T& obj) {
        heap[++actual_size] = obj;
        int i = actual_size;
        for (int j = i; i > 1 and obj < heap[j = i / 2]; i = j) {
            heap[i] = heap[j];
        }
        heap[i] = obj;
    }

    T extractmin() {
        if (actual_size == 0) {
            throw runtime_error(
                "Can't extractmin from an empty PriorityQueue.");
        }

        auto min_val = heap[1];

        auto temp = heap[1] = heap[actual_size--];
        int i = 1, next = i;
        for (; (next *= 2) <= actual_size; i = next) {
            if (next + 1 <= actual_size and heap[next + 1] < heap[next]) {
                next++;
            }
            if (heap[next] >= temp) {
                break;
            }
            heap[i] = heap[next];
        }
        heap[i] = temp;

        return min_val;
    }

    int size() { return actual_size; }
};

template <typename T>
struct PriorityVector {
    int capacity, actual_size;
    vector<T> vec;

   public:
    PriorityVector(const int& cap)
        : capacity(cap), actual_size(0), vec(cap, 0) {}

    void insert(const T& obj) {
        int i = 0;
        for (; i < actual_size and vec[i] < obj; ++i)
            ;
        if (i == actual_size) {
            vec[i] = obj;
        } else {
            int j = actual_size;
            for (; j > i; --j) {
                vec[j] = vec[j - 1];
            }
            vec[j] = obj;
        }
        actual_size++;
    }

    T extractmin() {
        auto min_val = vec[0];
        actual_size--;
        for (int i = 0; i < actual_size; ++i) {
            vec[i] = vec[i + 1];
        }
        return min_val;
    }
    int size() { return actual_size; }
};

template <typename PriorityContainer>
void InsertTest(PriorityContainer& pc, const vector<int>& nums) {
    for (const auto& n : nums) {
        pc.insert(n);
    }
}

template <typename PriorityContainer>
void ExtractminTest(PriorityContainer& pc) {
    while (pc.size() != 0) {
        pc.extractmin();
    }
}

template <typename PriorityContainer>
pair<long long, long long> profiler(PriorityContainer& pc,
                                    const vector<int>& nums) {
    auto t1 = chrono::high_resolution_clock::now();
    InsertTest<PriorityContainer>(pc, nums);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto time1 = chrono::duration_cast<chrono::nanoseconds>(t2).count();

    t1 = chrono::high_resolution_clock::now();
    ExtractminTest<PriorityContainer>(pc);
    t2 = chrono::high_resolution_clock::now() - t1;
    auto time2 = chrono::duration_cast<chrono::nanoseconds>(t2).count();

    return {time1, time2};
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int n_lower = 2;
    const int n_upper = 1000;

    for (int n = n_lower; n <= n_upper; n <<= 1) {
        cout << "input size: " << n << '\n';
        vector<int> nums;
        nums.reserve(n);
        for (int i = 0; i < n; ++i) {
            nums.push_back(rand() % n);
        }
        PriorityQueue<int> pq(n);
        auto res1 = profiler<PriorityQueue<int>>(pq, nums);

        PriorityVector<int> pv(n);
        auto res2 = profiler<PriorityVector<int>>(pv, nums);

        cout << "pq insertion time: " << res1.first
             << " extractmin time: " << res1.second << '\n';
        cout << "pv insertion time: " << res2.first
             << " extractmin time: " << res2.second << '\n';
    }

    // PriorityQueue<int> pq(20);

    // for(int i = 20; i > 0; --i)
    // {
    //     pq.insert(i);
    // }
    // while(pq.size() != 0)
    // {
    //     cout << pq.extractmin() << ' ';
    // }

    return 0;
}
