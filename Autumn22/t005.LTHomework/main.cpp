#include <string>
#include <vector>
#include <iostream>

using namespace std;

int ansCounter = 0;

vector<bool> arr(36, false);
int pos = 4;

bool check() {
    bool good = true;
    for (int check = 4; check < pos; ++check) {
        bool con = true;
        for (int shift = -4; shift <= 0; ++shift) {
            if (arr[check + shift] != arr[pos + shift]) {
                con = false;
                break;
            }
        }

        if (con) {
            good = false;
            break;
        }
    }
    return good;
}

bool req() {
    ++pos;
    // cout << pos << endl;

    if (pos >= 36) {
        if (ansCounter >= 0)
            ++ansCounter;
        for (int i = 0; i < 36; ++i) {
            cout << arr[i] << ' ';
        }
        cout << endl;

        --pos;
        return true;
    }

    arr[pos] = 0;
    if (check()) {
        if (req()) {
            if (ansCounter < 0) {
                --pos;
                return true;
            }
        }
    }

    arr[pos] = 1;
    if (check()) {
        if (req()) {
            if (ansCounter < 0) {
                --pos;
                return true;
            }
        }
    }

    --pos;
    return false;
}

int main() {
    cout << req() << "-ghj" << endl;
    if (ansCounter >= 0)
        cout << "count : " << ansCounter << endl;

    /*for (int i = 0; i < 36; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;*/

    return 0;
}
