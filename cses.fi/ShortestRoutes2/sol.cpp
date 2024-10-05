#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

#define ll long long 
#define INF LLONG_MAX 

using namespace std;

int main() {
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>>adj(n + 1, vector<ll>(n + 1, INF));
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }
    for (int u = 1; u <= n; ++u) {
        adj[u][u] = 0;
    }

    vector<pair<int, int>>queries;
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        queries.push_back({u, v});
    }

    // Floyd-Warshall
    vector<vector<ll>>dist = adj;    
    for (int k = 1; k <= n; ++k) {
        for (int u = 1; u <= n; ++u) {
            for (int v = 1; v <= n; ++v) {
                ll distAtRoundK = (dist[u][k] != INF && dist[k][v] != INF) ? (dist[u][k] + dist[k][v]) : INF;
                dist[u][v] = min(dist[u][v], distAtRoundK);  
            }
        }
    }

    vector<ll>res;
    for (auto q: queries) {
        res.push_back((dist[q.first][q.second] == INF) ? -1 : dist[q.first][q.second]);
    }
    for (auto r: res) {
        cout << r << '\n';
    }

    return 0;
}