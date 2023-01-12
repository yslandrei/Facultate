def partition(arr, lft, rgt):
    pivot = arr[lft]
    i = lft - 1
    j = rgt + 1
    while(True):
        i += 1
        while arr[i] < pivot:
            i += 1
        j -= 1
        while arr[j] > pivot:
            j -= 1
        if(i >= j):
            return j
        arr[i], arr[j] = arr[j], arr[i]


def quickSort(arr, lft, rgt):
    if lft < rgt:
        pivotIndex = partition(arr, lft, rgt)
        quickSort(arr, lft, pivotIndex)
        quickSort(arr, pivotIndex + 1, rgt)

l = [1,7,2,6,98,1,5]
quickSort(l, 0, len(l) - 1)
print(l)

