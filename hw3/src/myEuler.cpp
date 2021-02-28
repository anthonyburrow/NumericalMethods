#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

#include "io.hpp"
#include "euler.hpp"

using namespace std;

double myDerivative(const vector<double> &X) {
    return -cos(X[0]);
}

double myAnalytic(const double &x) {
    // Assuming y(0) = 0
    return -sin(x);
}

// Want to get the solution for 10 cycles (20pi)
const double myLength = 20 * M_PI;

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    mylib::eulerParams params = mylib::readParams(inFilename);
    const double x0 = params.x0;
    const double h = params.h;
    const double x_max = x0 + myLength;

    // Setup output
    string outFilename = "./output.dat";
    ofstream outFile(outFilename);

    // Setup boundary conditions
    vector<double> X0(2);
    X0[0] = x0;
    X0[1] = myAnalytic(x0);

    mylib::writePoint(X0, outFile);

    // Do Euler method iteration
    vector<double> X(2);

    while (true) {
        X = mylib::eulerIter(X0, h, myDerivative);

        mylib::writePoint(X, outFile);

        if (X[0] >= x_max) { break; }

        X0 = X;
    }
    outFile.close();

    return 0;
}
