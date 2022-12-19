def cmpKey(a, b):
    return a < b

def shakeSort(arr):
    sorted = False
    lft = 0
    rgt = len(arr) - 1
    while(sorted == False):
        sorted = True
        for i in range(lft, rgt):
            if cmpKey(arr[i + 1], arr[i]):
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                sorted = False

        if sorted == True:
            return
        sorted = True

        rgt = rgt - 1
        for i in range(rgt - 1, lft - 1, -1):
            if cmpKey(arr[i + 1], arr[i]):
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                sorted = False
        lft = lft + 1

arr = [-3, 4, 1, 10, 19, -2, 5, 14]
shakeSort(arr)
print(arr)