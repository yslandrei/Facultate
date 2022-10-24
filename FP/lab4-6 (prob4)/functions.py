
def createTransaction(day, sum, type):
    return {
        "day": day,
        "sum": sum,
        "type": type
    }

def printTransaction(transaction):
    day = transaction["day"]
    sum = transaction["sum"]
    if transaction["type"] == "+":
        type = "Depunere"
    elif transaction["type"] == "-":
        type = "Scoatere"
    print(f"Ziua: {day} | Suma: {sum} | Tip: {type}")

def printAllTransactions(List):
    for i in range(len(List)):
        printTransaction(List[i])

def addTransaction(List, transaction):
    """
    Adaugă tranzacție (se dă ziua, suma, tipul)
    """
    List.append(transaction)

def modifyTransaction(List, transaction, newSum):
    """
    Actualizare tranzacție (se dă ziua, suma, tipul)
    """
    for i in range(len(List)):
        if List[i] == transaction:
            List[i]["sum"] = newSum

def popTransactionsByDay(List, day):
    """
    Șterge toate tranzacțiile de la ziua specificată
    """
    offset = 0
    for i in range(len(List)):
        if List[i - offset]["day"] == day:
            del List[i - offset]
            offset += 1

def popTransactionsByDate(List, st, dr):
    """
    Șterge tranzacțiile dintr-o perioadă dată (se dă ziua de început și sfârșit)
    """
    offset = 0
    for i in range(len(List)):
        if List[i - offset]["day"] >= st and List[i - offset]["day"] <= dr:
            del List[i - offset]
            offset += 1

def popTransactionsByDay(List, type):
    """
    Șterge toate tranzacțiile de un anumit tip
    """
    offset = 0
    for i in range(len(List)):
        if List[i - offset]["type"] == type:
            del List[i - offset]
            offset += 1

def printTransactionsHigherThanSum(List, sum):
    """
    Tipărește tranzacțiile cu sume mai mari decât o sumă dată
    """
    for i in range(len(List)):
        if List[i]["sum"] > sum:
            printTransaction(List[i])
            print()

def printTransactionsHigherThanSumAndLowerThanDay(List, sum, day):
    """
    Tipărește toate tranzacțiile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)
    """
    for i in range(len(List)):
        if List[i]["sum"] > sum and List[i]["day"] < day:
            printTransaction(List[i])
            print()

def printTransactionsByType(List, type):
    """
    Tipărește tranzacțiile de un anumit tip
    """
    for i in range(len(List)):
        if List[i]["type"] == type:
            printTransaction(List[i])
            print() 



