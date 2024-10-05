#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

#define ll long long 
#define INF LLONG_MAX 

using namespace std;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>>& adj, int s) {
    int n = adj.size() - 1;

    vector<ll>distance(n + 1, INF);
    distance[s] = 0;
    vector<bool>chosen(n + 1, false);
    // {weight, node}: use default operator < (deprecated in C++20)
    priority_queue<pair<ll, int>>q;
    q.push({0, s});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (!chosen[u]) {
            chosen[u] = true;
            for (auto p: adj[u]) {
                int v = p.first;
                ll w = p.second;
                distance[v] = min(distance[v], distance[u] + w);
                q.push({-distance[v], v});
            }
        }
    }

    return distance;
}

vector<ll>bellmanFord(const vector<vector<pair<int, ll>>>& adj, int s) {
    int n = adj.size() - 1;

    vector<ll>distance(n + 1, INF);
    distance[s] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (int u = 1; u <= n; ++u) {
            for (auto p: adj[u]) {
                int v = p.first;
                ll w = p.second;
                distance[v] = min(distance[v], distance[u] + w);
            }
        }
    }

    return distance;
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, ll>>>adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    vector<ll>distance = bellmanFord(adj, 1);
    for (int i = 1; i < distance.size(); ++i) {
        cout << distance[i] << '\n';
    }

    return 0;
}