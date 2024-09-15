#include <iostream>

using namespace std;

int main() {
    unsigned n;
    cin >> n;
    unsigned res = 1;
    for (int i = 0; i < n; ++i) {
        res = res << 1;
        res = res % (1000000000 + 7);
    }
    cout << res;
    return 0;
}