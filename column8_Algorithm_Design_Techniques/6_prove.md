Prove that any correct algorithm for computing maximum subvectors must inspect all k inputs. (Algorithms for some problems may correctly ignore some inputs; consider Saxe’s algorithmin Solution 2.2 and Boyer and Moore’s substring searching algorithm.)

---

Let's assume, our algorithm produced the result `res` without examining at least 1 certain element `n1 ... nk-1`.

Since we've never seen this number `n1` before, it can't be included in `res` (its value is independent from res).
However, since there's no upper bound for how large an element in the vector can be, we can always assume `n1` equals `res+1` for any res, and thus `n1 > res`. Now, a subvector made of a single element `n1` becomes the maximum subvector. Therefore, the result obtained by our algorithm was incorrect.

Thus if an algorithm correctly solves this problem,
it can ignore at most 0 elements in the vector. (in other words, have to examine every element)
