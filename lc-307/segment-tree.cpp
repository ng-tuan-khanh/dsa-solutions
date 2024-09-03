#include <vector>

using namespace std;

class NumArray {
private:
    vector<int>_tree;
    int _n;

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
    int sumRange(int left, int right) {
        left += _n;
        right += _n;
        int sum = 0;
        while (left <= right) {
            if (left % 2 == 1) {
                sum += _tree[left++];
            }
            if (right % 2 == 0) {
                sum += _tree[right--];
            }
            left /= 2;
            right /= 2;
        }
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */