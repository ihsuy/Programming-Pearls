What special properties of the “juggling” rotation algorithm allowed us to replace the % remainder operator with an if statement, and not a more costly while statement?  
Experiment to determine when it is worth replacing a % remainder operator with a while statement.

---

The special property of the _juggling rotation_ is that its step size will always be less than the arr's size which guarantees the code below will only run once:

```c++
if(n>arr.size())
{
	n-=arr.size();
}
```

i.e. its guaranteed that `n - arr.size() < arr.size()`

Base on the reasoning above, we don't need a while loop for this task.  
For More detailed timing and experiements about this problem,  
checkout [IntegerRemainder_speedTest](https://github.com/ihsuy/programming_pearls/blob/master/column9_Code_Tuning/IntegerRemainder_speedTest.cpp).

Note that for this special case (implement juggling rotation) while or if doesn't make much difference in runtime (refer to the file above for experiements and results).
