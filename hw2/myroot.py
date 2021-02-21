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
    roots = (f'{root1[0]:.17f}, {root1[1]:.17f}\n'
             f'{root2[0]:.16f}, {root2[1]:.16f}')

    print(roots)


if __name__ == '__main__':
    main()
