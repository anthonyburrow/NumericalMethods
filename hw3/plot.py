import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


fn = './output/euler.dat'
euler_data = np.loadtxt(fn)

fn = './output/eulerPC.dat'
eulerPC_data = np.loadtxt(fn)

fn = './output/odeint.dat'
odeint_data = np.loadtxt(fn)

def analytic(X):
    return -np.sin(X)

def make_plot(data, filename):
    fig, ax = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]},
                           sharex=True)

    x = data[:, 0]
    y = data[:, 1]

    res = y - analytic(data[:, 0])

    ax[0].plot(x, y, c='k')

    ax[1].plot(x, res, c='k')

    ax[0].set_ylabel('Calculated y(x)')
    ax[1].set_xlabel('x')
    ax[1].set_ylabel('Residual y(x)')

    ax[0].set_ylim(-1, 1)
    [_ax.set_xlim(0, 20 * np.pi) for _ax in ax]

    plt.tight_layout()

    fn = './output/figs/{}.pdf'.format(filename)
    fig.savefig(fn, format='pdf')


print('Generating plots...')

make_plot(euler_data, 'euler')
make_plot(eulerPC_data, 'eulerPC')
make_plot(odeint_data, 'odeint')
