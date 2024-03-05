# Considerându-se o matrice cu n x m elemente binare (0 sau 1) sortate crescător pe linii, să se 
# identifice indexul liniei care conține cele mai multe elemente de 1.

# O(n * m)
def prob10(matrix: list[list[int]]) -> int:
  result = 0
  maxSum = 0
  for i in range(len(matrix)):
    if sum(matrix[i]) > maxSum:
      result = i
      maxSum = sum(matrix[i])
  return result + 1

assert prob10([
  [0, 0, 0, 1, 1], 
  [0, 1, 1, 1, 1], 
  [0, 0, 1, 1, 1]]) == 2