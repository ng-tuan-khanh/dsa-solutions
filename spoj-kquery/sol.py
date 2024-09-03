import sys
sys.stdin = open('spoj-kquery/inp.txt', 'r')

class ST:
    def __init__(self, nums):
        # Find the least power of 2
        # greater than n
        i = 0
        self.n = len(nums)
        while (self.n > 0):
            self.n >>= 1
            i += 1
        self.n = 1 << i
        self.tree = []
        for i in range(2 * self.n):
            self.tree.append(STNode([]))

        for i in range(len(nums)):
            self.tree[i + self.n].arr = [nums[i]]

        self.populate(1)

    # Populate tree
    def populate(self, k):
        if (k * 2 >= len(self.tree)):
            return self.tree[k]
        self.tree[k] = self.populate(2 * k) + self.populate(2 * k + 1)
        return self.tree[k]

    # Range query
    def range(self, pivot, q_l, q_r, k, r_l, r_r):
        if (q_l > r_r or q_r < r_l): 
            return 0
        if (r_l >= q_l and r_r <= q_r):
            return bs(self.tree[k].arr, pivot)
        m = (r_l + r_r) // 2
        return self.range(pivot, q_l, q_r, k * 2, r_l, m) + self.range(pivot, q_l, q_r, k * 2 + 1, m + 1, r_r)

    def solve(self, i, j, pivot):
        return self.range(pivot, i - 1, j - 1, 1, 0, self.n - 1)

def bs(arr, pivot):
    if (len(arr) == 0): return 0
    i = 0
    j = len(arr) // 2
    while (j >= 1):
        while (i + j < len(arr) and arr[i + j] <= pivot):
            i += j
        j //= 2
    if (arr[i] > pivot): return len(arr)
    return len(arr) - 1 - i

class STNode:
    def __init__(self, arr):
        self.arr = arr

    def __add__(self, r_node):
        l, r = 0, 0
        res = []
        while (l < len(self.arr) and r < len(r_node.arr)):
            if (self.arr[l] < r_node.arr[r]):
                res.append(self.arr[l])
                l += 1
            else:
                res.append(r_node.arr[r])
                r += 1
        while (l < len(self.arr)):
            res.append(self.arr[l])
            l += 1

        while (r < len(r_node.arr)):
            res.append(r_node.arr[r])
            r += 1
        return STNode(res)    

def main():
    n = int(input())
    nums = list(map(lambda x: int(x), input().split()))
    # Build the segment tree
    st = ST(nums)

    q = int(input())
    res = []
    for i in range(q):
        query = list(map(lambda x: int(x), input().split()))
        res.append(st.solve(query[0], query[1], query[2]))
    for i in range(len(res)):
        print(res[i])

if __name__ == '__main__':
    main()