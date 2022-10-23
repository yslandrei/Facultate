import math
import copy
from complexNumb import complexNumb
from undo import undo


def appendList(List, a, b, undoStack):
    """
    Adaugă un număr complex la sfârșitul listei
    a, b - partea reala/imaginara a numarului
    """
    undoStack[len(undoStack) - 1].append(undo(a, b, "+", len(List)))
    undoStack.append(list())
    List.append(complexNumb(a, b))

def insertList(List, a, b, i, undoStack):
    """
    Inserează un număr complex pe o poziție dată
    a, b - partea reala/imaginara a numarului
    i - pozitia la care numarul este inserat
    """
    undoStack[len(undoStack) - 1].append(undo(a, b, "+", i))
    undoStack.append(list())
    List.insert(i, complexNumb(a, b))

def popList(List, i, undoStack):
    """
    Șterge un element de pe o poziție dată
    i - pozitia numarului care este sters
    """
    undoStack[len(undoStack) - 1].append(undo(List[i].a, List[i].b, "-", i))
    undoStack.append(list())
    List.pop(i)

def popListElements(List, st, dr, undoStack):
    """
    Șterge elementele de pe un interval de poziții
    st, dr - indicii intervalului care este sters
    """
    for i in range(dr - st + 1):
        undoStack[len(undoStack) - 1].append(undo(List[st].a, List[st].b, "-", st))
        List.pop(st)
    undoStack.append(list())

def replaceList(List, a, b, x, y, undoStack):
    """
    Înlocuiește toate aparițiile unui număr complex cu un alt număr complex
    a, b - partea reala/imaginara a numarului cautat
    x, y - partea reala/imaginara a numarului inlocuit
    """
    for i in range(len(List)):
        if List[i].a == a and List[i].b == b:
            undoStack[len(undoStack) - 1].append(undo(a, b, "-", i))
            undoStack[len(undoStack) - 1].append(undo(x, y, "+", i))
            List[i].a, List[i].b = x, y
    undoStack.append(list())

def printImaginaryElements(List, st, dr):
    """
    Tipărește partea imaginara pentru o subsecventa de numerele din listă
    st, dr - indicii intervalului al carui parte imaginara este tiparita
    """
    for i in range(st, dr + 1):
        print(List[i].b, end = '  ')
    print("\n")

def printModulesLessThan10(List):
    """
    Tipărește toate numerele complexe care au modulul mai mic decât 10
    """
    for i in range(len(List)):
        if List[i].getModule() < 10:
            print(List[i], end = '   ')
    print("\n")

def printModulesEqualTo10(List):
    """
    Tipărește toate numerele complexe care au modulul egal cu 10
    """
    for i in range(len(List)):
        if List[i].getModule() == 10:
            print(List[i], end = '   ')
    print("\n")

def sumOfModules(List, st, dr):
    """
    Returnează suma numerelor dintr-o subsecventă dată
    st, dr - indicii intervalului al carei suma este calculata
    """
    sum = complexNumb(0, 0)
    for i in range(st, dr + 1):
        sum.a += List[i].a
        sum.b += List[i].b
    return sum

def prodOfModules(List, st, dr):
    """
    Returnează produsul numerelor dintr-o subsecventă dată
    st, dr - indicii intervalului al carei suma este calculata
    """
    prod = complexNumb(1, 0)
    for i in range(st, dr + 1):
        aux = copy.deepcopy(prod)
        prod.a = aux.a * List[i].a - aux.b * List[i].b
        prod.b = aux.b * List[i].a + aux.a * List[i].b
    return prod

def printSortedListDescendingByImaginaryPart(List):
    """
    Tipărește lista sortată descrescător după partea imaginara
    """
    sortedList = copy.deepcopy(List)
    sortedList.sort()
    for i in range(len(sortedList)):
        print(sortedList[i], end = '   ')
    print("\n")

def isPrime(x):
    """
    Returneaza daca un numar este prim sau nu
    """
    if x <= 1:
        return False
    elif x == 2:
        return True
    elif x % 2 == 0:
        return False
    rad = int(math.ceil(math.sqrt(x)))
    for i in range(3, rad + 1):
        if x % i == 0:
            return False
    return True

def filterByPrimalityOfRealPart(List, undoStack):
    """
    Elimină din listă numerele complexe a căror parte reală este primă
    """
    offset = 0
    for i in range(len(List)):
        if isPrime(List[i - offset].a):
            undoStack[len(undoStack) - 1].append(undo(List[i - offset].a, List[i - offset].b, "-", i - offset))
            List.pop(i - offset)
            offset += 1
    undoStack.append(list())

def filterByModule(List, semn, nr, undoStack):
    """
    Elimină din listă numerele complexe la care modulul este <, = sau > decât un număr dat
    semn - <, = sau >
    nr - numarul dat
    """
    offset = 0
    for i in range(len(List)):
        if semn == ">" and List[i - offset].getModule() > nr:
            undoStack[len(undoStack) - 1].append(undo(List[i - offset].a, List[i - offset].b, "-", i - offset))
            List.pop(i - offset)
            offset += 1
        elif semn == "=" and List[i - offset].getModule() == nr:    
            undoStack[len(undoStack) - 1].append(undo(List[i - offset].a, List[i - offset].b, "-", i - offset))
            List.pop(i - offset)
            offset += 1
        elif semn == "<" and List[i - offset].getModule() < nr:
            undoStack[len(undoStack) - 1].append(undo(List[i - offset].a, List[i - offset].b, "-", i - offset))
            List.pop(i - offset)
            offset += 1
    undoStack.append(list())
