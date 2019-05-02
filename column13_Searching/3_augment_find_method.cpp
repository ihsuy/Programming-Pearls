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
Augment the set classes with a find function that tells whether
a given element is in the set. Can you implement that
function to be more efficient than insert?
*/


class IntSetArray
{
    int* S;
    int sz;
public:
    IntSetArray(const int& maxelements, const int& maxval)
    {
        S = new int[maxelements + 1];
        S[0] = maxval;
        sz = 0;
    }
    void insert(const int& t)
    {
        int i = 0;
        for (; S[i] < t; ++i);

        if (S[i] == t)
        {
            return;
        }

        for (int j = sz; j >= i; --j)
        {
            S[j + 1] = S[j];
        }

        S[i] = t;
        sz++;
    }

    bool find(const int& t)
    {
        int i = 0;
        for (; S[i] < t; ++i);
        return S[i] == t;
    }

    int size()
    {
        return sz;
    }
    void report(int* v)
    {
        for (int i = 0; i < sz; ++i)
        {
            v[i] = S[i];
        }
    }
    ~IntSetArray()
    {
        delete S;
    }
};

class IntSetList
{
    struct node
    {
        int val;
        node* next;
        node(const int& val, node* nx): val(val), next(nx) {}
    };
    int sz;
    node *head, *sentinel;

public:

    IntSetList(const int& maxelements, const int& maxval)
        : sz(0)
    {
        head = new node(maxval, nullptr);
        sentinel = head;

    }
    void insert(const int& num)
    {
        if (head->next == nullptr)
        {
            head = new node(num, head);
            sz++;
            return;
        }

        node* temp = head;
        while (temp->next->val < num)
        {
            temp = temp->next;
        }
        if (temp->next->val == num)
        {
            return;
        }
        temp->next = new node(num, temp->next);
        sz++;
    }

    bool find(const int& num)
    {
        node* temp = head;
        while (temp->val < num)
        {
            temp = temp->next;
        }
        return temp->val == num;
    }

    int size()
    {
        return sz;
    }
    void report(int* v)
    {
        int i = 0;
        node* temp = head;
        while (temp != sentinel)
        {
            v[i++] = temp->val;
            temp = temp->next;
        }
    }

    void DestroyList(node* ptr)
    {
        if (ptr->next == nullptr)
        {
            return;
        }
        DestroyList(ptr->next);
        delete ptr;
    }
    ~IntSetList()
    {
        DestroyList(head);
    }
};

class IntSetBST
{
    struct node
    {
        int val;
        node* left, *right;
        node(const int& v, node* l, node* r)
            : val(v), left(l), right(r) {}
    };
    node* root;
    int sz;

public:

    IntSetBST(const int& maxelements, const int& maxval)
        : root(nullptr), sz(0) {}
    void insert(const int& num)
    {
        if (root == nullptr)
        {
            root = new node(num, nullptr, nullptr);
            sz++;
            return;
        }

        node* temp = root, *savetemp = root;
        while (temp != nullptr)
        {
            savetemp = temp;
            if (temp->val > num)
            {
                temp = temp->left;
            }
            else if (temp->val < num)
            {
                temp = temp->right;
            }
            else
            {
                return;
            }
        }

        if (savetemp->val > num)
        {
            savetemp->left = new node(num, nullptr, nullptr);
        }
        else
        {
            savetemp->right = new node(num, nullptr, nullptr);
        }
        sz++;
    }

