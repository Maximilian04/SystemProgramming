/*
Дан массив из 0 и 1, дано k. Нужно найти размер максимального подмассива который содержит не более k нулей.
Пример: [1, 0, 0, 0, 1, 1, 0, 1] , k = 2. Ответ: 5
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    int size = 0;
    cin >> size;

    vector<int> arr(size, 0);
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }

    int k = 0;
    cin >> k;

    int maxLenght = 0; // length = r - l
    int l = 0;
    int r = 0;
    // track : [l,r)

    int counter = 0;

    while (r < size) {
        ++r;
        if (arr[r - 1] == 0)
            ++counter;

        while (counter > k) {
            if (arr[l++] == 0)
                --counter;
        }

        if (r - l > maxLenght)
            maxLenght = r - l;
    }

    cout << maxLenght << endl;

    return 0;
}
