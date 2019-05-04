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
A common implementation of sequential files on disk has each block point to its
successor, which may be any block on the disk. This method requires a constant
amount of time to write a block (as the file is originally written), to read the
first block in the file, and to read the ith block, once you have read the i – 1st
block. Reading the ith block from scratch therefore requires time proportional to
i. When Ed McCreight was designing a disk controller at Xerox Palo Alto Research
Center, he observed that by adding just one additional pointer per node, you can
keep all the other properties, but allow the ith block to be read in time
proportional to log i. How would you implement that insight?
*/

struct SeqFile
{
    static int unique_id;
    int id;
    int content;
    SeqFile *f1, *f2;
    SeqFile(): id(unique_id++), content(rand()), f1(nullptr), f2(nullptr) {}
};
int SeqFile::unique_id = 0;

// build a sequential file system that contains "size" number of files
vector<SeqFile> BuildFileSystem(const int& size)
{
    vector<SeqFile> files(size);
    // connect files
    for (int i = 0; i < size - 1; ++i)
    {
        files[i].f1 = &files[i + 1];
    }
    for (int i = 0; i < size / 2; ++i)
    {
        files[i].f2 = &files[2 * i];
    }

    return files;
}

SeqFile* SearchFile(const int& id, SeqFile* file_system,
                    const bool& verbose = false)
{
    if (id == 0)
    {
        if (verbose) cout << "Begin\n";
        return &file_system[0];
    }
    if (id % 2 == 0)
    {
        auto probe = SearchFile(id / 2, file_system, verbose);

        if (verbose) cout << "Big jump to " << id << '\n';
        return probe->f2;
    }
    else
    {
        auto probe = SearchFile(id - 1, file_system, verbose);

        if (verbose) cout << "Small jump to " << id << '\n';
        return probe->f1;
    }
}

int main()
{
    srand(chrono::high_resolution_clock::now().time_since_epoch().count());

    const int sys_size = 1000000;
    const int nTest = 2;
    const int verbose = true;

    auto file_system = BuildFileSystem(sys_size);

    for (int i = 0; i < nTest; ++i)
    {
        const int search_id = rand() % sys_size;
        cout << "Searching for id: " << search_id << endl;
        auto res = SearchFile(search_id, &file_system[0], verbose);
        assert(res->id == search_id);
    }
    cout << "all good\n";
    return 0;
}
