import random
from scipy.stats import binom, hypergeom, geom

#2.i)
print("\n2.")
def simulateTicket():
     numChosen = set(random.sample(range(1, 50), 6))
     ok = True
     nr = 0
     while ok:
         chosenNums = set(random.sample(range(1, 50), 6))
         nr += 1
         if len(chosenNums.intersection(numChosen)) >= 3:
             ok = False
     return nr

def simulateNTicket(numSimulations):
     results = [simulateTicket() for i in range(numSimulations)]
     return results

print("i) ", simulateNTicket(10))

#2.ii)
def probability(numSimulations):
    results = [simulateTicket() for i in range(numSimulations)]
    nr = sum(1 for i in results if i >= 10)
    return nr / numSimulations
    
print("ii) Probabilitatea estimata:", probability(10000))

def aproxProbability():
    prob = hypergeom.pmf(3, 49, 6, 6) + hypergeom.pmf(4, 49, 6, 6) + hypergeom.pmf(5, 49, 6, 6) + hypergeom.pmf(6, 49, 6, 6)
    return 1 - geom.cdf(9, prob)

print("    Probabilitatea teoretica:", aproxProbability())
