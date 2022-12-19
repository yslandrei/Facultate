def cmpKey(a, b):
    return a < b

def selectionSort(arr):
    for i in range(len(arr)):
        minIndex = i
        for j in range(i + 1, len(arr)):
            if cmpKey(arr[j], arr[minIndex]):
                minIndex = j
        (arr[i], arr[minIndex]) = (arr[minIndex], arr[i])

arr = [-3, 4, 1, 10, 19, -2, 5, 14]
selectionSort(arr)
print(arr)