def longestDecreasingUnevenSublist(arr):
    dp = [1 for _ in range(len(arr))]
    next = [-1 for _ in range(len(arr))]
    maxim = 0
    maxIndex = 0

    for i in range(len(arr) - 1, -1, -1):
        for j in range(i + 1, len(arr)):
            if arr[i] > arr[j] and arr[i] % 2 == 1 and arr[j] % 2 == 1:
                if dp[j] + 1 > dp[i]:
                    dp[i] = dp[j] + 1
                    next[i] = j
                if dp[i] > maxim:
                    maxim = dp[i]
                    maxIndex = i
    
    n = max(dp)
    rez = []

    while maxIndex != -1:
        rez.append(arr[maxIndex])
        maxIndex = next[maxIndex]

    return n, rez

l = [5, 4, 3, 2, 10, 9, 8, 1]
print(longestDecreasingUnevenSublist(l))

