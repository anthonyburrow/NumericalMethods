#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include "rootsolve.hpp"
#include "io.hpp"

using namespace std;

vector<double> myFunc(const vector<double> &X) {
    vector<double> f(2);

    f[0] = sin(X[0] + X[1]);
    f[1] = cos(X[0] - X[1]);

    return f;
}

vector<vector<double>> myInvJacobian(const vector<double> &X) {
    vector<vector<double>> invJacobian(2, vector<double>(2));

    const double costerm = cos(X[0] + X[1]);
    const double sinterm = sin(X[0] - X[1]);

    invJacobian[0][0] = sinterm;
    invJacobian[0][1] = costerm;
    invJacobian[1][0] = sinterm;
    invJacobian[1][1] = -costerm;

    const double inv_det = 1 / (2 * sinterm * costerm);

    for (vector<double> &row : invJacobian) {
        for (double &elem : row) {
            elem *= inv_det;
        }
    }

    return invJacobian;
}

int main(int argc, char* argv[]) {
    vector<double> root(2);

    vector<double> X0(2);
    const std::string filename = "./config/params";
    X0 = mylib::read_params(filename);

    root = mylib::findRoot(myFunc, myInvJacobian, X0);

    const int n_digits = numeric_limits<double>::max_digits10;
    cout.precision(n_digits);

    cout << "root: " << root[0] << ", " << root[1] << endl;

    return 0;
}
