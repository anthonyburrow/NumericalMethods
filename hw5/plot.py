import numpy as np
import matplotlib.pyplot as plt
plt.switch_backend('agg')


xmin = -20
xmax = 20
tmin = 0
tmax = 2

def make_plot(filename):
    fn = './output/{fn}.dat'.format(fn = filename)
    ftcs_data = np.loadtxt(fn, dtype=np.float64).T

    fig, ax = plt.subplots(dpi=200)

    scmap = ax.imshow(ftcs_data, extent=(tmin, tmax, xmin, xmax), aspect='auto',
                      cmap='binary')

    fs = 18
    ax.set_xlabel('t', fontsize=fs)
    ax.set_ylabel('x', fontsize=fs)
    ax.tick_params(axis='both', labelsize=fs - 4)

    cb = fig.colorbar(scmap, ticks=[0, 0.2, 0.4, 0.6, 0.8, 1])
    cb.ax.tick_params(labelsize=fs - 4)
    cb.set_label('n', fontsize=fs)

    plt.tight_layout()

    fn = './doc/figs/{fn}.pdf'.format(fn = filename)
    fig.savefig(fn, fmt='pdf', dpi=200)

    plt.close('all')


make_plot('ftcs')
