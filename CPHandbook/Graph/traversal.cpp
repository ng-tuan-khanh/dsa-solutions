#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    for (auto v: adj[u]) {
        if (!visited[v]) dfs(v, adj, visited);
    }
}

void bfs(int s, const vector<vector<int>>& adj) {
    vector<bool> visited;
    queue<int> q;
    visited.resize(adj.size());
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v: adj[u]) {
            if (!visited[v]) {
                q.push(v);
                visited[v] = true;
            }
        }
    }
}

int main() {
    vector<vector<int>> adj;
    vector<bool> visited;
    dfs(1, adj, visited);
    return 0;
}