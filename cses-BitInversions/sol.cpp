#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class STNode {
public:
    int len = 0;
    int longest = 0;
    int left = -1, leftLongest = 0;
    int right = -1, rightLongest = 0;

    STNode() = default;

    STNode(int _len, int _longest, int _left, int _leftLongest, int _right, int _rightLongest) {
        len = _len;
        longest = _longest;
        left = _left;
        leftLongest = _leftLongest;
        right = _right;
        rightLongest = _rightLongest;
    }

    STNode operator+(const STNode& rhs) {
        if (this->longest == 0) {
            return rhs;
        }
        if (rhs.longest == 0) {
            return *this;
        }

        STNode res;

        res.len = this->len + rhs.len;
        res.left = this->left;
        res.right = rhs.right;

        if (this->leftLongest == this->len && this->left == rhs.left) {
            res.leftLongest = this->len + rhs.leftLongest;
        }
        else {
            res.leftLongest = this->leftLongest;
        }
        if (rhs.rightLongest == rhs.len && rhs.right == this->right) {
            res.rightLongest = rhs.len + this->rightLongest;
        }
        else {
            res.rightLongest = rhs.rightLongest;
        }

        int midLongest = (this->right == rhs.left) ? this->rightLongest + rhs.leftLongest : 0;
        res.longest = max(this->longest, rhs.longest);
        res.longest = max(res.longest, midLongest);

        return res;
    } 
};

class ST {
public:
    vector<STNode>tree;
    ST(const string& s) {
        int n = s.size();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    };

    void build(const string &s, int k, int l, int r) {
        if (l == r) {
            int b = (s[l] == '1') ? 1 : 0;
            tree[k] = STNode(1, 1, b, 1, b, 1);
            return;
        }

        int m = (l + r) / 2;
        build(s, k * 2, l, m);
        build(s, k * 2 + 1, m + 1, r);
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
    }

    void update(int k, int l, int r, int i, int b) {
        if (i < l || r < i) return;
        if (l == r) {
            tree[k] = STNode(1, 1, b, 1, b, 1);
            return;
        }
        
        int m = (l + r) / 2;
        update(k * 2, l, m, i, b);
        update(k * 2 + 1, m + 1, r, i, b);
        tree[k] = tree[k * 2] + tree[k * 2 + 1];
    }

    STNode range(int k, int l, int r, int u, int v) {
        if (u > r || v < l) return STNode();
        if (u <= l && r <= v) return tree[k];

        int m = (l + r) / 2;
        return range(k * 2, l, m, u, v) + range(k * 2 + 1, m + 1, r, u, v);
    }
};


int main() {
    // ifstream fin("inp.txt");
    // ofstream fout("oup.txt");
    string s;
    int m, n;
    cin >> s >> m;
    n = s.size();

    ST st(s);
    vector<int>res;
    for (int i = 0; i < m; ++i) {
        int u, b;
        cin >> u;
        s[u - 1] = (s[u - 1] == '1') ? '0' : '1';
        b = (s[u - 1] == '1') ? 1 : 0;
        st.update(1, 0, n - 1, u - 1, b);
        res.push_back(st.range(1, 0, n - 1, 0, n - 1).longest);
    }
    // fin.close();
    for (auto r: res) {
        cout << r << ' ';
    }
    // fout.close();
    return 0;
}