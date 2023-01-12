pronos = ['1', 'X', '2']

def main():
    n = int(input("Introduceti numarul de pronosticuri: "))
    recursive(0, n, [0 for i in range(n)])

def recursive(i, n, arr):
    if i == n:
        if valid(arr):
            print(arr)
        return

    for prono in pronos:
        arr[i] = prono
        recursive(i + 1, n, arr) 
    
def valid(arr):
    if arr[-1] == 'X':
        return False
    
    counter1 = 0
    for i in range(len(arr)):
        if arr[i] == '1':
            counter1 += 1
    if counter1 > 2:
        return False
    
    return True

if __name__ == '__main__':
    main()