import sys
sys.stdin = open('spoj-kquery/inp.txt', 'r')

# Idea:
# - The goal is to either reduce the time complexity
# of either the single update (which is the chosen way in this solution)
# or the range query operation (my solution).
# - Offline processing is used to make use of the fact that
# if the query pivots are sorted, previous calculations can be used.

class ST:
    def __init__(self, n):
        self.n = n
        self.tree = [None] * 4 * n
        self.build(1, 0, n - 1)

    def build(self, k, l, r):
        if (l == r):
            self.tree[k] = 1
            return
        
        mid = (l + r) // 2
        self.build(k * 2, l, mid)
        self.build(k * 2 + 1, mid + 1, r)

        self.tree[k] = self.tree[k * 2] + self.tree[k * 2 + 1]

    # [l,r] corresponds to k, update tree[i] = val
    def update(self, k, l, r, i, val):
        if (i < l or r < i):
            return
        
        if (l == r):
            self.tree[k] = val
            return

        m = (l + r) // 2
        self.update(k * 2, l, m, i, val)
        self.update(k * 2 + 1, m + 1, r, i, val)

        self.tree[k] = self.tree[k * 2] + self.tree[k * 2 + 1]

    # [l, r] corresponds to k, [u, v] is the range query
    def range(self, k, l, r, u, v):
        if (u > r or v < l):
            return 0
        
        if (l >= u and r <= v):
            return self.tree[k]
        
        m = (l + r) // 2
        return self.range(k * 2, l, m, u, v) + self.range(k * 2 + 1, m + 1, r, u, v)
    
    def solve(self, u, v):
        return self.range(1, 0, self.n - 1, u - 1, v - 1)

class Query:
    def __init__(self, id, l, r, pivot):
        self.id = id
        self.l = l
        self.r = r
        self.pivot: int = pivot
        self.res: int

def main():
    n = int(input())
    nums = list(map(lambda x: int(x), input().split()))
    q = int(input())
    queries = []
    for i in range(q):
        inp = list(map(lambda x: int(x), input().split()))
        queries.append(Query(i, inp[0], inp[1], inp[2]))

    # Process queries/Offline processing
    # Build the segment tree
    st = ST(n)

    # Sort queries by pivot
    queries.sort(key = lambda query: query.pivot)

    # Compute the position of each num in the sorted nums
    j = 0
    mark = sorted([[i, nums[i]] for i in range(n)], key=lambda e: e[1])

    for i in range(q):
        # Update tree[k] = 0 if num[k] <= pivot
        while (j < n and mark[j][1] <= queries[i].pivot):
            st.update(1, 0, n - 1, mark[j][0], 0)
            j += 1
        queries[i].res = st.solve(queries[i].l, queries[i].r)

    queries.sort(key = lambda query: query.id)
    for i in range(q):
        print(queries[i].res)

main()
