from undo import createUndoStackElement, stackTop


def createTransaction(day, sum, type):
    """
    Creeaza o noua tranzactie cu:
    day(int) = ziua
    sum(int) = suma
    type(string) = tipul ("+" / "-")
    """
    return {
        "day": day,
        "sum": sum,
        "type": type
    }

def printTransaction(transaction):
    """
    Printeaza o tranzactie
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    """
    day = transaction["day"]
    sum = transaction["sum"]
    if transaction["type"] == "+":
        type = "Depunere"
    elif transaction["type"] == "-":
        type = "Scoatere"
    print(f"Ziua: {day} | Suma: {sum} | Tip: {type}")

def printAllTransactions(List):
    """
    Printeaza toate tranzactile
    """
    for i in range(len(List)):
        printTransaction(List[i])

def appendTransaction(List, transaction, undoStack):
    """
    Adaugă tranzacție (se dă ziua, suma, tipul)
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    """
    List.append(transaction)
    undoStack.append(list())
    undoStack[stackTop(undoStack)].append(createUndoStackElement(transaction, "+", stackTop(List)))
    
def modifyTransaction(List, transaction, newSum, undoStack):
    """
    Actualizare tranzacție (se dă ziua, suma, tipul)
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    newSum(int) = noua suma cu care va fi actualizata cea veche
    """
    undoStack.append(list())
    for i in range(len(List)):
        if List[i] == transaction:
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i], "-", i))
            List[i]["sum"] = newSum
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i], "+", i))
    
def popTransactionsByDay(List, day, undoStack):
    """
    Șterge toate tranzacțiile de la ziua specificată
    day(int) = ziua in care vor fi sterse tranzactiile
    """
    offset = 0
    undoStack.append(list())
    for i in range(len(List)):
        if List[i - offset]["day"] == day:
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i - offset], "-", i - offset))
            del List[i - offset]
            offset += 1

def popTransactionsByDate(List, st, dr, undoStack):
    """
    Șterge tranzacțiile dintr-o perioadă dată (se dă ziua de început și sfârșit)
    st(int) = intervalul din stanga a perioadei data
    dr(int) = intervalul din dreapta a perioadei data
    """
    offset = 0
    undoStack.append(list())
    for i in range(len(List)):
        if List[i - offset]["day"] >= st and List[i - offset]["day"] <= dr:
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i - offset], "-", i - offset))
            del List[i - offset]
            offset += 1

def popTransactionsByType(List, type, undoStack):
    """
    Șterge toate tranzacțiile de un anumit tip
    type(string) = tipul de tranzactii care vor fi sterse
    """
    offset = 0
    undoStack.append(list())
    for i in range(len(List)):
        if List[i - offset]["type"] == type:
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i - offset], "-", i - offset))
            del List[i - offset]
            offset += 1

def printTransactionsHigherThanSum(List, sum):
    """
    Tipărește tranzacțiile cu sume mai mari decât o sumă dată
    sum(int) = suma care este cautata
    """
    for i in range(len(List)):
        if List[i]["sum"] > sum:
            printTransaction(List[i])

def printTransactionsHigherThanSumAndLowerThanDay(List, day, sum):
    """
    Tipărește toate tranzacțiile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)
    day(int) = ziua cautata
    sum(int) = suma cautata
    """
    for i in range(len(List)):
        if List[i]["sum"] > sum and List[i]["day"] < day:
            printTransaction(List[i])

def printTransactionsByType(List, type):
    """
    Tipărește tranzacțiile de un anumit tip
    type(string) = tipul cautat
    """
    for i in range(len(List)):
        if List[i]["type"] == type:
            printTransaction(List[i])

def sumOfTransactionsByType(List, type):
    """
    Suma totală a tranzacțiilor de un anumit tip
    type(string) = tipul cautat
    """
    s = 0
    for i in range(len(List)):
        if List[i]["type"] == type:
            s += List[i]["sum"]
    print(s)

def balanceOfAccountUntilDay(List, day):
    """
    Soldul contului la o dată specificată
    day(int) = ziua cautata
    """
    s = 0
    for i in range(len(List)):
        if List[i]["day"] <= day:
            if List[i]["type"] == "+":
                s += int(List[i]["sum"])
            else:
                s -= int(List[i]["sum"]) 
    print(s)

def printSortedListOfATypeBySum(List, type):
    """
    Tipărește toate tranzacțiile de un anumit tip ordonat după sumă
    type(string) = tipul cautat
    """
    sortedList = []
    for i in range(len(List)):
        if List[i]["type"] == type:
            sortedList.append(List[i])
    sortedList = sorted(sortedList, key = lambda x: x["sum"], reverse = True)
    printAllTransactions(sortedList)
"""
def popTransactionsByType(List, type): (se repeta cerinta)
    
    Elimină toate tranzacțiile de un anumit tip
    type(string) = tipul cautat

    offset = 0
    for i in range(len(List)):
        if List[i - offset]["type"] == type:
            del List[i - offset]
            offset += 1
"""
def popTransactionsByTypeAndBelowSum(List, sum, type, undoStack):
    """
    Elimină toate tranzacțiile mai mici decât o sumă dată care au tipul
    specificat
    sum(int) = suma cautata
    type(string) = tipul cautat
    """
    offset = 0
    undoStack.append(list())
    for i in range(len(List)):
        if List[i - offset]["type"] == type and List[i - offset]["sum"] < sum:
            undoStack[stackTop(undoStack)].append(createUndoStackElement(List[i - offset], "-", i - offset))
            del List[i - offset]
            offset += 1

