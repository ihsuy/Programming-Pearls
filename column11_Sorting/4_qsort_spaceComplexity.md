Although Quicksort uses only O(log n) stack space on the average, it can use linear space in the worst case. Explain why, then modify the program to use only logarithmic space in the worst case.

The extra space complexity is a product of recursive stack frame creation.
When recursion happenes, a stack frame is created that requires a contant amount of memory. Therefore it can be concluded that the amount of extra space that we
need is dominated by the depth of the recursion.

In an naive implementation of QuickSort which uses the leftmost entry as pivot, the input array is halved on each recursion calls. Since the recursion will hit the bottom back when the input size becomes 1, we need to recurse log(N) times to reach there, and that's why we need log(N) space in general.
However, the space complexity of this algorithm can get as bad as O(N) under the situation an sorted array is given. Since naive_quickSort always pick the leftmot entry, and it can be observed that the algorithm will be creating partitions of size (1, n-1), (1, n-2), (1, n-3), ... (1, 1) and result in recursion depth of n which needs O(n) extra space.

To tackle this issue, randomized quickSort (also refer to qsort4 in [sorting_algorithms.cpp](https://github.com/ihsuy/programming_pearls/blob/master/column11_Sorting/sorting_algorithms.cpp)) can be used. Instead of always selecting the leftmost entry as pivot, we randomly select 1 and proceed. It is proven to be effective to do such as it cancels the effective of any adversarial input by not selecting pivot under any fixed behaviour.
Another approach based on randomized quickSort is that "after partitioning, the partition with the fewest elements is (recursively)sorted first, requiring at most O(log n) space. Then the other partition is sorted using tail recursion oriteration, which doesn't add to the call stack"([cited from](http://en.wikipedia.org/wiki/Quicksort#Randomized_quicksort_expected_complexity)). This can be understood as: because the alrgorithm always partition the input into 2 parts on each recursion calls, there's always a longer half and a shorter half. If we always choose the shorter half to continue sorting, we will only need at most log(n) recursion depth in the worst case.

```c++
const int cut_off = 10;
void qsort4_helper(vector<int>& nums, int low, int high)
{
    int hl_diff = high - low;
    if (hl_diff <= cut_off)
    {
        return;
    }
    // random pivot
    swap(nums[low], nums[rand() % (hl_diff + 1) + low]);
    int pivot = nums[low];

    int l = low, h = high + 1;
    for (;;)
    {
        do
        {
            l++;
        }
        while (l <= high and nums[l] < pivot);

        do
        {
            h--;
        }
        while (nums[h] > pivot);

        if (l > h)
        {
            break;
        }
        // hand made swap
        auto tmp = nums[l];
        nums[l] = nums[h];
        nums[h] = tmp;
    }
    swap(nums[h], nums[low]);

    qsort4_helper(nums, low, h - 1);
    qsort4_helper(nums, h + 1, high);
}

void qsort4(vector<int>& nums)
{
    qsort4_helper(nums, 0, nums.size() - 1);
    InsertionSort3(nums);
}
```
