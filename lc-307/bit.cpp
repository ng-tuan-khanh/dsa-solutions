class NumArray {
private:
    vector<int>_tree;

    int _sum(int k) {
        int sum = 0;
        while (k >= 1) {
            sum += _tree[k];
            int p = k & -k;
            k -= p;
        }
        return sum;
    }
public:
    // Preprocessing
    NumArray(vector<int>& nums) {
        _tree.resize(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); ++i) {
            update(i, nums[i]);
        }
    }
    
    // Single updates
    void update(int k, int val) {
        int diff = val - sumRange(k, k);
        ++k;
        while (k < _tree.size()) {
            _tree[k] += diff;
            int p = k & -k;
            k += p;
        }
    }
    
    // Range queries
    int sumRange(int left, int right) {
        ++left;
        ++right;
        return _sum(right) - _sum(left - 1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */