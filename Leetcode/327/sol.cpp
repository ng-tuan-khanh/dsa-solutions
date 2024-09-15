#include <string>
#include <vector>
#include <iostream>

using namespace std;

class STNode {
public:
    int numSums;
    vector<int>leftSums, rightSums;
    STNode(): numSums(0) {}
    STNode(int numSums, int val): numSums(numSums) {
        leftSums.push_back(val);
        rightSums.push_back(val);
    }

    STNode operator+(const STNode& rhs) {
        STNode tmp;

        int cnt = 0;
        for (int i = 0; i < rightSums.size(); ++i) {
            for (int j = 0; j < rhs.leftSums.size(); ++j) {
                int sum = rightSums[i] + rhs.leftSums[j];
                if ()
            }
        }

        return tmp;
    }
};

class ST {
private:
    int _n, _lower, _upper;
    vector<STNode>_tree;

public:
    ST(const vector<int>& nums, int lower, int upper) : _lower(lower), _upper(upper) {
        int n = nums.size(), i = 0;
        while (n != 0) {
            n >>= 1;
            ++i;
        }
        _n = 1 << i;
        _tree.resize(2 * _n, STNode());
        for (int i = 0; i < nums.size(); ++i) {
            update(i, nums[i]);
        }
    }

    // Single updates (bottom up)
    void update(int k, int val) {
        k += _n;

        if (_lower <= val && val <= _upper) {
            _tree[k] = STNode(1, val);
        }
        else {
            _tree[k] = STNode();
        }

        for (k /= 2; k >= 1; k /= 2) {
            _tree[k] = _tree[2 * k] + _tree[2 * k + 1];
        }
    }

    // Range queries (top down)
    STNode range(int l, int r, int k, int x, int y) {
        if (l > y || r < x) return STNode();
        if (x >= l && y <= r) return _tree[k];
        // The middle is always left-skewed, as _n is power of 2 -> length[x, m] == length[m + 1, y]
        int m = (x + y) / 2;
        return range(l, r, 2 * k, x, m) + range(l, r, 2 * k + 1, m + 1, y);
    }

    int solve(int l, int r) {
        return range(l, r, 1, 0, _n - 1).numSums;
    }
};