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

    vector<bool> arr(size + 1, true);
    for (int i = 0; i < size; ++i) {
        cin >> in;
        arr[in] = false;
    }

    for (int i = 0; i <= size; ++i) {
        if (arr[i])
            cout << i << " ";
    }
    cout << endl;

    return 0;
}
