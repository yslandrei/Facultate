from random import sample
from math import factorial, perm, comb
from itertools import permutations, combinations

WORD = 'word'

def prob2():
  permWord = list(permutations(WORD))

  # 2.a)
  print("2.a)", end=" ")
  print(permWord)

  # 2.b)
  print("2.b)", end=" ")
  print(factorial(len(WORD)))

  # 2.c)
  print("2.c)", end=" ")
  print(sample(permWord, 1))


def prob3():
  print("3.")

  aranjamente(WORD, 2)
  combinari(WORD, 2)

def aranjamente(str: str, n: int, numar_total: bool=False, aleator: bool=False):
  aranStr = list(permutations(str, n))
  print("aranjamente:", end=" ")

  if numar_total:
    print(len(aranStr))
  
  elif aleator:
    print(sample(aranStr, 1))

  else:
    print(aranStr)

def combinari(str: str, n: int, numar_total: bool=False, aleator: bool=False):
  combStr = list(combinations(str, n))
  
  print("combinari:", end=" ")
  if numar_total:
    print(len(combStr))
  
  elif aleator:
    print(sample(combStr, 1))

  else:
    print(combStr)


if __name__ == '__main__':
  prob2()
  prob3()