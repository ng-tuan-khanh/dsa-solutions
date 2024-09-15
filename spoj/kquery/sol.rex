// Input the nums array //
pull nums.0
do i = 1 to nums.0
    pull nums.i
end
// Build the segment tree //
// Find the least power of 2 larger than nums.0
i = 0
_n = nums.0
do while _n > 0
    _n = _n % 2
    i = i + 1
end
_n = 2 ** i
// 1. TODO: Init
// Default value for the nodes
do i = 1 to _n
    st.i.val = 0
    st.i.arr.0 = 0
end

// 4. Single updates from nums
do i = 1 to nums.0
    update(st, _n, i, nums.i)
end

/* 7. Receive query and solve
pull q.0
do i = 1 to q.0
    pull i
    pull j
    pull k
    q.i = 
end
*/
exit
// 2. Single updates //
update: procedure
arg st, _n, k, val
    k = k + _n - 1
    st.k.val = val
    
    k = k % 2
    do while k >= 1
        l = 2 * k
        r = 2 * k + 1
        st.k = merge(st.l, st.r)
        k = k % 2
    end
return
// 3. Merge //
merge: procedure
arg l_node, r_node
    i = 1
    l = 1
    r = 1
    do while l <= l_node.arr.0 & r <= r_node.arr.0
        if l_node.arr.l < r_node.arr.r then do
            res.arr.i = l_node.arr.l
            l = l + 1
        else do
            res.arr.i = r_node.arr.r
            r = r + 1
        end
        i = i + 1
    end
return res
// 5. Range queries //
range: procedure
arg st, l, r, k, x, y
    if l > y | r < x return
    if x >= l & y <= r return
    m = (x + y) % 2
    return merge(range(l, r, 2 * k, x, m), range(l, r, 2 * k + 1, m + 1, y))
end    
// 6. Solve
solve: procedure
arg st, _n, l, r, pivot
    return range(l, r)
return

