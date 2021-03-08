#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> velVerletIter(const vector<double> &X0, const double &dt,
                                 function<double (double, double)> force,
                                 const double &mass) {
        vector<double> X(4);

        const double &t0 = X0[0];
        const double &x0 = X0[1];
        const double &p0 = X0[2];
        const double &f0 = X0[3];

        X[0] = t0 + dt;
        X[1] = x0 + p0 * dt + 0.5 * f0 * dt * dt;
        X[3] = force(X[1], mass);
        X[2] = p0 + 0.5 * (f0 + X[3]) * dt;

        return X;
    }
}