#include <iostream>
#include <fstream>
#include <cstdlib>

#include "time.h"
#include "Tree.h"

using namespace std;

// rand: [0 .. ~32000]
// #define RAND rand() + (rand() << 15)
#define RAND rand()

int main() {
    Tree tree;

    TIMEPOINT(tpAdd5Begin);

    for (int i = 0; i < 1e5; ++i) {
        tree.add(RAND);
    }

    TIMEPOINT(tpAdd5End);

    TIMEPOINT(tpRem5Begin);

    int counter = 0;
    for (int i = 0; i < 5e4; ++i) {
        counter += tree.remove(RAND);
    }
    cout << counter << " совпадений" << endl;

    TIMEPOINT(tpRem5End);

    
    TIMEPOINT(tpAddSort5Begin);

    for (int i = 0; i < 7e4; ++i) {
        tree.add(i);
    }

    TIMEPOINT(tpAddSort5End);

    TIMEPOINT(tpRemSort5Begin);

    counter = 0;
    for (int i = 0; i < 3e4; ++i) {
        counter += tree.remove(i);
    }
    cout << counter << " совпадений" << endl;

    TIMEPOINT(tpRemSort5End);


    ofstream file("output.txt", ios::app);
    file << "Add 10^5      rands  : " << GETDURATION(tpAdd5Begin, tpAdd5End) << " ms" << endl;
    file << "Remove 5*10^4 rands  : " << GETDURATION(tpRem5Begin, tpRem5End) << " ms" << endl;
    file << "Add 7*10^4    sorted : " << GETDURATION(tpAddSort5Begin, tpAddSort5End) << " ms" << endl;
    file << "Remove 3*10^4 sorted : " << GETDURATION(tpRemSort5Begin, tpRemSort5End) << " ms" << endl;
    file << "_____________________" << endl;
    file.close();

    return 0;
}