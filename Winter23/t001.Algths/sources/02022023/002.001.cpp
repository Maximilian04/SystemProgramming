/*
Дан массив содержащий уникальные значения из диапазона [0..n], однако одно число отсутствует. Найти его.
Пример: [1, 5, 4, 2, 0]
Вывод: 3
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int size = 0, in = 0;
    cin >> size;

    int ans = 0;
    for (int i = 0; i < size; ++i) {
        cin >> in;
        ans ^= i;
        ans ^= in;
    }
    ans ^= size;

    cout << ans << endl;

    return 0;
}
