def cmpKey(a, b):
    return a < b

def getMinIndexFromArray(arr, lft, rgt):
    minIndex = lft
    for i in range(lft, rgt):
        if cmpKey(arr[i], arr[minIndex]):
            minIndex = i
    return minIndex

def selectionSortRec(arr, lft, rgt):
    if lft == rgt:
        return
    minIndex = getMinIndexFromArray(arr, lft, rgt)
    (arr[lft], arr[minIndex]) = (arr[minIndex], arr[lft])
    selectionSortRec(arr, lft + 1, rgt)

arr = [-3, 4, 1, 10, 19, -2, 5, 14]
selectionSortRec(arr, 0, len(arr))
print(arr)
    