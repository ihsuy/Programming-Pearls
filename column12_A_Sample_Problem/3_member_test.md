Show that when `m < n/2`, the expected number of member tests made by the set-based algorithm before finding a number not in the set is less than 2.

---

Since we try to prove that in average we need less than 2 member tests to find a element that's not in the set, we consider the "worst senario".  
In a realistic setting, the probablity for having to do at least 1 extra member test is `k/n` where k is number of elements already in the set. when `k` is small, the probablity that we don't need to do extra member test at all is very high and this probablity decreases as we successfully insert more elements into the set.  
So what's the worst senario?  
The worst situation happens when we alreayd have `m-1` elements in the set, and we need to find that 1 element left in the `n-m+1` elements that we are left with. The possibility for having to draw again becomes `(m-1)/n`.  
However, since we know that `m < n/2`, so our worst possibility will be 
`1/2 - 1/n` which is less than `1/2`, i.e. in the worst senario, we need strictly less than 2 member test to find a valid number.  
Therefore we can conclude that, in average, throughout of the whole process of generation, number of member tests made before finding a number not in the set is less than 2.  