    bool find(const int& num)
    {
        auto temp = root;
        while (temp != nullptr)
        {
            if (temp->val > num)
            {
                temp = temp->left;
            }
            else if (temp->val < num)
            {
                temp = temp->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    void InOrderTraverse(node* root, int* v, int& i)
    {
        if (root == nullptr)
        {
            return;
        }

        InOrderTraverse(root->left, v, i);
        v[i++] = root->val;
        InOrderTraverse(root->right, v, i);
    }

    void report(int* v)
    {
        int i = 0;
        InOrderTraverse(root, v, i);
    }

    int size()
    {
        return sz;
    }
};

/*
IntSetImp(int maxelements, int maxval);
    void insert(int t);
    int size();
    void report(int *v);
*/

class IntSetBitVec
{
    enum {SHIFT = 5, MASK = 0x1f};
    int* bits;
    int sz, capacity;

    void set(const int& i)
    {
        bits[i >> SHIFT] |= (1 << (i & MASK));
    }

    void clr(const int& i)
    {
        bits[i >> SHIFT] &= ~(1 << (i & MASK));
    }

    bool test(const int& i)
    {
        return bits[i >> SHIFT] & (1 << (i & MASK));
    }

public:
    IntSetBitVec(const int& maxelements, const int& maxval):
        bits(new int[(maxval >> SHIFT) + 1]), sz(0), capacity(maxval)
    {
        //memset(bits, 0, maxelements);
        for (int i = 0; i < capacity; ++i)
        {
            clr(i);
        }
    }

    int size()
    {
        return sz;
    }

    void insert(const int& num)
    {
        if (!test(num))
        {
            set(num);
            sz++;
        }
    }

    bool find(const int& num)
    {
        return test(num);
    }

    void report(int* v)
    {
        for (int i = 0, j = 0; i < capacity; ++i)
        {
            if (test(i))
            {
                v[j++] = i;
            }
        }
    }
};

class IntSetBin
{
    struct node
    {
        int val;
        node* next;
        node(const int& v, node* nx): val(v), next(nx) {}
    };
    node** bins;
    node* sentinel;
    int sz, nbins, max_value;

public:

    IntSetBin(const int& maxelements, const int& maxval)
        : sentinel(new node(maxval, nullptr)),
          sz(0), nbins(maxelements), max_value(maxval)
    {
        bins = new node*[nbins];
        for (int i = 0; i < nbins; ++i)
        {
            bins[i] = sentinel;
        }
    }

    int size ()
    {
        return sz;
    }

    void insert(const int& num)
    {
        int choice = num / (1 + (max_value / nbins));

        if (bins[choice]->next == nullptr)
        {
            bins[choice] = new node(num, bins[choice]);
            sz++;
            return;
        }

        auto temp = bins[choice];

        while (temp->next->val < num)
        {
            temp = temp->next;
        }

        if (temp->next->val == num)
        {
            return;
        }

        temp->next = new node(num, temp->next);
        sz++;
    }

    bool find(const int& num)
    {
        auto temp = bins[num / (1 + (max_value / nbins))];
        while (temp->val < num)
        {
            temp = temp->next;
        }
        return temp->val == num;
    }

    void report(int* v)
    {
        for (int i = 0, j = 0; i < nbins; ++i)
        {
            auto temp = bins[i];
            while (temp->val < max_value)
            {
                v[j++] = temp->val;
                temp = temp->next;
            }
        }
    }
};

template<typename IntSet>
void genset(const int& m, const int& n, int* v, IntSet& s)
{
    while (s.size() != m)
    {
        s.insert(rand() % n);
    }
    s.report(v);
}

template<typename IntSet>
void genset_floyd(const int& m, const int& n, int* v, IntSet& s)
{
    for (int i = n - m; i < n; ++i)
    {
        int select = rand() % (i + 1);
        if (s.find(select))
        {
            s.insert(i);
        }
        else
        {
            s.insert(select);
        }
    }
    s.report(v);
}

template<typename IntSet>
void profiler(void(gs)(const int&, const int&, int*, IntSet&),
              const int& m, const int& n, int* v, const string& name)
{
    IntSet s(m, n);
    auto t1 = chrono::high_resolution_clock::now();
    gs(m, n, v, s);
    auto t2 = chrono::high_resolution_clock::now() - t1;
    auto t = chrono::duration_cast<chrono::microseconds>(t2).count();
    cout << "data structure: " << name << " time spent: " << t << " microseconds\n";
}

/*
Results on small m, n
When m is far smaller than n
Floyd's algorithm performs very close to or even a little bit worse than
the naive set-based method
However when m get's closer to n, Floyd's algorithm out plays naive method
by approximately factor of 2
when m == n, Floyd's method using IntSetBitVec implementation is 7 times faster
than the naive method using the same set implementation

m: 10000 n: 1000000
data structure: IntSetBitVec time spent: 4043 microseconds
data structure: IntSetBin time spent: 1263 microseconds
data structure: Floyd IntSetBitVec time spent: 3934 microseconds
data structure: Floyd IntSetBin time spent: 1332 microseconds
m: 20000 n: 1000000
data structure: IntSetBitVec time spent: 4050 microseconds
data structure: IntSetBin time spent: 2408 microseconds
data structure: Floyd IntSetBitVec time spent: 4119 microseconds
data structure: Floyd IntSetBin time spent: 2710 microseconds
m: 30000 n: 1000000
data structure: IntSetBitVec time spent: 4301 microseconds
data structure: IntSetBin time spent: 4367 microseconds
data structure: Floyd IntSetBitVec time spent: 4341 microseconds
data structure: Floyd IntSetBin time spent: 3949 microseconds
m: 40000 n: 1000000
data structure: IntSetBitVec time spent: 4642 microseconds
data structure: IntSetBin time spent: 5456 microseconds
data structure: Floyd IntSetBitVec time spent: 4562 microseconds
data structure: Floyd IntSetBin time spent: 5586 microseconds
m: 50000 n: 1000000
data structure: IntSetBitVec time spent: 4807 microseconds
data structure: IntSetBin time spent: 6772 microseconds
data structure: Floyd IntSetBitVec time spent: 4905 microseconds
data structure: Floyd IntSetBin time spent: 7209 microseconds

m get closer to n 

m: 500000 n: 1000000
data structure: IntSetBitVec time spent: 26298 microseconds
data structure: IntSetBin time spent: 99416 microseconds
data structure: Floyd IntSetBitVec time spent: 22648 microseconds
data structure: Floyd IntSetBin time spent: 89848 microseconds
m: 600000 n: 1000000
data structure: IntSetBitVec time spent: 27808 microseconds
data structure: IntSetBin time spent: 128175 microseconds
data structure: Floyd IntSetBitVec time spent: 26483 microseconds
data structure: Floyd IntSetBin time spent: 108557 microseconds
m: 700000 n: 1000000
data structure: IntSetBitVec time spent: 33304 microseconds
data structure: IntSetBin time spent: 162257 microseconds
data structure: Floyd IntSetBitVec time spent: 28516 microseconds
data structure: Floyd IntSetBin time spent: 158706 microseconds
m: 800000 n: 1000000
data structure: IntSetBitVec time spent: 40107 microseconds
data structure: IntSetBin time spent: 188847 microseconds
data structure: Floyd IntSetBitVec time spent: 29533 microseconds
data structure: Floyd IntSetBin time spent: 156116 microseconds
m: 900000 n: 1000000
data structure: IntSetBitVec time spent: 51881 microseconds
data structure: IntSetBin time spent: 230637 microseconds
data structure: Floyd IntSetBitVec time spent: 28022 microseconds
data structure: Floyd IntSetBin time spent: 173586 microseconds

m: 950000 n: 1000000
data structure: IntSetBitVec time spent: 53689 microseconds
data structure: IntSetBin time spent: 242934 microseconds
data structure: Floyd IntSetBitVec time spent: 28218 microseconds
data structure: Floyd IntSetBin time spent: 175818 microseconds
m: 960000 n: 1000000
data structure: IntSetBitVec time spent: 57815 microseconds
data structure: IntSetBin time spent: 247678 microseconds
data structure: Floyd IntSetBitVec time spent: 25987 microseconds
data structure: Floyd IntSetBin time spent: 184075 microseconds
m: 970000 n: 1000000
data structure: IntSetBitVec time spent: 61119 microseconds
data structure: IntSetBin time spent: 257560 microseconds
data structure: Floyd IntSetBitVec time spent: 27692 microseconds
data structure: Floyd IntSetBin time spent: 175705 microseconds
m: 980000 n: 1000000
data structure: IntSetBitVec time spent: 64208 microseconds
data structure: IntSetBin time spent: 251932 microseconds
data structure: Floyd IntSetBitVec time spent: 25488 microseconds
data structure: Floyd IntSetBin time spent: 182471 microseconds
m: 990000 n: 1000000
data structure: IntSetBitVec time spent: 71390 microseconds
data structure: IntSetBin time spent: 264398 microseconds
data structure: Floyd IntSetBitVec time spent: 27427 microseconds
data structure: Floyd IntSetBin time spent: 180314 microseconds

m: 1000000 n: 1000000
data structure: IntSetBitVec time spent: 153551 microseconds
data structure: IntSetBin time spent: 261013 microseconds
data structure: Floyd IntSetBitVec time spent: 25300 microseconds
data structure: Floyd IntSetBin time spent: 174386 microseconds
*/
int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int max_n = 1000000;
    const int min_m = 990000;
    const int max_m = 1000000;
    for (int m = min_m; m <= max_m; m += 10000)
    {
        cout << "m: " << m << " n: " << max_n << '\n';
        int v[m];
        // profiler(genset_floyd<IntSetSTL>, m, max_n, v, "IntSetSTL");
        // profiler(genset_floyd<IntSetArray>, m, max_n, v, "IntSetArray");
        // profiler(genset_floyd<IntSetList>, m, max_n, v, "IntSetList");
        // profiler(genset_floyd<IntSetBST>, m, max_n, v, "IntSetBST");
        profiler<IntSetBitVec>(genset<IntSetBitVec>, m, max_n, v, "IntSetBitVec");
        profiler<IntSetBin>(genset<IntSetBin>, m, max_n, v, "IntSetBin");

        profiler<IntSetBitVec>(genset_floyd<IntSetBitVec>, m, max_n, v, "Floyd IntSetBitVec");
        profiler<IntSetBin>(genset_floyd<IntSetBin>, m, max_n, v, "Floyd IntSetBin");
    }
    return 0;
}