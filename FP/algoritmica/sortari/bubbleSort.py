def bubbleSort(arr):
    sorted = False
    while(sorted == False):
        sorted = True
        for i in range(1, len(arr)):
            if arr[i - 1] > arr[i]:
                arr[i - 1], arr[i] = arr[i], arr[i - 1]
                sorted = False
    return arr

l = [1,7,2,6,98,1,5]
print(bubbleSort(l))