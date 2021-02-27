#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "io.hpp"
#include "euler.hpp"

using namespace std;

double myDerivative(const vector<double> &X) {
    return -cos(X[0]);
}

double myBoundary(const double &x0) {
    return -sin(x0);
}

int main(int argc, char* argv[]) {
    // Read in parameters
    string filename = "./config/params";
    mylib::eulerParams params = mylib::read_params(filename);
    const double x0 = params.x0;
    const double h = params.h;
    const int n_points = params.n_points;

    vector<double> X0(2);
    X0[0] = x0;
    X0[1] = myBoundary(x0);

    // Write X0 to file

    // Do Euler method iteration
    vector<double> X(2);

    const int max_iter = n_points - 1;
    int count = 0;
    while (true) {
        X = mylib::eulerIter(X0, h, myDerivative);

        // Write X to file

        if (count >= max_iter) { break; }

        X0 = X;
        count++;
    }

    return 0;
}
