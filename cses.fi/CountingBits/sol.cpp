#include <iostream>
#include <string>

using namespace std;

#define ll long long 

int main() {
    ll n, res = 0;
    cin >> n;
    for (int i = 0; n >> i; ++i) {
        ll setBits, r = 0;
        // ith bit = 1
        // e.g., 1011 -> 10x1 -> 101 -> +1 because 000 is still valid
        if (n & (1LL << i)) {
            r = (n & ~(-1LL << i));
            setBits = ((n >> 1) & (-1LL << i) | r) + 1;
        }
        // ith bit = 0
        // e.g., 11000101 -> 110x0101 -> 1100000 -> 1011111 -> +1 because 0000000 is still valid
        else {
            setBits = (((n >> 1) & (-1LL << i)) - 1) + 1;
        }
        res += setBits;
    }
    cout << res;

    return 0;
}