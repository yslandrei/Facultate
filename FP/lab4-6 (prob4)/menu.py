
from functions import appendTransaction, balanceOfAccountUntilDay, createTransaction, modifyTransaction, popTransactionsByDate, popTransactionsByDay, popTransactionsByType, popTransactionsByTypeAndBelowSum, printAllTransactions, printSortedListOfATypeBySum, printTransactionsByType, printTransactionsHigherThanSum, printTransactionsHigherThanSumAndLowerThanDay, sumOfTransactionsByType
from undo import undoList


def printMenu():
    print("\n")
    print("• Adaugă tranzacție                                               - add [ziua] [suma] [tip]")
    print("• Actualizare tranzacție                                          - upt [ziua] [suma] [tip] [newSum]")
    print("• Șterge toate tranzacțiile de la ziua specificată                - deld [ziua]")
    print("• Șterge tranzacțiile dintr-o perioadă dată                       - delm [st] [dr]")
    print("• Șterge toate tranzacțiile de un anumit tip                      - delt [tip]")
    print("• Tipărește tranzacțiile cu sume mai mari decât o sumă dată       - pts [suma]") 
    print("• Tipărește toate tranzacțiile efectuate înainte de o zi          - ptd [ziua] [suma]")
    print("  și mai mari decât o sumă")
    print("• Tipărește tranzacțiile de un anumit tip                         - ptt [tip]")
    print("• Suma totală a tranzacțiilor de un anumit tip                    - stt [tip]")
    print("• Soldul contului la o dată specificată                           - bbd [ziua]")
    print("• Tipărește toate tranzacțiile de un anumit tip ordonat după sumă - ptss [tip]")
    print("• Elimină toate tranzacțiile mai mici decât o sumă dată           - ptlst [suma] [tip]")
    print("  care au tipul specificat")

def menu():
    TList = []
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
            day, sum, type = com.split()
            appendTransaction(TList, createTransaction(int(day), int(sum), type), undoStack)
        elif com[:4] == "upt ":
            com = com[4:]
            day, sum, type, newSum = com.split()
            modifyTransaction(TList, createTransaction(int(day), int(sum), type), int(newSum), undoStack)
        elif com[:5] == "deld ":
            com = com[5:]
            day = int(com)
            popTransactionsByDay(TList, day, undoStack)
        elif com[:5] == "delm ":
            com = com[5:]
            st, dr = com.split()
            popTransactionsByDate(TList, int(st), int(dr), undoStack)
        elif com[:5] == "delt ":
            com = com[5:]
            type = com
            popTransactionsByType(TList, type, undoStack)
        elif com[:4] == "pts ":
            com = com[4:]
            sum = com
            printTransactionsHigherThanSum(TList, int(sum), undoStack)
        elif com[:4] == "ptd ":
            com = com[4:]
            day, sum = com.split()
            printTransactionsHigherThanSumAndLowerThanDay(TList, int(sum), int(day))
        elif com[:4] == "ptt ":
            com = com[4:]
            type = com
            printTransactionsByType(TList, type)
        elif com[:4] == "stt ":
            com = com[4:]
            type = com
            sumOfTransactionsByType(TList, type)
        elif com[:4] == "bbd ":
            com = com[4:]
            day = com
            balanceOfAccountUntilDay(TList, int(day))
        elif com[:5] == "ptss ":
            com = com[5:]
            type = com
            printSortedListOfATypeBySum(TList, type)
        elif com[:6] == "ptlst ":
            com = com[6:]
            sum, type = com.split()
            popTransactionsByTypeAndBelowSum(TList, int(sum), type, undoStack)
        elif com == "u":
            try:
                undoList(TList, undoStack)
            except ValueError:
                print("Nicio operatie ramasa pentru undo")
        elif com == "a":
            printAllTransactions(TList)
        else:
            print("Comanda Invalida!")
            
