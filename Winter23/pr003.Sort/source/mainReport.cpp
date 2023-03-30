#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <Windows.h>

#define SPLINE_PTSNUM (100)

using namespace std;

class SuffInfo {
public:
    SuffInfo() {}
    SuffInfo(string lineStyle): lineStyle(lineStyle), maxSizeI(0) {}

    void addStat(long long size, long long time) {
        stats.emplace_back(size, time);

        if (size > stats[maxSizeI].second) maxSizeI = stats.size() - 1;
    }

    static bool compare(const SuffInfo& a, const SuffInfo& b) {
        return greater<long long>()(a.stats[a.maxSizeI].second, b.stats[b.maxSizeI].second);
    }

    void printSizes(ofstream& out) {
        for (auto stat : stats)
            out << ", " << stat.first;
    }

    void printTimes(ofstream& out) {
        for (auto stat : stats)
            out << ", " << stat.second;
    }

    long long getMaxSize() {
        return stats[maxSizeI].first;
    }

    string getLineStyle() {
        return lineStyle;
    }
private:
    string lineStyle;
    vector<pair<long long, long long>> stats;
    size_t maxSizeI;
};

#define SUFFS(name, lineStyle, ...) \
    {name, SuffInfo(lineStyle)},

map<string, SuffInfo> suffsList({
#include "suffs"
    });

#undef SUFFS

int main() {
    ofstream python("report.py", ios::trunc);
    // ofstream python = cout;
    ofstream report("../../README.md", ios::trunc);
    ifstream fileStat("stat.txt");

    while (true) {
        string trash, suff;
        long long size = 0, time = 0;

        fileStat >> trash;
        if (trash.empty()) break;
        fileStat >> trash >> suff >> trash >> size >> trash >> time >> trash;

        if (!suffsList.count(suff)) {
            cout << "ERROR: unrecognized suff '" << suff << "'" << endl;
            return 1;
        }

        suffsList[suff].addStat(size, time);
    }

    vector<pair<string, SuffInfo>> stats(suffsList.begin(), suffsList.end());
    sort(stats.begin(), stats.end(), [](const pair<string, SuffInfo>& a, const pair<string, SuffInfo>& b) -> bool {
        return SuffInfo::compare(a.second, b.second);
    });

    python <<
        "import numpy as np\n"
        "import matplotlib.pyplot as plt\n"
        "from scipy import interpolate\n"
        "\n"
        "plt.figure()\n"
        "\n";

    for (pair<string, SuffInfo> stat : stats) {
        // "xPts = np.array([0.0, 5.0, 0.1])\n"

        python << "xPts = np.array([0";
        stat.second.printSizes(python);
        python << "])\n";

        python << "yPts = np.array([0";
        stat.second.printTimes(python);
        python << "])\n";

        double maxSize = (double)stat.second.getMaxSize();
        // "t2 = np.arange(0.0, 5.0, 0.02)\n"
        python << "xSpl = np.arange(0.0, " << maxSize << ", " << maxSize / SPLINE_PTSNUM << ")\n";

        // "tck = interpolate.splrep(t1, f(t1))\n"
        python << "tck = interpolate.splrep(xPts, yPts)\n";
        // "plt.plot(t1, f(t1), 'bo', t2, interpolate.splev(t2, tck), 'k')\n"
        python << "plt.plot(xPts, yPts, " << stat.second.getLineStyle() << ", xSpl, interpolate.splev(xSpl, tck), 'k')\n";
        python << "\n";
    }
    // "plt.legend(['kukaruke'])\n"
    python << "\n";
    python << "plt.legend([";
    for (pair<string, SuffInfo> stat : stats) {
        python << "'" << stat.first << "', '', ";
    }
    python << "])\n";
    python << "\n";

    // python << "plt.show()\n";
    python << "plt.savefig('../../reportGraph.png')\n";

    /*python <<
        "import numpy as np\n"
        "import matplotlib.pyplot as plt\n"
        "from scipy import interpolate\n"
        "\n"
        "def f(t):\n"
        "   return np.exp(-t) * np.cos(2*np.pi*t)\n"
        "\n"
        "t1 = np.arange(0.0, 5.0, 0.1)\n"
        "t2 = np.arange(0.0, 5.0, 0.02)\n"
        "\n"
        "tck = interpolate.splrep(t1, f(t1))\n"
        "\n"
        "plt.figure()\n"
        "plt.plot(t1, f(t1), 'bo', t2, interpolate.splev(t2, tck), 'k')\n"
        "plt.legend(['kukaruke'])\n"
        "plt.show()\n";*/

    report << "# Практическая работа 3.\n";
    report << "![plot](./reportGraph.png)\n";


    python.close();
    report.close();
    fileStat.close();
    system("python report.py");

    cout << "Program finished 0" << endl;
}
