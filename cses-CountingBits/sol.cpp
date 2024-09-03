#include <iostream>
#include <string>

using namespace std;

string bin(int n) {
    string res;
    for (int i = 31; i >= 0; --i) {
        if (n & (1 << i)) res += '1';
        else res += '0';
    }
    return res;
}

// 101 -> 3 + 2 + 2

int main() {
    unsigned long long n, res = 0;
    n = 10;
    for (int i = 0; n >= (1 << i); ++i) {
        unsigned long long parts, r = 0;
        // ith bit = 1
        // 1011 -> 10x1 -> 101 -> +1
        if (n & (1 << i)) {
            r = (n & ~(-1 << i));
            parts = ((n >> 1) & (-1 << i) | r) + 1;
        }
        // ith bit = 0
        // 11000101 -> 110x0101 -> 1100000 -> 1011111 -> +1
        else {
            parts = ((n >> 1) & (-1 << i)) - 1 + 1;
        }
        cout << parts << ' ' << bin(r) << '\n';
        res += parts;
    }
    cout << res;

    return 0;
}