#include <iostream>
#include <vector>
#include <string>
#include <pair>

using namespace std;

void dfs(int i, int j, const vector<string>& map, vector<vector<bool>>& trace) {
    trace[i][j] = true;
    int n = map.size(), m = map[0].size();
    if (j - 1 >= 0 && map[i][j - 1] == '.' && !trace[i][j - 1]) {
        dfs(i, j - 1, map, trace);
    } 
    if (j + 1 < m && map[i][j + 1] == '.' && !trace[i][j + 1]) {
        dfs(i, j + 1, map, trace);
    } 
    if (i - 1 >= 0 && map[i - 1][j] == '.' && !trace[i - 1][j]) {
        dfs(i - 1, j, map, trace);
    } 
    if (i + 1 < n && map[i + 1][j] == '.' && !trace[i + 1][j]) {
        dfs(i + 1, j, map, trace);
    } 
}

int solve(const vector<string>& map) {
    int n = map.size(), m = map[0].size(), rA, cA, rB, cB;
    vector<vector<pair<int, int>>>trace(n, vector<pair<int, int>(m, {-1, -1}));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 'A') {
                rA = i;
                cA = j;
            }
            if (map[i][j] == 'B') {
                rB = i;
                cB = j;
            }
        }
    }
    
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string>map;
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        map.push_back(row);
    }
    cout << solve(map);

    return 0;
}