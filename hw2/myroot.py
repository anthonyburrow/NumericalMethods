import numpy as np
from scipy.optimize import fsolve


def myFunc(X):
    f = np.zeros_like(X)

    f[0] = np.sin(X.sum())
    f[1] = np.cos(X[0] - X[1])

    return f


def main():
    X0 = np.array([0.1, 1])
    root = fsolve(myFunc, X0)

    print(root)


if __name__ == '__main__':
    main()
