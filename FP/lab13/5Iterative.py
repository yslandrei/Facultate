def backtIter(n):
    pronos = ["1", "X", "2"]
    tickets = []
    for i in range(n):
        if i == 0:
            for prono in pronos:
                tickets.append([prono])
        else:
            new_tickets = []
            for ticket in tickets:
                for prono in pronos:
                    new_tickets.append(ticket + [prono])
                    if consistent(new_tickets[-1], n):
                        if not solution(new_tickets[-1]):
                            new_tickets.pop(-1)
            tickets = new_tickets
    return tickets

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
tickets = backtIter(n)

for ticket in tickets:
    print(ticket)
