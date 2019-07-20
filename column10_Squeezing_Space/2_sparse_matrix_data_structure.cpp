#include <math.h>
#include <algorithm>
#include <bitset>
#include <chrono>
#include <fstream>
#include <iomanip>
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
“How would you write a program to build
the sparse-matrix data structure described
in Section 10.2?
Can you find other simple but space-efficient
data structures for the task?
*/

struct SparseNode {
    int row, col;
    double value;
    SparseNode(const int& r, const int& c, const double& val)
        : row(r), col(c), value(val){};
    SparseNode() : row(0), col(0), value(0.0) {}
    SparseNode(const SparseNode& sn)
        : row(sn.row), col(sn.col), value(sn.value) {}

    SparseNode& operator=(SparseNode&& other) {
        row = move(other.row);
        col = move(other.col);
        value = move(other.value);
        return *this;
    }

    SparseNode& operator=(const SparseNode& other) {
        row = other.row;
        col = other.col;
        value = other.value;
        return *this;
    }
};

// sparse matrix data structure that uses an array of "nodes"
// and a array of indices indicating where begins the first node
// in certain row
// this structure will only need exactly number of none zero element
// much of space
// this can save a alot of memory i.e. if we have a 10000x10000 matrix
// where it only has 1000 active entires
// a regular 2d array approach will force the system to allocate
// 100000000 doubles whereas the SparseMatrix only needs 1000 nodes
// and 1000 integers. Thats only 3000 integers and 1000 doubles.
// however the element retrieval will be a little bit slower but
// completely tolerable
// I also added the concept "default value" which will be conventionally
// set to 0. I also provided the "<<" operator and a random sparse
// matrix generator for quick experiment and fun
struct SparseMatrix {
    double default_value;

    int n_row, n_col, n_elements;
    vector<SparseNode> elements;
    vector<int> first_in_row;

    // constructor 1
    // build from a vector of SparseNodes
    SparseMatrix(const int& nr,
                 const int& nc,
                 vector<SparseNode>& entries,
                 const double dv = 0.0)
        : default_value(dv),
          n_row(nr),
          n_col(nc),
          n_elements(entries.size()),
          first_in_row(n_row + 1, 0) {
        elements.reserve(n_elements);

        // sort entries with repect to rows
        // Note: modifies the input vector
        sort(entries.begin(), entries.end(),
             [](SparseNode& s1, SparseNode& s2) { return s1.row < s2.row; });

        // build matrix
        for (int i = 1; i < n_elements; ++i) {
            if (entries[i - 1].row != entries[i].row) {
                for (int tmp = entries[i - 1].row + 1; tmp < entries[i].row;
                     ++tmp) {
                    first_in_row[tmp] = first_in_row[entries[i - 1].row];
                }
                first_in_row[entries[i].row] = i;
            }

            elements.push_back(entries[i]);
        }
        first_in_row.back() = n_elements;
    }

    // constructor 2: build from a 2D vector of doubles
    SparseMatrix(const vector<vector<double>>& dm, const double dv = 0.0)
        : default_value(dv),
          n_row(dm.size()),
          n_col(dm[0].size() /*assumes dm is nonempty*/),
          first_in_row(n_row + 1, 0) {  // note: this process can be optimized
        // I implemented it by first naively build a vector of SparseNodes
        // from 2d vector and basically did the same thing as the previous
        // construct
        vector<SparseNode> temp_elements;
        for (int r = 0; r < dm.size(); ++r) {
            for (int c = 0; c < dm[0].size(); ++c) {
                if (dm[r][c] !=
                    0.0)  // could use epsilon to discard small entry
                {
                    temp_elements.push_back(SparseNode(r, c, dm[r][c]));
                }
            }
        }
        n_elements = temp_elements.size();
        assert(n_elements != 0);

        // basically constructor 1
        elements.reserve(n_elements);
        elements.push_back(temp_elements[0]);

        for (int i = 1; i < n_elements; ++i) {
            if (temp_elements[i - 1].row != temp_elements[i].row) {
                for (int tmp = temp_elements[i - 1].row + 1;
                     tmp < temp_elements[i].row; ++tmp) {
                    first_in_row[tmp] = first_in_row[temp_elements[i - 1].row];
                }
                first_in_row[temp_elements[i].row] = i;
            }
            elements.push_back(temp_elements[i]);
        }
        for (int i = elements.back().row + 1; i < n_row; ++i) {
            first_in_row[i] = first_in_row[elements.back().row];
        }
        first_in_row.back() = n_elements;
        // inspect<vector<int>>(first_in_row);
    }

    // return the value of the entry at r-th row and c-th column
    double get(const size_t& r, const size_t& c) const {
        if (r >= n_row or c >= n_col) {
            throw runtime_error("index out of range");
        }

        for (int i = first_in_row[r]; i < first_in_row[r + 1]; ++i) {
            if (elements[i].col == c) {
                return elements[i].value;
            }
        }

        return default_value;
    }

    // set the value of entry at r-th row and c-th column to val
    // if the entry to be set is now "defualt value" and will be
    // set to a new value, then we need to modify n_elements
    // as well as first_in_row.
    // insert at the end of first_in_row[r] and increment every
    // index after it
    void set(const size_t& r, const size_t& c, const double& val) {
        if (r >= n_row or c >= n_col) {
            throw runtime_error("index out of range");
        }

        for (int i = first_in_row[r]; i < first_in_row[r + 1]; ++i) {
            if (elements[i].col == c) {
                elements[i].value = val;
                return;
            }
        }

        // trying to insert new value, handle it...
        // *** implement here ***
        throw runtime_error("inserting new value isn't implemented yet.");
    }
};

// show matrix
ostream& operator<<(ostream& out, const SparseMatrix& m) {
    out.precision(4);

    out << "SparseMatrix:\n{\n";

    for (int i = 0; i < m.n_row; ++i) {
        for (int j = 0; j < m.n_col; ++j) {
            out << left << setw(8) << m.get(i, j) << ' ';
        }
        out << '\n';
    }
    out << "}\n";

    return out;
}

// generate 2d vector of size nr x nc
// and only 10% percent of time will entries of this 2d vector
// be none zero
vector<vector<double>> Sparse2DMatrixGenerator(const int& nc, const int& nr) {
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());
    vector<vector<double>> mat;

    for (int i = 0; i < nr; ++i) {
        vector<double> row;
        for (int j = 0; j < nc; ++j) {
            double val = 0.0;
            if (rand() % 10 == 0) {
                val = (double)(rand() % 1000) / 100;
            }
            row.push_back(val);
        }
        mat.push_back(row);
    }
    assert(mat.size() == nr and mat[0].size() == nc);

    return mat;
}

int main() {
    int n_col = 10, n_row = 30;
    vector<vector<double>> mat = Sparse2DMatrixGenerator(n_col, n_row);
    auto sm = SparseMatrix{mat, 0};

    cout << sm << '\n';
    return 0;
}
