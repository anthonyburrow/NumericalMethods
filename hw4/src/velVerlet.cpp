#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> velVerletIter(vector<double> &X,
                                 const vector<double> &X0,
                                 const double &dt,
                                 function<double (double, double)> force,
                                 function<double (double, double)> kinetic,
                                 const double &mass) {
        const double &t0 = X0[0];
        const double &x0 = X0[1];
        const double &p0 = X0[2];
        const double &f0 = X0[3];

        X[0] = t0 + dt;
        X[1] = x0 + (p0 * dt + 0.5 * f0 * dt * dt) / mass;
        X[3] = force(X[1], mass);
        X[2] = p0 + 0.5 * (f0 + X[3]) * dt;
        X[4] = kinetic(X[2], mass);

        return X;
    }
}