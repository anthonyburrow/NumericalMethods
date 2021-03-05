import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


fn = './output/odeint.dat'
odeint_data = np.loadtxt(fn)

fn = './output/leapfrog.dat'
leapfrog_data = np.loadtxt(fn)

fn = './output/velverlet.dat'
# velverlet_data = np.loadtxt(fn)

fn = './config/params'
with open(fn) as file:
    for line in file.readlines():
        if line[0] == '#':
            continue
        x0 = float(line)
        break

def analytic_position(t):
    return x0 * np.cos(t)

def analytic_energy(t):
    return 0.5 * (x0 * np.sin(t))**2

def make_plot(data, filename):
    fig, ax = plt.subplots(2, 2, figsize=(10, 6), gridspec_kw={'height_ratios': [3, 1]},
                           sharex=True, dpi=200)

    t = data[:, 0]
    x = data[:, 1]
    v = data[:, 2]

    # Position vs time
    x_true = analytic_position(t)

    ax[0, 0].plot(t, x, c='k', label='Calculated')
    ax[0, 0].plot(t, x_true, '--', c='r', label='Analytic')

    ax[1, 0].plot(t, x - x_true, c='k')

    fs = 12
    ax[0, 0].set_ylabel('Calculated x(t)', fontsize=fs)
    ax[1, 0].set_xlabel('t', fontsize=fs)
    ax[1, 0].set_ylabel('Residual', fontsize=fs)

    ylim = 1.05 * x0
    ax[0, 0].set_ylim(-ylim, ylim)

    ax[0, 0].legend(loc='upper right', framealpha=1, fontsize=fs)

    # Energy vs time
    T_true = analytic_energy(t)
    T = 0.5 * v**2

    ax[0, 1].plot(t, T, c='k', label='Calculated')
    ax[0, 1].plot(t, T_true, '--', c='r', label='Analytic')

    ax[1, 1].plot(t, T - T_true, c='k')

    ax[0, 1].set_ylabel('Calculated T(t)', fontsize=fs)
    ax[1, 1].set_xlabel('t', fontsize=fs)

    ylim = 1.05 * analytic_energy(np.pi / 2)
    ax[0, 1].set_ylim(0, ylim)

    ax[0, 1].legend(loc='upper right', framealpha=1, fontsize=fs)

    # Global
    [_ax.ticklabel_format(axis='y', style='sci', scilimits=(0, 0)) for _ax in ax[1]]
    [_ax.set_xlim(0, 10 * np.pi) for _ax in ax.ravel()]

    plt.tight_layout()

    # Output
    fn = './doc/figs/{}.pdf'.format(filename)
    fig.savefig(fn, format='pdf', dpi=200)


print('Generating plots...')

make_plot(odeint_data, 'odeint')
make_plot(leapfrog_data, 'leapfrog')
# make_plot(velverlet_data, 'velverlet')
