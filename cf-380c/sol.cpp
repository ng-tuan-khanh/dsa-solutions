#include <string>
#include <vector>
#include <iostream>

using namespace std;

class TreeNode {
public:
    int optimal = 0;
    int open = 0;
    int close = 0;
    TreeNode() = default;
    TreeNode(int _optimal, int _open, int _close)
        : optimal(_optimal), open(_open), close(_close) {}

    TreeNode operator+(TreeNode const& r) {
        TreeNode res;
        int numMatch = min(open, r.close);
        res.optimal = optimal + r.optimal + numMatch * 2;
        res.open = open + r.open - numMatch;
        res.close = close + r.close - numMatch;
        return res;
    }
};

class BracketSeq {
private:
    int _n = 0;
    vector<TreeNode>_tree;


public:
    BracketSeq(const string& s) {
        int n = s.size(), i = 0;
        while (n != 0) {
            n >>= 1;
            ++i;
        }
        _n = 1 << i;
        _tree.resize(2 * _n, TreeNode());
        for (int i = 0; i < s.size(); ++i) {
            update(i, s[i]);
        }
    }

    // Single updates (bottom up)
    void update(int k, char c) {
        k += _n;

        if (c == '(') _tree[k] = TreeNode(0, 1, 0);
        else _tree[k] = TreeNode(0, 0, 1);

        for (k /= 2; k >= 1; k /= 2) {
            _tree[k] = _tree[2 * k] + _tree[2 * k + 1];
        }
    }

    // Range queries (top down)
    TreeNode range(int l, int r, int k, int x, int y) {
        if (l > y || r < x) return TreeNode();
        if (x >= l && y <= r) return _tree[k];
        // The middle is always left-skewed, as _n is power of 2 -> length[x, m] == length[m + 1, y]
        int m = (x + y) / 2;
        return range(l, r, 2 * k, x, m) + range(l, r, 2 * k + 1, m + 1, y);
    }

    int solve(int l, int r) {
        return range(l, r, 1, 0, _n - 1).optimal;
    }
};

int main() {
    string s; cin >> s;
    int n; cin >> n;
    BracketSeq seq(s);

    vector<int>inp;
    for (int i = 0; i < n; ++i) {
        int l, r; cin >> l >> r;
        inp.push_back(l);
        inp.push_back(r);
    }
    for (int i = 0; i < n; ++i) {
        cout << seq.solve(inp[i * 2] - 1, inp[i * 2 + 1] - 1) << '\n';
    }
    return 0;
}