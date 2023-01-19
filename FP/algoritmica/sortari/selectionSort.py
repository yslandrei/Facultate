def selectionSort(arr):
    for i in range(len(arr)):
        minNr = arr[i]
        minIndex = i
        for j in range(i + 1, len(arr)):
            if arr[j] < minNr:
                minNr = arr[j]
                minIndex = j
        
        arr[i], arr[minIndex] = arr[minIndex], arr[i]
    return arr

l = [1,7,2,6,98,1,5]
print(selectionSort(l))

