#include "include.h"

#define SUFFS(name, ...) \
    name,

vector<string> suff1l({
#include "suffs"
    });

#undef SUFFS

const int REPEAT_NUM = 3;
const int STEP_NUM = 10;

SizeGen sizeGenerator;

void saveArr(int* arr, size_t size) {
    ofstream arrFile("arr.txt");

    arrFile << size << endl;

    for (size_t i = 0; i < size; ++i) {
        arrFile << arr[i] << endl;
    }

    arrFile.close();
}

void generateArr() {
    size_t size = sizeGenerator.getSize();
    int* arr = (int*)calloc(size, sizeof(int));
    if (!arr) {
        cout << "MEM ERR" << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = randGenerator() % 10;
    }

    saveArr(arr, size);
    free(arr);
}

int main() {
    {
        ofstream file("log.txt", ios::trunc);
        file.close();
        file.open("logNames.txt", ios::trunc);
        file.close();
    }

    for (int i = 0; i < STEP_NUM; ++i) {
        sizeGenerator.newSize();

        for (int j = 0; j < REPEAT_NUM; ++j) {
            generateArr();

            cout << "run " << sizeGenerator.getSize() << endl;
            for (const string& suff1 : suff1l) {
                system(("PracTest" + suff1 + ".exe").c_str());
                cout << "run " << "PracTest" + suff1 + ".exe" << endl;
            }

            cout << (i * REPEAT_NUM + j) << "/" << (STEP_NUM * REPEAT_NUM) << "done" << endl;
        }
    }

    ifstream file("log.txt");
    ifstream fileNames("logNames.txt");
    ofstream fileStat("stat.txt");
    // file >> noskipws;

    for (int i = 0; i < STEP_NUM; ++i) {
        sizeGenerator.nextStoredSize();

        map<string, long long> sums;
        for (int i = 0; i < REPEAT_NUM; ++i) {
            for (const string& suff1 : suff1l) {
                if (!i)
                    sums.insert({ suff1, 0ll });

                string trash; // "ms" string
                long long time;

                file >> time;
                sums[suff1] += time;

                file >> trash;
            }

        }
        for (const string& suff1 : suff1l) {
            sums[suff1] /= REPEAT_NUM;

            fileStat << "Statistic : " << suff1 << " : " << sizeGenerator.getStoredSize() << " : " << sums[suff1] << " ms" << endl;
        }
    }
    file.close();
    fileStat.close();

    cout << "Program finished 0" << endl;
}
