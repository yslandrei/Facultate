from functions import addTransaction, createTransaction, popTransactionsByDay, printAllTransactions, printTransaction
    

def testFunctions():
    List = []
    addTransaction(List, createTransaction(1, 100, "+"))
    addTransaction(List, createTransaction(2, 150, "+"))
    addTransaction(List, createTransaction(2, 300, "-"))
    addTransaction(List, createTransaction(3, 400, "-"))
    popTransactionsByDay(List, 2)
    printAllTransactions(List)