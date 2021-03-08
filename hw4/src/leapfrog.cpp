#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> leapfrogIter(vector<double> &X,
                                const vector<double> &X0,
                                const double &dt,
                                function<double (double)> acceleration,
                                function<double (double, double)> kinetic,
                                const double &mass) {
        const double &t0 = X0[0];
        const double &x0 = X0[1];
        const double &v0 = X0[2];
        const double &a0 = X0[3];

        X[0] = t0 + dt;
        X[1] = x0 + v0 * dt + 0.5 * a0 * dt * dt;
        X[3] = acceleration(X[1]);
        X[2] = v0 + 0.5 * (a0 + X[3]) * dt;
        X[4] = kinetic(X[2], mass);

        return X;
    }
}