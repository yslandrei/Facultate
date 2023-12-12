import logging
from itertools import product
from random import sample, randrange, random, randint
from math import comb
import numpy as np
from typing import List

from scipy.stats import binom

from matplotlib.pyplot import bar, hist, grid, show, legend


def ex1a():
    cnt = 0
    cnt2 = 0
    for i in range(0, 1000):
        bile_extrase = sample(['red', 'blue', 'green'], counts=[5, 3, 2], k=3)
        if bile_extrase[0] == bile_extrase[1] and bile_extrase[1] == bile_extrase[2] and bile_extrase[0] == 'red':
            cnt += 1
        if bile_extrase[0] == 'red' or bile_extrase[1] == 'red' or bile_extrase[2] == 'red':
            cnt2 += 1
    print("Aproximari pentru probabilitatea (B|A): ", cnt / cnt2)


def ex1b():
    pa = 1 - (comb(5, 3) / comb(10, 3))
    pba = comb(5, 3) / comb(10, 3)
    prez = pba / pa
    print("Probabilitatea P(B|A): ", prez)


def ex2():
    data = [randrange(1, 7) for _ in range(500)]
    bin_edges = [k + 0.5 for k in range(7)]
    hist(data, bin_edges, density=True, rwidth=0.9, color='green', edgecolor='black',
         alpha=0.5, label='frecvente relative')
    distribution = dict([(i, 1 / 6) for i in range(1, 7)])
    bar(distribution.keys(), distribution.values(), width=0.85, color='red', edgecolor='black', alpha=0.6,
        label='probabilitati')
    legend(loc='lower left')
    grid()
    show()


def ex3():
    n = 5
    p = 6 / 10
    sample_size = 1000
    samples = binom.rvs(n, p, size=sample_size)
    print("Lista generate cu 1000 de valori: \n")
    print(samples)
    # calcularea histogramelor
    hist(samples, bins=range(7), density=True)
    grid()
    show()
    prob_teoretica = binom.cdf(5, n, p) - binom.cdf(2, n, p)
    print(f"Valoarea teoretica: {prob_teoretica}")


def ex4():
    distribution = dict([(i, 0) for i in range(3, 19)])
    for z in product(range(1, 7), repeat=3):
        distribution[sum(z)] += (1/216)
    print(max(zip(distribution.values(), distribution.keys())))
    distributionSimulari = dict([(i, 0) for i in range(3, 19)])
    for i in range(0, 2500):
        i = randint(1, 6)
        j = randint(1, 6)
        k = randint(1, 6)
        s = i+j+k
        distributionSimulari[s] += 1
    print(max(zip(distributionSimulari.values(), distributionSimulari.keys())))
    print(max(distributionSimulari.values())/2500)
    data = [randrange(1, 7) + randrange(1, 7) + randrange(1, 7) for _ in range(20000)]
    bin_edges = [k + 0.5 for k in range(3, 19)]
    hist(data, bin_edges, density=True)
    bar(distribution.keys(), distribution.values(), label='probabilitati', color='purple')
    grid()
    show()


if __name__ == '__main__':
     print("Exercitiul 1a: \n")
     ex1a()
     print("Exercitiul 1b: \n")
     ex1b()
     ex2()
     print("Exercitiul 3: \n")
     ex3()
     print("Exercitiul 4: \n")
     ex4()