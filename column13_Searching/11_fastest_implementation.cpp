#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <math.h>
#include <utility>
#include <string>

template<typename T>
inline void inspect(T& t) {typename T::iterator i1 = t.begin(), i2 = t.end(); while (i1 != i2) {std::cout << (*i1) << ' '; i1++;} std::cout << '\n';}

/////////////////////////////////////////////////////////////
using namespace std;

/*
Build the fastest possible complete function to generate a
sorted array of random integers without duplicates.
*/

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
    // fn: index to first free node, 
    // start from 0, increment when a node is taken
    int sz, fn, nbins, shift;

public:

    IntSetBin(const int& maxelements, const int& maxval)
        : sentinel(new node(maxval, nullptr)),
          free_nodes(new node * [maxelements + 1]),
          sz(0), fn(0), shift(1)
    {   // calculate "shift" to replace division with bit operation
        int upper = maxval / maxelements;
        for (int i = 2; i < upper; i <<= 1)
        {
            shift++;
        }
        nbins = (maxval >> shift) + 1;

        // pre-allocate block of nodes
        for (int i = 0; i < maxelements + 1; ++i)
        {
            free_nodes[i] = new node(0, nullptr);
        }

        // set sentinel at the end of each bin
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
    {   // hash
        int choice = num >> shift;

        if (bins[choice] == sentinel or bins[choice]->val > num)
        {   // use a node from free nodes 
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

    bool find(const int& num)
    {   // a quick find function
        auto temp = bins[num >> shift];
        while (temp->val < num)
        {
            temp = temp->next;
        }
        if (temp->val == num)
        {
            return true;
        }
        return false;
    }

    void report(int* v)
    {
        for (int i = 0, j = 0; i < nbins; ++i)
        {
            auto temp = bins[i];
            while (temp != sentinel)
            {
                v[j++] = temp->val;
                temp = temp->next;
            }
        }
    }
};

void randGen(const int& m, const int& n, int* v)
{
    IntSetBin is(m, n);
    for (int i = n - m; i < n; ++i)
    {
        int k = rand() % (i + 1);
        if (is.find(k))
        {
            is.insert(i);
        }
        else
        {
            is.insert(k);
        }
    }
    is.report(v);
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int select = 10, total = 13000;

    int v[select];

    randGen(select, total, v);

    for (int i = 0; i < select; ++i)
    {
        cout << v[i] << ' ';
    }
    cout << '\n';

    return 0;
}
