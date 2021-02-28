import numpy as np
import matplotlib.pyplot as plt


fn = './output/euler.dat'
euler_data = np.loadtxt(fn)

fn = './output/eulerPC.dat'
eulerPC_data = np.loadtxt(fn)

analytic = -np.sin(euler_data[:, 0])

fig, ax = plt.subplots(dpi=200)

fn = './output/euler.pdf'
fig.savefig(fn, format='pdf')
