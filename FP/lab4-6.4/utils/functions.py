import copy
from domain.undo import createUndoStackElement, stackTop, appendUndoStack, updateUndoStack


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

def getTransaction(List, i):
    return List[i]

def getTransactionDay(List, i):
    return List[i]["day"]

def getTransactionSum(List, i):
    return List[i]["sum"]

def getTransactionType(List, i):
    return List[i]["type"]

def setTransactionDay(List, i, newDay):
    List[i]["day"] = newDay

def setTransactionSum(List, i, newSum):
    List[i]["sum"] = newSum

def setTransactionType(List, i, newType):
    List[i]["type"] = newType

def popTransaction(List, i):
    del List[i]

def printTransaction(transaction):
    """
    Printeaza o tranzactie
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    """
    day = transaction["day"]
    sum = transaction["sum"]
    type = "Depunere" if transaction["type"] == "+" else "Scoatere"
    print(f"Ziua: {day} | Suma: {sum} | Tip: {type}")

def printAllTransactions(List):
    """
    Printeaza toate tranzactile
    """
    for i in range(len(List)):
        printTransaction(getTransaction(List, i))

def appendTransaction(List, transaction, undoStack):
    """
    Adaugă tranzacție (se dă ziua, suma, tipul)
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    """
    List.append(transaction)
    updateUndoStack(undoStack)
    appendUndoStack(undoStack, createUndoStackElement(transaction, "+", stackTop(List)))
    
def modifyTransaction(List, transaction, newSum, undoStack):
    """
    Actualizare tranzacție (se dă ziua, suma, tipul)
    transaction(dictionary) = tranzactia dorita cu zi, suma si tip 
    newSum(int) = noua suma cu care va fi actualizata cea veche
    """
    updateUndoStack(undoStack)
    for i in range(len(List)):
        if getTransaction(List, i) == transaction:
            transaction = copy.deepcopy(getTransaction(List, i))
            appendUndoStack(undoStack, createUndoStackElement(transaction, "r", i))
            setTransactionSum(List, i, newSum)
    
def popTransactionsByDay(List, day, undoStack):
    """
    Șterge toate tranzacțiile de la ziua specificată
    day(int) = ziua in care vor fi sterse tranzactiile
    """
    offset = 0
    updateUndoStack(undoStack)
    for i in range(len(List)):
        if getTransactionDay(List, i - offset) == day:
            appendUndoStack(undoStack, createUndoStackElement(getTransaction(List, i - offset), "-", i - offset))
            popTransaction(List, i - offset)
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
        if getTransactionDay(List, i - offset) >= st and getTransactionDay(List, i - offset) <= dr:
            appendUndoStack(undoStack, createUndoStackElement(getTransaction(List, i - offset), "-", i - offset))
            popTransaction(List, i - offset)
            offset += 1

def popTransactionsByType(List, type, undoStack):
    """
    Șterge toate tranzacțiile de un anumit tip
    type(string) = tipul de tranzactii care vor fi sterse
    """
    offset = 0
    undoStack.append(list())
    for i in range(len(List)):
        if getTransactionType(List, i - offset) == type:
            appendUndoStack(undoStack, createUndoStackElement(getTransaction(List, i - offset), "-", i - offset))
            popTransaction(List, i - offset)
            offset += 1

def printTransactionsHigherThanSum(List, sum):
    """
    Tipărește tranzacțiile cu sume mai mari decât o sumă dată
    sum(int) = suma care este cautata
    """
    for i in range(len(List)):
        if getTransactionSum(List, i) > sum:
            printTransaction(getTransaction(List, i))

def printTransactionsHigherThanSumAndLowerThanDay(List, day, sum):
    """
    Tipărește toate tranzacțiile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)
    day(int) = ziua cautata
    sum(int) = suma cautata
    """
    for i in range(len(List)):
        if getTransactionSum(List, i) > sum and getTransactionDay(List, i) < day:
            printTransaction(getTransaction(List, i))

def printTransactionsByType(List, type):
    """
    Tipărește tranzacțiile de un anumit tip
    type(string) = tipul cautat
    """
    for i in range(len(List)):
        if getTransactionType(List, i) == type:
            printTransaction(getTransaction(List, i))

def sumOfTransactionsByType(List, type):
    """
    Suma totală a tranzacțiilor de un anumit tip
    type(string) = tipul cautat
    """
    s = 0
    for i in range(len(List)):
        if getTransactionType(List, i) == type:
            s += getTransactionSum(List, i)
    print(s)

def balanceOfAccountUntilDay(List, day):
    """
    Soldul contului la o dată specificată
    day(int) = ziua cautata
    """
    s = 0
    for i in range(len(List)):
        if getTransactionDay(List, i) <= day:
            if getTransactionType(List, i) == "+":
                s += int(getTransactionSum(List, i))
            else:
                s -= int(getTransactionSum((List, i))) 
    print(s)

def printSortedListOfATypeBySum(List, type):
    """
    Tipărește toate tranzacțiile de un anumit tip ordonat după sumă
    type(string) = tipul cautat
    """
    sortedList = []
    for i in range(len(List)):
        if getTransactionType(List, i) == type:
            sortedList.append(getTransaction(List, i))
    sortedList = sorted(sortedList, key = lambda x: x["sum"], reverse = True)
    printAllTransactions(sortedList)
"""
def popTransactionsByType(List, type): (se repeta cerinta)
    
    Elimină toate tranzacțiile de un anumit tip
    type(string) = tipul cautat

    offset = 0
    for i in range(len(List)):
        if getTransactionType(List, i - offset) == type:
            popTransaction(List, i - offset)
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
        if getTransactionType(List, i - offset) == type and getTransactionSum(List, i - offset) < sum:
            appendUndoStack(undoStack, createUndoStackElement(getTransaction(List, i - offset), "-", i - offset))
            popTransaction(List, i - offset)
            offset += 1

