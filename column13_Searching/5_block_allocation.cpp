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
Section 9.1 and Solution 9.2 describe how Chris Van Wyk
avoided many calls to a storage allocator by keeping a
collection of available nodes in his own structure.
Show how that same idea applies to IntSets implemented by
lists, bins and binary search trees.
*/

class IntSetList
{
    struct node
    {
        int val;
        node* next;
        node(const int& v, node* nx): val(v), next(nx) {}
        node* update(const int& v, node* ptr)
        {val = v; next = ptr; return this;}
    };
    int sz, fn;
    node *head, *sentinel, **free_nodes;
public:
    IntSetList(const int& maxelements, const int& maxval)
        : sz(0), fn(0), free_nodes(new node * [maxelements + 1])
    {
        for (int i = 0; i < maxelements + 1; ++i)
        {
            free_nodes[i] = new node(0, nullptr);
        }

        head = free_nodes[fn++]->update(maxval, nullptr);

        sentinel = head;
    }
    void insert(const int& num)
    {
        if (head->next == nullptr or head->val > num)
        {
            head = free_nodes[fn++]->update(num, head);
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
        temp->next = free_nodes[fn]->update(num, temp->next); fn++;
        sz++;
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
        node* update(const int& v, node* l, node* r)
        {val = v; left = l; right = r; return this;}
    };
    node* root, **free_nodes;
    int sz, fn;

public:

    IntSetBST(const int& maxelements, const int& maxval)
        : root(nullptr), free_nodes(new node * [maxelements + 1]),
          sz(0), fn(0)
    {
        for (int i = 0; i < maxelements + 1; ++i)
        {
            free_nodes[i] = new node(0, nullptr, nullptr);
        }
    }

    void insert(const int& num)
    {
        if (root == nullptr)
        {
            root = free_nodes[fn++]->update(num, nullptr, nullptr);
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
            savetemp->left = free_nodes[fn++]->update(num, nullptr, nullptr);
        }
        else
        {
            savetemp->right = free_nodes[fn++]->update(num, nullptr, nullptr);
        }
        sz++;
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
    enum {BITSPERWORD = 32, SHIFT = 5, MASK = 0x1f};
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
        node* update(const int& v, node* ptr)
        {val = v; next = ptr; return this;}
    };
    node **bins, *sentinel, **free_nodes;
    int sz, fn, nbins, max_value;

public:

    IntSetBin(const int& maxelements, const int& maxval)
        : sentinel(new node(maxval, nullptr)),
          free_nodes(new node * [maxelements + 1]),
          sz(0), fn(0), nbins(maxelements), max_value(maxval)
    {
        for (int i = 0; i < maxelements + 1; ++i)
        {
            free_nodes[i] = new node(0, nullptr);
        }

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

        if (bins[choice]->next == nullptr or bins[choice]->val > num)
        {
            bins[choice] = free_nodes[fn++]->update(num, bins[choice]);
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
        temp->next = free_nodes[fn++]->update(num, temp->next);
        sz++;
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


/*
block allocation of nodes did improve the runtime
but the improvement varies depending on n and m
: 10000 n: 1000000
data structure: IntSetBitVec time spent: 4098 microseconds
data structure: IntSetBin time spent: 578 microseconds
data structure: IntSetBitVec time spent: 4030 microseconds
data structure: IntSetBin time spent: 574 microseconds
m: 20000 n: 1000000
data structure: IntSetBitVec time spent: 4074 microseconds
data structure: IntSetBin time spent: 1142 microseconds
data structure: IntSetBitVec time spent: 4163 microseconds
data structure: IntSetBin time spent: 1275 microseconds
m: 30000 n: 1000000
data structure: IntSetBitVec time spent: 4383 microseconds
data structure: IntSetBin time spent: 2589 microseconds
data structure: IntSetBitVec time spent: 4292 microseconds
data structure: IntSetBin time spent: 3213 microseconds
m: 40000 n: 1000000
data structure: IntSetBitVec time spent: 4689 microseconds
data structure: IntSetBin time spent: 3571 microseconds
data structure: IntSetBitVec time spent: 5026 microseconds
data structure: IntSetBin time spent: 3582 microseconds
m: 50000 n: 1000000
data structure: IntSetBitVec time spent: 5217 microseconds
data structure: IntSetBin time spent: 4355 microseconds
data structure: IntSetBitVec time spent: 5029 microseconds
data structure: IntSetBin time spent: 3867 microseconds
*/

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
        auto select = rand() % (i + 1), 
        sz = s.size();
        s.insert(select);
        if (s.size() == sz)
        {
            s.insert(i);
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

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int max_n = 1000000;
    const int min_m = 10000;
    const int max_m = 100000;
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
        profiler<IntSetBitVec>(genset_floyd<IntSetBitVec>, m, max_n, v, "IntSetBitVec");
        profiler<IntSetBin>(genset_floyd<IntSetBin>, m, max_n, v, "IntSetBin");
    }
    return 0;
}
