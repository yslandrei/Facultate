from functions import createTransaction, popTransactionsByDay, appendTransaction, modifyTransaction, popTransactionsByDate, popTransactionsByType, popTransactionsByTypeAndBelowSum


def testCT():
    transaction = createTransaction(1, 100, "+")
    assert transaction["day"] == 1 and transaction["sum"] == 100 and transaction["type"] == "+"

def testAT():
    TList = []
    undoStack = []
    transaction = createTransaction(1, 100, "+")
    appendTransaction(TList, transaction, undoStack)
    assert TList[0] == transaction

def testMT():
    TList = []
    undoStack = []
    transaction1 = createTransaction(1, 100, "+")
    transaction2 = createTransaction(1, 200, "+")
    appendTransaction(TList, transaction1, undoStack)
    modifyTransaction(TList, transaction1, 200, undoStack)
    assert TList[0] == transaction2

def testPTD():
    TList = []
    undoStack = []
    transaction1 = createTransaction(1, 100, "+")
    transaction2 = createTransaction(2, 200, "+")
    appendTransaction(TList, transaction1, undoStack)
    appendTransaction(TList, transaction2, undoStack)
    popTransactionsByDay(TList, 1, undoStack)
    assert TList[0] == transaction2

def testPTDA():
    TList = []
    undoStack = []
    transaction1 = createTransaction(1, 100, "+")
    transaction2 = createTransaction(2, 200, "+")
    transaction3 = createTransaction(3, 300, "+")
    appendTransaction(TList, transaction1, undoStack)
    appendTransaction(TList, transaction2, undoStack)
    appendTransaction(TList, transaction3, undoStack)
    popTransactionsByDate(TList, 1, 2, undoStack)
    assert TList[0] == transaction3

def testPTT():
    TList = []
    undoStack = []
    transaction1 = createTransaction(1, 100, "-")
    transaction2 = createTransaction(2, 200, "+")
    appendTransaction(TList, transaction1, undoStack)
    appendTransaction(TList, transaction2, undoStack)
    popTransactionsByType(TList, "-", undoStack)
    assert TList[0] == transaction2

def testPTTS():
    TList = []
    undoStack = []
    transaction1 = createTransaction(1, 100, "-")
    transaction2 = createTransaction(2, 200, "+")
    transaction3 = createTransaction(3, 300, "+")
    transaction4 = createTransaction(4, 400, "+")
    appendTransaction(TList, transaction1, undoStack)
    appendTransaction(TList, transaction2, undoStack)
    appendTransaction(TList, transaction3, undoStack)
    appendTransaction(TList, transaction4, undoStack)
    popTransactionsByTypeAndBelowSum(TList, 350, "+", undoStack)
    assert TList[0] == transaction1
    assert TList[1] == transaction4

def testFunctions():
    testCT()
    testAT()
    testMT()
    testPTD()
    testPTDA()
    testPTT()
    testPTTS()