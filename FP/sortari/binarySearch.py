def binarySearch(arr, nr):
    lft = 0
    rgt = len(arr) - 1
    while(lft <= rgt):
        mid = (lft + rgt) // 2
        if nr > arr[mid]:
            lft = mid + 1
        elif nr < arr[mid]:
            rgt = mid - 1
        else:
            return mid
    return -1

l = [1,6,8,10,12,17,28]
nr = 13
print(binarySearch(l, nr))