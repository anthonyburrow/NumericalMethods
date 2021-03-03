#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> leapfrogIter(const vector<double> &X0, const double &dt,
                                function<double (double)> acceleration) {
        vector<double> X(4);

        X[0] = X0[0] + dt;
        X[1] = X0[1] + X0[2] * dt + 0.5 * X0[3] * dt * dt;
        X[3] = acceleration(X[1]);
        X[2] = X0[2] + 0.5 * (X0[3] + X[3]);

        return X;
    }
}