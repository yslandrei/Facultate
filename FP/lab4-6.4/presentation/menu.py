from business.functions import appendTransaction, balanceOfAccountUntilDay, modifyTransaction, popTransactionsByDate, popTransactionsByDay, popTransactionsByType, popTransactionsByTypeAndBelowSum, printAllTransactions, printSortedListOfATypeBySum, printTransactionsByType, printTransactionsHigherThanSum, printTransactionsHigherThanSumAndLowerThanDay, sumOfTransactionsByType
from domain.transaction import createTransaction
from business.undo import undoList


def printMenu():
    print("\n")
    print("• Adaugă tranzacție                                               - add [ziua] [suma] [tip]")
    print("• Actualizare tranzacție                                          - upt [ziua] [suma] [tip] [newSum]")
    print("• Șterge toate tranzacțiile de la ziua specificată                - deld [ziua]")
    print("• Șterge tranzacțiile dintr-o perioadă dată                       - delp [st] [dr]")
    print("• Șterge toate tranzacțiile de un anumit tip                      - delt [tip]")
    print("• Tipărește tranzacțiile cu sume mai mari decât o sumă dată       - pts [suma]") 
    print("• Tipărește toate tranzacțiile efectuate înainte de o zi          - ptd [ziua] [suma]")
    print("  și mai mari decât o sumă")
    print("• Tipărește tranzacțiile de un anumit tip                         - ptt [tip]")
    print("• Suma totală a tranzacțiilor de un anumit tip                    - stt [tip]")
    print("• Soldul contului la o dată specificată                           - bad [ziua]")
    print("• Tipărește toate tranzacțiile de un anumit tip ordonat după sumă - ptts [tip]")
    print("• Elimină toate tranzacțiile mai mici decât o sumă dată           - ptst [suma] [tip]")
    print("  care au tipul specificat")

def menu():
    TList = []
    undoStack = []
    print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
    while(1):
        printMenu()
        com = input("Comanda (a = afis, u = undo, q = quit): ")
        print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
        if com == "q":
            return
        elif com[:4] == "add ":
            com = com[4:]
            try:
                day, sum, type = com.split()
                appendTransaction(TList, createTransaction(int(day), int(sum), type), undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "upt ":
            com = com[4:]
            try:
                day, sum, type, newSum = com.split()
                modifyTransaction(TList, createTransaction(int(day), int(sum), type), int(newSum), undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:5] == "deld ":
            com = com[5:]
            try:
                day = int(com)
                popTransactionsByDay(TList, day, undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:5] == "delp ":
            com = com[5:]
            try:
                st, dr = com.split()
                popTransactionsByDate(TList, int(st), int(dr), undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:5] == "delt ":
            com = com[5:]
            try:
                type = com
                popTransactionsByType(TList, type, undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "pts ":
            com = com[4:]
            try:
                sum = com
                printTransactionsHigherThanSum(TList, int(sum), undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "ptd ":
            com = com[4:]
            try:
                day, sum = com.split()
                printTransactionsHigherThanSumAndLowerThanDay(TList, int(day), int(sum))
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "ptt ":
            com = com[4:]
            try:
                type = com
                printTransactionsByType(TList, type)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "stt ":
            com = com[4:]
            try:
                type = com
                sumOfTransactionsByType(TList, type)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:4] == "bad ":
            com = com[4:]
            try:
                day = com
                balanceOfAccountUntilDay(TList, int(day))
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:5] == "ptts ":
            com = com[5:]
            try:
                type = com
                printSortedListOfATypeBySum(TList, type)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com[:5] == "ptst ":
            com = com[5:]
            try:
                sum, type = com.split()
                popTransactionsByTypeAndBelowSum(TList, int(sum), type, undoStack)
            except ValueError:
                print("Sintaxa Invalida!")
        elif com == "u":
            try:
                undoList(TList, undoStack)
            except ValueError:
                print("Nicio operatie ramasa pentru undo")
        elif com == "a":
            printAllTransactions(TList)
        else:
            print("Comanda Invalida!")
            
