# Să se genereze toate numerele (în reprezentare binară) cuprinse între 1 și n. 
# De ex. dacă n = 4, numerele sunt: 1, 10, 11, 100.

# O(nlogn)
def prob8(n: int) -> list[int]:
  return [int(bin(i)[2:]) for i in range(1, n + 1)]

assert prob8(4) == [1, 10, 100, 11]