import math
from undo import undo, undoList
from functions import appendList, filterByModule, filterByPrimalityOfRealPart, insertList, isPrime, popList, popListElements, prodOfModules, replaceList, sumOfModules


def testFunctions():
    """
    Testeaza toate functiile definite in afara de cele de afisare
    """
    testList = []
    undoStack = []
    appendList(testList, 5, -3, undoStack)
    assert testList[0].a == 5 and testList[0].b == -3
    insertList(testList, 1, 2, 0, undoStack)
    assert testList[0].a == 1 and testList[0].b == 2
    appendList(testList, 1, 3, undoStack)
    popList(testList, 1, undoStack)
    assert testList[1].a == 1 and testList[1].b == 3
    appendList(testList, -1, -2, undoStack)
    appendList(testList, 2, 2, undoStack)
    appendList(testList, 3, -2, undoStack)
    popListElements(testList, 1, 3, undoStack)
    assert testList[1].a == 3 and testList[1].b == -2
    appendList(testList, 3, -2, undoStack)
    replaceList(testList, 3, -2, -3, 2, undoStack)
    assert testList[1].a == -3 and testList[1].b == 2
    assert sumOfModules(testList, 0, 2).a == -5 and sumOfModules(testList, 0, 2).b == 6
    assert prodOfModules(testList, 0, 2).a == 29 and prodOfModules(testList, 0, 2).b == -2
    assert isPrime(7) == True
    assert isPrime(18) == False
    appendList(testList, 2, 5, undoStack)
    appendList(testList, 4, 3, undoStack)
    filterByPrimalityOfRealPart(testList, undoStack)
    assert testList[3].a == 4 and testList[3].b == 3
    filterByModule(testList, "=", math.sqrt(5), undoStack)
    assert testList[0].a == -3 and testList[0].b == 2

def testUndo():
    """
    Testeaza Stiva de Undo
    """
    testList = []
    undoStack = []
    appendList(testList, 1, 1, undoStack)
    appendList(testList, 3, 3, undoStack)
    insertList(testList, 2, 2, 1, undoStack)
    appendList(testList, 4, 4, undoStack)
    popListElements(testList, 2, 3, undoStack)
    undoList(testList, undoStack)
    assert testList[2].a == 3 and testList[2].b == 3
    appendList(testList, 2, 2, undoStack)
    replaceList(testList, 2, 2, 6, 6, undoStack)
    undoList(testList, undoStack)
    assert testList[1].a == 2 and testList[1].b == 2
    undoList(testList, undoStack)
    undoList(testList, undoStack)
    assert len(testList) == 3
    filterByPrimalityOfRealPart(testList, undoStack)
    undoList(testList, undoStack)
    assert testList[2].a == 3 and testList[2].b == 3
    filterByModule(testList, "<", 3, undoStack)
    undoList(testList, undoStack)
    assert testList[0].a == 1 and testList[0].b == 1