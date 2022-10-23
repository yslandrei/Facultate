"""
P1. Numere

    Creați un program care lucrează cu numere complexe (a + bi). Programul
gestionează o listă de numere complexe și permite efectuarea repetată a
următoarelor acțiuni:

1. Adaugă număr în listă.
    • Adaugă număr complex la sfârșitul listei
    • Inserare număr complex pe o poziție dată.
2. Modifică elemente din listă.
    • Șterge element de pe o poziție dată.
    • Șterge elementele de pe un interval de poziții.
    • Înlocuiește toate aparițiile unui număr complex cu un alt număr
      complex.
3. Căutare numere.
    • Tipărește partea imaginara pentru numerele din listă. Se dă intervalul
      de poziții (sub secvența).
    • Tipărește toate numerele complexe care au modulul mai mic decât 10
    • Tipărește toate numerele complexe care au modulul egal cu 10
4. Operații cu numerele din listă
    • suma numerelor dintr-o subsecventă dată (se da poziția de început și
      sfârșit).
    • Produsul numerelor dintr-o subsecventă dată (se da poziția de început
      și sfârșit).
    • Tipărește lista sortată descrescător după partea imaginara
5. Filtrare.
    • Filtrare parte reala prim. elimină din listă numerele complexe la care
      partea reala este prim.
    • Filtrare modul. elimina din lista numerele complexe la care modulul
      este <,= sau > decât un număr dat.
6. Undo
    • Reface ultima operație (lista de numere revine la numerele ce existau
      înainte de ultima operație care a modificat lista). Nu folosiți funcția
      deepCopy
"""

from tests import testUndo, testFunctions
from menu import menu

def main():
    testFunctions()
    testUndo()
    menu()

if __name__ == '__main__':
  main()