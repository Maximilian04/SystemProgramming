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

    int ptr1 = 0;
    int ptr2 = 0; // ptr2 >= ptr1
    while (ptr2 < size) {
        if (arr[ptr1] == 0) {
            while (arr[ptr2] == 0) {
                ++ptr2;
            }

            arr[ptr1] = arr[ptr2];
            arr[ptr2] = 0;
        }

        ++ptr1;
        ++ptr2;
    }

    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
