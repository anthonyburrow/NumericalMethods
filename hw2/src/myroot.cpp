#include <iostream>
#include <vector>
#include <cmath>

#include "rootsolve.hpp"

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

    vector<double> X0 = {0, 0};

    mylib::findRoot(myFunc, myInvJacobian, X0);

    return 0;
}
