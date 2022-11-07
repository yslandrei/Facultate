"""
4.  Scrieți o aplicație pentru gestiunea unui cont bancar. Fiecare tranzacție are ziua,
suma, și tipul (intrare/ieșire). Aplicația permite:

1. Adăugare de noi tranzacții
    • Adaugă tranzacție (se dă ziua, suma, tipul)
    • Actualizare tranzacție (se dă ziua, suma, tipul)
2. Ștergere
    • Șterge toate tranzacțiile de la ziua specificată
    • Șterge tranzacțiile dintr-o perioadă dată (se dă ziua de început și sfârșit)
    • Șterge toate tranzacțiile de un anumit tip
3. Căutări
    • Tipărește tranzacțiile cu sume mai mari decât o sumă dată
    • Tipărește toate tranzacțiile efectuate înainte de o zi și mai mari decât o
    sumă (se dă suma și ziua)
    • Tipărește tranzacțiile de un anumit tip
4. Rapoarte
    • Suma totală a tranzacțiilor de un anumit tip
    • Soldul contului la o dată specificată
    • Tipărește toate tranzacțiile de un anumit tip ordonat după sumă
5. Filtrare
    • Elimină toate tranzacțiile de un anumit tip
    • Elimină toate tranzacțiile mai mici decât o sumă dată care au tipul
    specificat
6. Undo
    • Reface ultima operație (lista de tranzacții revine la ce exista înainte de
    ultima operație care a modificat lista). – Nu folosiți funcția deepCopy
"""

from ui.batchMenu import batchMenu
from ui.menu import menu
from utils.tests import testFunctions


def main():
    testFunctions()
    com = input("Meniul Dorit(n  = Normal, b = Batch): ")
    if com == 'n':
        menu()
    elif com == 'b':
        batchMenu()

if __name__ == "__main__":
    main()