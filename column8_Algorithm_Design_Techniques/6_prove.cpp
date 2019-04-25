/*
Prove that any correct algorithm for computing 
maximum subvectors must inspect all k inputs. 
(Algorithms for some problems may correctly 
ignore some inputs; consider Saxe’s algorithm
in Solution 2.2 and Boyer and Moore’s 
substring searching algorithm.)

Let's assume, our algorithm produced the result "res"
without examining at least 1 certain element n1 ... nk-1.

Since, we've never seen that number before, 
it's not included in res (its value is independent from res).
However, since there's no upper bound for how large an element in the vector
can be, we can always assign n1 to be res+1 for any res, and thus n1 > res.
Now, a subvector made of element "n" alone becomes the maximum subvector.
Therefore, the result obtained by our algorithm was incorrect.

Thus if an algorithm correctly solves this problem, 
it at ignore at most 0 elements in the vector.
*/

