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
