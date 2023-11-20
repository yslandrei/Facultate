import matplotlib.pyplot as pyplot
import random
import math


def calcCircleAprox(n):
    corect = 0
    xs = []
    ys = []
    Correctxs = []
    Correctys = []
    pyplot.axis([0, 1, 0, 1])
    for i in range(n):
        x, y = random.random(), random.random()
        distance = math.dist([0.5, 0.5], [x, y])
        if distance < 0.5:
            Correctxs.append(x)
            Correctys.append(y)
            corect += 1
        else:
            xs.append(x)
            ys.append(y)

    pyplot.plot(xs, ys, 'yo')
    pyplot.plot(Correctxs, Correctys, 'go')
    pyplot.show()
    return corect / n


def calcSquareAprox(n):
    corect = 0
    xs = []
    ys = []
    Correctxs = []
    Correctys = []
    pyplot.axis([0, 1, 0, 1])
    for i in range(n):
        x, y = random.random(), random.random()
        dists = [math.dist([1.0, 1.0], [x, y]), math.dist([0.0, 1.0], [x, y]),
                 math.dist([1.0, 0.0], [x, y]), math.dist([0.0, 0.0], [x, y])]
        distCentru = math.dist([0.5, 0.5], [x, y])
        ok = True
        for j in range(4):
            if distCentru > dists[j]:
                ok = False
                break
        if ok:
            Correctxs.append(x)
            Correctys.append(y)
            corect += 1
        else:
            xs.append(x)
            ys.append(y)

    pyplot.plot(xs, ys, 'yo')
    pyplot.plot(Correctxs, Correctys, 'go')
    pyplot.show()
    return corect / n

def calcFlowerAprox(n):
    corect = 0
    xs = []
    ys = []
    Correctxs = []
    Correctys = []
    pyplot.axis([0, 1, 0, 1])
    for i in range(n):
        x, y = random.random(), random.random()
        dists = [math.dist([0.5, 1.0], [x, y]), math.dist([0.0, 0.5], [x, y]),
                 math.dist([0.5, 0.0], [x, y]), math.dist([1.0, 0.5], [x, y])]

        common = 0
        for j in range(4):
            if 0.5 > dists[j]:
               common+=1
        if common>=2:
            Correctxs.append(x)
            Correctys.append(y)
            corect += 1
        else:
            xs.append(x)
            ys.append(y)

    pyplot.plot(xs, ys, 'yo')
    pyplot.plot(Correctxs, Correctys, 'go')
    pyplot.show()
    return corect / n

N = 2000


print("2.")
print("i)")
print("Probabilitate Aproximata=" + str(calcCircleAprox(N)))
print("Probabilitate Exacta=" + str(math.pi/4))
print("ii)")
print("Probabilitate Aproximata=" + str(calcSquareAprox(N)))
print("Probabilitate Exacta=" + str(1/2))
print("iii)")
print("Probabilitate Aproximata=" + str(calcFlowerAprox(N)))
print("Probabilitate Exacta=" + str(math.pi/2-1))