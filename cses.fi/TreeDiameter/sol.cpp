#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int u, int p, const vector<vector<int>>& adj,vector<int>& toLeaf, vector<int>& diameter) {
    int maxToLeaf = -1, secondMaxToLeaf = -1;
    for (auto v : adj[u]) {
        if (v != p) {
            solve(v, u, adj, toLeaf, diameter);
            // The new value can be in one of 3 ranges
            if (maxToLeaf <= toLeaf[v]) {
                secondMaxToLeaf = maxToLeaf;
                maxToLeaf = toLeaf[v];
            }
            else if (secondMaxToLeaf <= toLeaf[v]) {
                secondMaxToLeaf = toLeaf[v];
            }
        }
    }
    toLeaf[u] = maxToLeaf + 1;
    diameter[u] = (secondMaxToLeaf != -1) ?
     maxToLeaf + secondMaxToLeaf + 2 :
     maxToLeaf + 1;
}

int main() {
    int n; cin >> n;
    vector<vector<int>>adj(n + 1, vector<int>());
    for (int i = 1; i <= n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int>toLeaf(n + 1, 0);
    vector<int>diameter(n + 1, 0);
    solve(1, 0, adj, toLeaf, diameter);
    cout << *max_element(diameter.begin(), diameter.end());

    return 0;
}