#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    for (int k = 1; k <= n - 1; ++k) {
        int cnt = 0;
        for (int i = 0; i + k < n; ++i) {
            if (s[i] == '1' && s[i + k] == '1') {
                cnt += 1;
            }
        }
        cout << cnt << ' ';
    }

    return 0;
}