/*
Дано n, нужно вывести корень из n округленый вниз. Пример: 65 -> 8
Пример: 63 -> 7
sqrt(), pow() использовать нельзя
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n = 0;
    cin >> n;

    int l = 1;
    int m = 0, mm = 0;
    int r = n;

    while (true) {
        m = (l + r) / 2;
        mm = m * m;

        if (mm == n) {
            l = r = m;
            break;
        }

        if (mm < n) {
            l = m;
        } else {
            r = m;
        }

        if (r - l <= 1) {
            break;
        }
        // cout << r << " " << l << endl;
    }

    cout << l << endl;

    return 0;
}
