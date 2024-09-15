#include <iostream>

using namespace std;

#define ll long long

int leftmostSetBit(ll n) {
    int b = -1;
    while (n) {
        b += 1;
        n = n >> 1;
    }
    return b;
}

ll numSetBits(ll n) {
    if (n == 0) return 0;

    // n >= 2^b
    int b = leftmostSetBit(n);

    ll res = 0;
    // Set bits of [0, 2^b - 1] = b * 2^(b - 1)
    res += b * (1LL << (b - 1));

    // Set bits at index b of [2^b, n] = n - 2^b + 1
    res += n - (1LL << b) + 1;

    // The remaining set bits are equal to set bits of [0, n - 2^b]
    res += numSetBits(n - (1LL << b));

    return res; 
}

int main() {
    ll n;
    cin >> n;

    cout << numSetBits(n);

    return 0;
}