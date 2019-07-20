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
Modify siftdown to have the following specification.
void siftdown(l, u)
        pre   heap(l+1, u)
        post  heap(l, u)

What is the run time of the code? Show how it can be used to
construct an n-element heap in O(n) time and thereby a faster
Heapsort that also uses less code.
*/

/*
some result sorting various sized arrays
size: 1024
heapsort1: 173784
heapsort2: 151924
stl sort:  53120
size: 2048
heapsort1: 376696
heapsort2: 308627
stl sort:  105917
size: 4096
heapsort1: 826691
heapsort2: 675500
stl sort:  229929
size: 8192
heapsort1: 1528878
heapsort2: 1214641
stl sort:  419179
size: 16384
heapsort1: 2973528
heapsort2: 2405803
stl sort:  850151
size: 32768
heapsort1: 6806153
heapsort2: 5383589
stl sort:  1809390
size: 65536
heapsort1: 13789503
heapsort2: 12664651
stl sort:  3906044
size: 131072
heapsort1: 28820432
heapsort2: 27315402
stl sort:  7953098
size: 262144
heapsort1: 68360424
heapsort2: 44243740
stl sort:  13445876
size: 524288
heapsort1: 94735621
heapsort2: 82891908
stl sort:  28065201
size: 1048576
heapsort1: 195004373
heapsort2: 176318780
stl sort:  59116338
size: 2097152
heapsort1: 412456241
heapsort2: 389815916
stl sort:  123581196
size: 4194304
heapsort1: 1047137355
heapsort2: 934604437
stl sort:  250125901
size: 8388608
heapsort1: 2550097562
heapsort2: 2372173015
stl sort:  528245435
*/

void siftdown0_min(int* nums, const int& n) {
    int i = 1;
    auto temp = nums[i];
    for (int j = i; (j *= 2) <= n; i = j) {
        if (j + 1 <= n and nums[j + 1] < nums[j]) {
            j++;
        }
        if (nums[j] >= temp) {
            break;
        }
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void siftdown_min(int* nums, const int& l, const int& u) {
    int i = l;
    auto temp = nums[l];
    for (int j = i; (j *= 2) <= u; i = j) {
        if (j + 1 <= u and nums[j + 1] < nums[j]) {
            j++;
        }
        if (nums[j] >= temp) {
            break;
        }
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void siftup_min(int* nums, const int& n) {
    int i = n;
    auto temp = nums[n];
    for (int j = i; i > 1 and nums[j /= 2] > temp; i = j) {
        nums[i] = nums[j];
    }
    nums[i] = temp;
}

void HeapSort1(int* nums, const int& size) {  // build the heap
    for (int i = 1; i <= size; ++i) {
        siftup_min(nums, i);
    }
    // build array
    for (int i = size; i > 1; --i) {
        swap(nums[1], nums[i]);
        siftdown0_min(nums, i - 1);
    }
}

void HeapSort2(int* nums, const int& size) {  // build the heap
    for (int i = size / 2; i >= 1; --i) {
        siftdown_min(nums, i, size);
    }
    // build array
    for (int i = size; i > 1; --i) {
        auto temp = nums[1];
        nums[1] = nums[i];
        nums[i] = temp;
        siftdown_min(nums, 1, i - 1);
    }
}

void STLSort(int* nums, const int& size) {
    sort(nums + 1, nums + size + 1);
}

long long profiler(void(HeapSort)(int*, const int&),
                   int* nums,
                   const int& size) {
    auto t1 = chrono::high_resolution_clock::now();
    HeapSort(nums, size);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    return chrono::duration_cast<chrono::nanoseconds>(t2).count();
}

int* arrgen(const int& size) {
    int* arr = new int[size + 1];
    for (int i = 0; i <= size; ++i) {
        arr[i] = rand() % size;
    }
    return arr;
}

int main() {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    for (int sz = (1 << 10); sz <= (1 << 25); sz <<= 1) {
        cout << "size: " << sz << endl;
        auto nums = arrgen(sz);
        auto t1 = profiler(HeapSort1, nums, sz);
        cout << "heapsort1: " << t1 << endl;
        delete nums;
        auto nums2 = arrgen(sz);
        auto t2 = profiler(HeapSort2, nums2, sz);
        cout << "heapsort2: " << t2 << endl;
        delete nums2;
        auto nums3 = arrgen(sz);
        auto t3 = profiler(STLSort, nums3, sz);
        cout << "stl sort:  " << t3 << endl;
        delete nums3;
    }

    return 0;
}
