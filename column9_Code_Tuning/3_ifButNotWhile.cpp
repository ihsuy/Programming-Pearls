/*
What special properties of the “juggling” 
rotation algorithm allowed us to replace 
the % remainder operator with an if statement, 
and not a more costly while statement? 
Experiment to determine when it is worth 
replacing a % remainder operator with 
a while statement.

The special property of the "juggling" rotation is that
the step size will always be less than the arr's size
which guarantees that the code below only will only run once 
"if(n>arr.size()){n-=arr.size();}"
Because n - arr.size() will 100% yield a result thats less than arr.size()

Base on the reasoning above, we don't need a while loop for this task
for More detailed timing and experiements on this problem, 
checkout "IntegerRemainder_speedTest.cpp" in the same repository

Note that for this special case (implement juggling rotation)
while or if doesn't make much difference in runtime
*/
