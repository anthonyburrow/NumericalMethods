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

vector<double> myIterCorrection(const vector<double> &X) {
    vector<double> iterCorrection(2);

    const double tanterm = 0.5 * tan(X[0] + X[1]);
    const double cotterm = 0.5 / tan(X[0] - X[1]);

    iterCorrection[0] = tanterm - cotterm;
    iterCorrection[1] = tanterm + cotterm;

    return iterCorrection;
}

int main(int argc, char* argv[]) {
    vector<double> root(2);

    // Read initial guess
    vector<double> X0(2);
    const std::string filename = "./config/params";
    X0 = mylib::read_params(filename);

    // Check for uninvertible Jacobian (x = y)
    const double eps = std::numeric_limits<double>::epsilon();
    if (abs(X0[0] - X0[1]) < eps) {
        cout << "Components that are equal lead to uninvertible Jacobian. " <<
                "Setting y = " << X0[1] << " + 0.1" << endl;
        X0[1] += 0.1;
    }

    // Solve root
    root = mylib::findRoot(myFunc, myIterCorrection, X0);

    // Print results
    const int n_digits = numeric_limits<double>::max_digits10;
    cout.precision(n_digits);

    cout << "root: " << root[0] << ", " << root[1] << endl;

    return 0;
}
