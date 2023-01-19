def longestIncreasingEvenSublist(arr):
    dp = [1 for _ in range(len(arr))] #lista care tine minte care e cea mai lunga subliste crescatoare care incepe cu un element
    #orice elemente reprezinta o sublista crescatoare para de lungime 1. Tehnic, doar elementele pare ar trb sa aiba 1
    #insa oricum verificam de fiecare data ca aceasta cond sa fie indeplinita, asa ca putem initializa toata lista cu 1
    next = [-1 for _ in range(len(arr))] #lista care tine minte elementul care urmeaza dupa elementul de pe poz i
    Max = 0
    maxIndex = 0

    for i in range(len(arr) - 1, -1, -1): #parcurgem lista de la stanga la dreapta deoarece stim sigur ca ultimul element
        for j in range(i + 1, len(arr)):  #va avea valorea 1
            if arr[i] < arr[j] and arr[i] % 2 == 0 and arr[j] % 2 == 0:
                    if dp[j] + 1 > dp[i]:
                        dp[i] = dp[j] + 1
                        next[i] = j
                    if dp[i] > Max:
                        Max = dp[i]
                        maxIndex = i
    n = max(dp)
    rez = []

    while maxIndex != -1:
        rez.append(arr[maxIndex])
        maxIndex = next[maxIndex]
    return n, rez

l = [1,2,3,4,5,5,5,4,4,2,6,7,8,9,10]
print(longestIncreasingEvenSublist(l))

