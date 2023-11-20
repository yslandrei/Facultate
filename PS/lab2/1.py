import random
import math

def aproximare(n):
    cazuri_posibile = 99999
    cazuri_favorabile = 0
    for i in range(cazuri_posibile):
        d = set()
        for j in range(n):
            d.add(random.randint(1, 365))
        if len(d) != n:
            cazuri_favorabile += 1
    return cazuri_favorabile / cazuri_posibile

def exacta(n):
    cazuri_posibile = 365 ** n
    cazuri_favorabile = math.factorial(365) / math.factorial(365 - n)
    return 1 - cazuri_favorabile / cazuri_posibile




print("1.")
print("Probabilitate Aproximata=" + str(aproximare(23)))
print("Probabilitate Exacta=" + str(exacta(23)))
