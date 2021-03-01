#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> eulerIter(const vector<double> &X0,
                             const double &h,
                             function<double (vector<double>)> deriv) {
        vector<double> X(2);

        X[0] = X0[0] + h;
        X[1] = X0[1] + deriv(X0) * h;

        return X;
    }

    vector<double> eulerPCIter(const vector<double> &X0,
                               const double &h,
                               function<double (vector<double>)> deriv) {
        vector<double> X(2);
        X = eulerIter(X0, h, deriv);

        double y_new = X0[1] + 0.5 * (deriv(X0) + deriv(X)) * h;

        X[1] = y_new;

        return X;
    }
}
