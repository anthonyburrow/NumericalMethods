import numpy as np
from scipy.optimize import fsolve


def myFunc(X):
    f = np.zeros_like(X)

    f[0] = np.sin(X.sum())
    f[1] = np.cos(X[0] - X[1])

    return f


def main():
    # Typing as np.double is unnecessary with 64-bit Python
    X0 = np.array([-1, 1], dtype=np.double)
    root1 = fsolve(myFunc, X0)

    X0 = np.array([-2, 2], dtype=np.double)
    root2 = fsolve(myFunc, X0)

    print('Python roots:')
    # schooner doesn't like f-strings for some reason...
    roots = '{r1:.17f}, {r2:.17f}\n'.format(r1 = root1[0], r2 = root1[1])
    roots += '{r1:.17f}, {r2:.17f}'.format(r1 = root2[0], r2 = root2[1])

    print(roots)


if __name__ == '__main__':
    main()
