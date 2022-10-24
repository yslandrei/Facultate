from functions import addTransaction, createTransaction, popTransactionsByDay, printAllTransactions, printSortedListOfATypeBySum, printTransaction
    


def testFunctions():
    List = []
    addTransaction(List, createTransaction(1, 100, "+"))
    addTransaction(List, createTransaction(2, 150, "+"))
    addTransaction(List, createTransaction(2, 50, "+"))
    addTransaction(List, createTransaction(3, 400, "+"))