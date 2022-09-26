import math as m
import matplotlib.pyplot as plt
import numpy as np


def fun(x):
    r1 = m.exp((m.pow(x, 4) + m.pow(x, 2) - x + m.sqrt(5)) / 5)
    r2 = m.sinh((m.pow(x, 3) + 21.0 * x + 9.0) / (21.0 * x + 6.0))
    return r1 + r2 - 3.0


def readFile(filename):
    array = []
    with open(filename) as f:
        for line in f:
            array.append([float(x) for x in line.split()])
    return array


def drawGraph(a: float, b: float, N: int = 1000):
    X = np.linspace(a, b, N, endpoint=True)
    Y = [fun(x) for x in X]
    plt.plot(X, Y, 'b')


def drawIntervals(array, x0: float = 0.0, stroke: float = 1.0, step: float = 0.5):
    for ind, [a, b] in enumerate(array):
        plt.plot([a, b], [x0 + ind*step, x0 + ind*step], 'g', linewidth=stroke)


def drawPoint(x, y):
    plt.plot(x, y, 'r*')


def createGraph(inputFile, outputFile):
    plt.grid()
    
    arr = readFile(inputFile)
    a, b = arr[0]
    # в последней строке хранятся точка минимума и сам минимум
    xmin, fmin = arr[-1]
    arr = arr[:-1]

    drawGraph(a, b)
    # drawIntervals(arr, step=0.06)
    drawIntervals(arr, step=0.025)
    drawPoint(xmin, fmin)
    plt.savefig(outputFile, dpi=500)
    plt.clf()


if __name__ == '__main__':
    createGraph('pointsDich.txt', 'intervalsDich.png')
    createGraph('pointsGold.txt', 'intervalsGold.png')
