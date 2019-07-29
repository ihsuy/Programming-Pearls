def BinarySearch(arr, val):
    assert isSortedAscending(
        arr), "fatal: perform binary search on an unsorted array"

    low = 0
    high = len(arr) - 1

    while low <= high:
        prev_size = high - low + 1

        mid = (low + high) // 2

        if arr[mid] < val:
            low = mid + 1
        elif arr[mid] == val:
            return mid
        else:
            high = mid - 1

        new_size = high - low + 1
        assert new_size < prev_size, """fatal: new size has to be smaller than old size, 
                                        otherwise it can result in infinite loop"""

    return -1


def isSortedAscending(arr):
    for i in range(len(arr) - 1):
        if arr[i] > arr[i + 1]:
            return False
    return True


# scaffolding

# create array of numbers
# 0, step_size*1, step_size*2, ..., step_size*(arr_size-1)
arr_size = 10000
step_size = 10

arr = [num * step_size for num in range(arr_size)]

# search numbers in the array
test_num = 3000
test_step = 8
for i in range(test_num):
    i = 5 * i
    res = BinarySearch(arr, i)

    test1_fail = (i % step_size == 0 and res != (i / step_size - 1))
    test2_fail = (i % step_size != 0 and res == -1)
    test3_fail = (i > arr[-1] and res != -1)

    assert test1_fail or test2_fail or test3_fail, "something is wrong"

print("All good")