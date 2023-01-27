#cautare binara

def bSearch(arr, nr):
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
    return lft

l = [1,6,8,10,12,17,28]
nr = 13
print(bSearch(l, nr))

#selection sort

def sSort(l):
    for i in range(len(l)):
        min = l[i]
        minIndex = i
        for j in range(i, len(l)):
            if l[j] < min:
                min = l[j]
                minIndex = j
        l[i], l[minIndex] = l[minIndex], l[i]
    return l

#insertion sort

def iSort(l):
    for i in range(len(l)):
        j = i
        while j > 0 and l[j]<l[j-1]:
            l[j-1], l[j] = l[j],l[j-1]
            j-=1
    return l

#bubble sort

def bSort(l):
    sorted = False
    while(sorted == False):
        sorted = True
        for i in range(len(l) - 1):
            if l[i] > l[i + 1]:
                l[i],l[i+1] = l[i+1],l[i]
                sorted = False
    return l

#merge sort

def merge(a, b):
    c = []
    i = 0
    j = 0
    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            c.append(a[i])
            i += 1
        else:
            c.append(b[j])
            j += 1
    while i < len(a):
        c.append(a[i])
        i += 1
    while j < len(b):
        c.append(b[j])
        j += 1
    return c

def mSort(l):
    if len(l) == 1:
        return l
    mid = len(l) // 2
    return merge(mSort(l[:mid]), mSort(l[mid:]))

#quick sort

def partition(l, lft, rgt):
    pivot = l[lft]
    i = lft
    j = rgt
    while i < j:
        while pivot <= l[j] and i < j:
            j -= 1
        l[i] = l[j]
        while pivot >= l[i] and i < j:
            i += 1
        l[j] = l[i]
    l[i] = pivot
    return i
        

def qSort(l, lft, rgt):
    if lft < rgt:
        pivotIndex = partition(l, lft, rgt)
        qSort(l, lft, pivotIndex - 1)
        qSort(l, pivotIndex + 1, rgt)

    
#sublista crescatoare

def dinamica(l):
    dp = [1 for _ in range(len(l))]
    next = [-1 for _ in range(len(l))]

    max = 0
    maxIndex = 0

    for i in range(len(l) - 1, -1, -1):
        for j in range(i + 1, len(l)):
            if l[i] < l[j]:
                if dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    next[i] = j
                if dp[i] > max:
                    max = dp[i]
                    maxIndex = i

    ret = []
    while maxIndex != -1:
        ret.append(l[maxIndex])
        maxIndex = next[maxIndex]
    return max, ret

#l = [1,2,3,4,5,4,3,2,1,2,6,7]
#print(dinamica(l))

