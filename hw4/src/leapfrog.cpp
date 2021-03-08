#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> leapfrogIter(const vector<double> &X0, const double &dt,
                                function<double (double)> acceleration) {
        vector<double> X(4);

        const double &t0 = X0[0];
        const double &x0 = X0[1];
        const double &v0 = X0[2];
        const double &a0 = X0[3];

        X[0] = t0 + dt;
        X[1] = x0 + v0 * dt + 0.5 * a0 * dt * dt;
        X[3] = acceleration(X[1]);
        X[2] = v0 + 0.5 * (a0 + X[3]) * dt;

        return X;
    }
}