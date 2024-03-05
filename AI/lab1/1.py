# Să se determine ultimul (din punct de vedere alfabetic) cuvânt care 
# poate apărea într-un text care conține mai multe cuvinte separate prin ” ” (spațiu). 
# De ex. ultimul (dpdv alfabetic) cuvânt din ”Ana are mere rosii si galbene” este cuvântul "si".

# O(n)
def prob1(s: str) -> str:
  s = s.split(' ')
  return max(s)

# O(nlogn)
def prob1_b(s: str) -> str:
  s = s.split(' ')
  return sorted(s)[-1]

assert prob1("Ana are mere rosii si galbene") == "si"
assert prob1_b("Ana are mere rosii si galbene") == "si"