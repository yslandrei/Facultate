# Considerându-se o matrice cu n x m elemente întregi și o listă cu perechi 
# formate din coordonatele a 2 căsuțe din matrice ((p,q) și (r,s)), să se calculeze suma 
# elementelor din sub-matricile identificate de fieare pereche.

def prob9(m: list[list[int]], pairs: list[tuple[tuple[int]]]) -> list[int]:
  partialM = [[0 for _ in range(len(m[0]) + 1)] for _ in range(len(m) + 1)]
  for i in range(1, len(m) + 1):
    for j in range(1, len(m[0]) + 1):
      partialM[i][j] = partialM[i - 1][j] + partialM[i][j - 1] - partialM[i - 1][j - 1] + m[i - 1][j - 1]

  result = []
  for pair in pairs:
    (p, q), (r, s) = pair
    result.append(partialM[r + 1][s + 1] - partialM[p][s + 1] - partialM[r + 1][q] + partialM[p][q])

  return result

print(prob9([
[0, 2, 5, 4, 1],
[4, 8, 2, 3, 7],
[6, 3, 4, 6, 2],
[7, 3, 1, 8, 3],
[1, 5, 7, 9, 4]] , [((1, 1), (3, 3)), ((2, 2), (4, 4))])) # [38, 44]


