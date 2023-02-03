/*
Решение судоку. На затраты по времени и памяти все равно.
*/

#include <iostream>
#include <vector>

using namespace std;

class Table {
public:

    bool isCorrect() const;

    friend istream& operator>>(istream& in, Table& table);
    friend ostream& operator<<(ostream& out, Table& table);
private:
    int data[81];

    static int getIndex(int i, int j);
};



int main() {
    Table pattern;
    cin >> pattern;

    cout << pattern.isCorrect() << endl;

    // cout << pattern;
}

#define CHECK_NUM(i, j)                 \
    int num = data[getIndex(i, j)];      \
    if (num < 0 || num > 9) return false; \
    if (nums[num]) return false;           \
    nums[num] = true;

#define FOR(lit, lim) \
    for (int lit = 0; lit < lim; ++lit)

bool Table::isCorrect() const {
    FOR(i, 9) {
        vector<bool> nums(9, false);

        FOR(j, 9) {
            CHECK_NUM(i, j);
        }
    }

    FOR(i, 9) {
        vector<bool> nums(9, false);

        FOR(j, 9) {
            CHECK_NUM(j, i);
        }
    }

    FOR(si, 3) {
        FOR(sj, 3) {
            vector<bool> nums(9, false);

            FOR(i, 3) {
                FOR(j, 3) {
                    CHECK_NUM(3 * si + i, 3 * sj + j);
                }
            }
        }
    }

    return true;
}

#undef CHECK_NUM
#undef FOR

istream& operator>>(istream& in, Table& table) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            in >> table.data[table.getIndex(i, j)];
        }
    }

    return in;
}

ostream& operator<<(ostream& out, Table& table) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            out << table.data[table.getIndex(i, j)] << " ";
        }
        out << endl;
    }

    return out;
}


int Table::getIndex(int i, int j) {
    return i * 9 + j;
}
