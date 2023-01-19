pronos = ['1', 'X', '2']

def backRec(i, n, arr):
    if consistent(arr[:i], n):
        if solution(arr):
            print(arr)
        return

    for prono in pronos:
        arr[i] = prono
        backRec(i + 1, n, arr) 
    
def consistent(arr, n):
    return len(arr) == n

def solution(arr):
    if arr[-1] == 'X':
        return False
    
    counter1 = 0
    for i in range(len(arr)):
        if arr[i] == '1':
            counter1 += 1
    if counter1 > 2:
        return False
    
    return True

n = int(input("Introduceti numarul de pronosticuri: "))
backRec(0, n, [0 for i in range(n)])
