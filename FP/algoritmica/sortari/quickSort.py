def partition(arr, lft, rgt):
    pivot = arr[lft]
    i = lft
    j = rgt
    while(i < j):
        while arr[j] >= pivot and i < j:
            j -= 1
        arr[i] = arr[j]
        while arr[i] <= pivot and i < j:
            i += 1
        arr[j] = arr[i]   
    l[i] = pivot
    return i

def quickSort(arr, lft, rgt):
    if lft < rgt:
        pivotIndex = partition(arr, lft, rgt)
        quickSort(arr, lft, pivotIndex - 1)
        quickSort(arr, pivotIndex + 1, rgt)

l = [1,7,2,4,6,6,98,1,5]
quickSort(l, 0, len(l) - 1)
print(l)



