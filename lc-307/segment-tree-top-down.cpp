#include <vector>

using namespace std;

class NumArray {
private:
    vector<int>_tree;
    int _n;

    int _sumRange(int l, int r, int k, int x, int y) {
        if (l > y || r < x) return 0;
        if (x >= l && y <= r) return _tree[k];
        // The middle is always left-skewed, as _n is power of 2 -> length[x, m] == length[m + 1, y]
        int m = (x + y) / 2;
        return _sumRange(l, r, 2 * k, x, m) + _sumRange(l, r, 2 * k + 1, m + 1, y);
    }

public:
    // Preprocessing
    NumArray(vector<int>& nums) {
        int n = nums.size(), i = 0;
        while (n != 0) {
            n >>= 1;
            ++i;
        }
        _n = 1 << i;
        _tree.resize(2 * _n, 0);
        for (int i = 0; i < nums.size(); ++i) {
            update(i, nums[i]);
        }
    }
    
    // Single updates
    void update(int k, int val) {
        int diff = val - sumRange(k, k);
        k += _n;
        _tree[k] += diff;
        for (k /= 2; k >= 1; k /= 2) {
            _tree[k] = _tree[2 * k] + _tree[2 * k + 1];
        }
    }
    
    // Range queries
    int sumRange(int l, int r) {
        return _sumRange(l, r, 1, 0, _n - 1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */