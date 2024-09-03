#include <iostream>
#include <fstream>
#include <algorithm>
#include <climits>

using namespace std;

#define P 16
#define D 30

int total[1 << P][D];
int price[P][D];

int main() {
    ifstream fin("inp.txt");
    int p, d;
    fin >> p >> d;
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < d; ++j) {
            fin >> price[i][j];
        }
    }
    fin.close();

    for (int i = 0; i < p; ++i) {
        total[1 << i][0] = price[i][0];
    }

    for (int i = 1; i < d; ++i) {
        for (int s = 0; s < (1 << p); ++s) {
            total[s][i] = total[s][i - 1];
            for (int j = 0; j < p; ++j) {
                if (s & (1 << j)) {
                    total[s][i] = min(total[s][i], total[s ^ (1 << j)][i - 1] + price[j][i]);
                }
            }
        }
    }

    ofstream fout("oup.txt");
    for (int s = 0; s < (1 << p); ++s) {
        fout << total[s][d - 1] << '\n';
    }
    fout.close();
    return 0;
}
