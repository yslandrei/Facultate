def merge(arr1, arr2):
    arrRet = []
    i = 0
    j = 0
    while(i < len(arr1) and j < len(arr2)):
        if arr1[i] < arr2[j]:
            arrRet.append(arr1[i])
            i += 1
        else:
            arrRet.append(arr2[j])
            j += 1
    
    while(i < len(arr1)):
        arrRet.append(arr1[i])
        i += 1
    
    while(j < len(arr2)):
        arrRet.append(arr2[j])
        j += 1

    return arrRet

def mergeSort(arr):
    if len(arr) == 1:
        return arr

    mid = len(arr) // 2

    return merge(mergeSort(arr[:mid]), mergeSort(arr[mid:]))

l = [1,7,2,4,6,6,98,1,5]
print(mergeSort(l))