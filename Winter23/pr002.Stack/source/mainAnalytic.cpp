#include <string>
#include <vector>
#include <Windows.h>
#include "include.h"

vector<string> suff1l({
    "1",
    "2",
    "3",
    });
vector<string> suff2l({
    "Arr",
    "List",
    });

#define REPEAT_NUM (5)

int main() {
    {
        ofstream file("log.txt", ios::trunc);
        file.close();
    }

    for (const string& suff1 : suff1l)
        for (const string& suff2 : suff2l)
            for (int i = 0; i < REPEAT_NUM; ++i)
                system(("PracTest" + suff1 + suff2 + ".exe").c_str());

    ifstream file("log.txt");
    file >> noskipws;
    ofstream fileStat("stat.txt");
    for (const string& suff1 : suff1l) {
        for (const string& suff2 : suff2l) {
            int sum = 0;
            for (int i = 0; i < REPEAT_NUM; ++i) {
                char trash;
                int time;
                for (int i = 0; i < 19; ++i)
                    file >> trash;

                file >> time;
                sum += time;

                for (int i = 0; i < 4; ++i)
                    file >> trash;
            }
            sum /= REPEAT_NUM;

            fileStat << "Statistic : " << suff1 << suff2 << " : " << sum << "ms" << endl;
        }
    }
    file.close();
    fileStat.close();

    cout << "Program finished 0" << endl;
}
