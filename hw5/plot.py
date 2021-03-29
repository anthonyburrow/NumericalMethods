import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as col
plt.switch_backend('agg')


def get_params(File):
    params = {}

    count = 0
    for line in File:
        if line[0] == '#' or line == '\n':
            continue

        val = np.float64(line)

        if count == 0:
            params['D'] = val
        elif count == 1:
            params['dt'] = val
        elif count == 2:
            params['dx'] = val
        elif count == 3:
            params['xmin'] = val
        elif count == 4:
            params['xmax'] = val
        elif count == 5:
            params['NL'] = val
        elif count == 6:
            params['NR'] = val
        elif count == 7:
            params['tmax'] = val
        count += 1

    return params


def make_plot(filename):
    fn = './output/{fn}.dat'.format(fn = filename)
    ftcs_data = np.loadtxt(fn, dtype=np.float64).T

    fn = './config/params'
    with open(fn) as File:
        params = get_params(File)

    xmin = params['xmin']
    xmax = params['xmax']
    tmin = 0
    tmax = params['tmax']

    r = params['D'] * params['dt'] / params['dx']**2

    fig, ax = plt.subplots(dpi=200)

    nmin = 1e-12
    nmax = 1
    scmap = ax.imshow(ftcs_data, extent=(tmin, tmax, xmin, xmax),
                      aspect='auto', cmap='binary',
                      norm=col.LogNorm(vmin=nmin, vmax=nmax))

    fs = 18
    ax.set_xlabel('t', fontsize=fs)
    ax.set_ylabel('x', fontsize=fs)
    ax.tick_params(axis='both', labelsize=fs - 4)

    cb = fig.colorbar(scmap, ticks=[1e-12, 1e-8, 1e-4, 1])
    cb.ax.tick_params(labelsize=fs - 4)
    cb.set_label('n', fontsize=fs)

    plt.tight_layout()

    fn = './doc/figs/{fn}-r{r:.3f}.pdf'.format(fn = filename, r=r)
    fig.savefig(fn, fmt='pdf', dpi=200)

    plt.close('all')


make_plot('ftcs')
make_plot('crankNicholson')
