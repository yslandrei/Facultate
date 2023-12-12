import random
import matplotlib.pyplot as plt
import numpy as np

#1.a)
def simulate(numSteps, p):
    currPosition = 0
    positions = [currPosition]
    for i in range(numSteps):
        if random.uniform(0, 1) < p:
            currPosition += 1
        else:
            currPosition -= 1
        positions.append(currPosition)
    return positions

positions = simulate(10, 0.5)
print("\n1.")
print("a)", positions)

#1.b)
def simulateN(n, numSteps, probability):
    finalPositions = []

    for i in range(n):
        finalPos = simulate(numSteps, probability)
        finalPositions.extend(finalPos)  

    plt.hist(finalPositions)
    plt.grid(axis='y')
    plt.xticks(np.arange(min(finalPositions), max(finalPositions), 1))
    plt.xlabel('Pozitie finala pe axa')
    plt.title('b) Histograma pozitiilor finale pe axa')
    plt.show()

simulateN(1000, 5, .5)

#1.c)
def simulateCircle(numSteps, probR, numNodes):
    currPosition = 0
    positions = [currPosition]
    for i in range(numSteps):
        if random.uniform(0, 1) < probR:
            currPosition = (currPosition + 1) % numNodes 
        else:
            currPosition = (currPosition - 1) % numNodes
        positions.append(currPosition)
    return positions

def histogramSimulateCircle(n, numSteps, probR, numNodes):
    finalPositions = []
    for i in range(n):
        finalPos = simulateCircle(numSteps, probR, numNodes)
        finalPositions.extend(finalPos)
    plt.hist(finalPositions)
    plt.grid(axis='y')
    plt.xlabel('Pozitie finala pe cerc')
    plt.title('c) Histograma pozitiilor pe cerc')
    plt.show()

histogramSimulateCircle(1000, 10, .5, 5)
