# Să se determine distanța Euclideană între două locații 
# identificate prin perechi de numere. De ex. distanța între (1,5) și (4,1) este 5.0

import math

# O(1)
def prob2(x1: int, y1: int, x2: int, y2: int) -> float:
  return math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

assert prob2(1, 5, 4, 1) == 5.0