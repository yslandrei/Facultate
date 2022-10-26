from undo import undoList
from functions import appendList, filterByModule, filterByPrimalityOfRealPart, insertList, popList, popListElements, printImaginaryElements, printModulesEqualTo10, printModulesLessThan10, printSortedListDescendingByImaginaryPart, prodOfModules, replaceList, sumOfModules


def afis(List):
    """
    Afiseaza lista curenta de numere complexe
    """
    for i in range(len(List)):
        print(List[i], end = '   ')
    print("\n")

def printMenu():
    print("\n")
    print("• Adaugă un număr complex la sfârșitul listei                             - add [a] [b]")
    print("• Inserează un număr complex pe o poziție dată                            - ins [a] [b] [pos]")
    print("• Șterge un element de pe o poziție dată                                  - pop [pos]")
    print("• Șterge elementele de pe un interval de poziții                          - popE [st] [dr]")
    print("• Înlocuiește toate aparițiile unui număr complex cu un alt număr complex - rpl [a] [b] [x] [y]")
    print("• Tipărește partea imaginara pentru o subsecventa  de numerele din listă  - pimg [st] [dr]") 
    print("• Tipărește toate numerele complexe care au modulul mai mic decât 10      - pml10")
    print("• Tipărește toate numerele complexe care au modulul egal cu 10            - pme10")
    print("• Tipărește lista sortată descrescător după partea imaginara              - psldi")
    print("• Returnează suma numerelor dintr-o subsecventă dată                      - sum [st] [dr]")
    print("• Returnează produsul numerelor dintr-o subsecventă dată                  - prod [st] [dr]")
    print("• Elimină din listă numerele complexe a căror parte reală este primă      - fpr")
    print("• Elimină din listă numerele complexe la care modulul este <, = sau >     - fm [semn] [nr]")
    print("  decât un număr dat")

def menu():
    CList = []
    undoStack = []
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
    while(1):   
        printMenu()
        com = input("Comanda (a = afis, u = undo, q = quit): ")
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
        if com == "q":
            break
        elif com[:4] == "add ":
            com = com[4:]
            a, b = com.split()
            try:
                appendList(CList, int(a), int(b), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:4] == "ins ":
            com = com[4:]
            a, b, pos = com.split()
            try:
                insertList(CList, int(a), int(b), int(pos), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:4] == "pop ":
            pos = com[4:]
            try:
                popList(CList, int(pos), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:5] == "popE ":
            com = com[5:]
            st, dr = com.split()
            try:
                popListElements(CList, int(st), int(dr), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:4] == "rpl ":
            com = com[4:]
            a, b, x, y = com.split()
            try:
                replaceList(CList, int(a), int(b), int(x), int(y), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:5] == "pimg ":
            com = com[5:]
            st, dr = com.split()
            try:
                printImaginaryElements(CList, int(st), int(dr))
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com == "pml10":
            printModulesLessThan10(CList)
        elif com == "pme10":
            printModulesEqualTo10(CList)
        elif com == "psldi":
            printSortedListDescendingByImaginaryPart(CList)
        elif com[:4] == "sum ":
            com = com[4:]
            st, dr = com.split()
            try:
                print(sumOfModules(CList, int(st), int(dr)))
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com[:5] == "prod ":
            com = com[5:]
            st, dr = com.split()
            try:
                print(prodOfModules(CList, int(st), int(dr)))
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com == "fpr":
            filterByPrimalityOfRealPart(CList, undoStack)
        elif com[:3] == "fm ":
            sign = com[3]
            nr = com[5:]
            try:
                filterByModule(CList, sign, int(nr), undoStack)
            except ValueError:
                print("Sintaxa Invalida! Introdu numere intregi")
        elif com == "u":
            try:
                undoList(CList, undoStack)
            except ValueError:
                print("Nicio operatie ramasa pentru undo")
        elif com == "a":
            afis(CList)
        else:
            print("Comanda Invalida!")