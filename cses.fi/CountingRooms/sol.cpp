#include <iostream>
#include <vector>
#include <string>

using namespace std;

void dfs(int i, int j, const vector<string>& map, vector<vector<bool>>& visited) {
    visited[i][j] = true;
    int n = map.size(), m = map[0].size();
    if (j - 1 >= 0 && map[i][j - 1] == '.' && !visited[i][j - 1]) {
        dfs(i, j - 1, map, visited);
    } 
    if (j + 1 < m && map[i][j + 1] == '.' && !visited[i][j + 1]) {
        dfs(i, j + 1, map, visited);
    } 
    if (i - 1 >= 0 && map[i - 1][j] == '.' && !visited[i - 1][j]) {
        dfs(i - 1, j, map, visited);
    } 
    if (i + 1 < n && map[i + 1][j] == '.' && !visited[i + 1][j]) {
        dfs(i + 1, j, map, visited);
    } 
}

int solve(const vector<string>& map) {
    int n = map.size(), m = map[0].size();
    vector<vector<bool>>visited(n, vector<bool>(m, false));
    int res = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '.' && !visited[i][j]) {
                ++res;
                dfs(i, j, map, visited);
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