# Să se determine produsul scalar a doi vectori rari care conțin numere reale. 
# Un vector este rar atunci când conține multe elemente nule. Vectorii pot avea oricâte dimensiuni. 
# De ex. produsul scalar a 2 vectori unisimensionali [1,0,2,0,3] și [1,2,0,3,1] este 4.

# O(n)
def prob3(v1: list[int], v2: list[int]) -> int:
  return sum(v1[i] * v2[i] for i in range(len(v1)))

assert prob3([1,0,2,0,3], [1,2,0,3,1]) == 4