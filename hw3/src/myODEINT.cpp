#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "io.hpp"

using namespace std;

void myDerivative(const DP x, Vec_I_DP &y, Vec_O_DP &dery) {
    dery[0] = -cos(x);
    return;
}

double myAnalytic(const double &x) {
    // Assuming y(0) = 0
    return -sin(x);
}

// Want to get the solution for 10 cycles (20pi)
const double myLength = 20 * M_PI;

// Dumb extern variables that need to be declared for odeint.cpp
DP dxsav;
int kmax, kount;
Vec_DP *xp_p;
Mat_DP *yp_p;

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    mylib::eulerParams params = mylib::readParams(inFilename);
    const double &x0 = params.x0;
    const double &nPoints = params.nPoints;
    const double &tol = params.tol;
    const double &hmin = params.hMinRatio;
    const double &xMax = x0 + myLength;
    const double &h = myLength / nPoints;

    // Setup output
    string outFilename = "./output/odeint.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Setup boundary condition
    Vec_IO_DP y(1);
    y[0] = myAnalytic(x0);

    vector<double> X(nPoints);
    X[0] = x0;

    mylib::writePoint(x0, y[0], outFile);

    // I believe these are set to be 0 in the code anyways so I don't
    // know what these are even for or what they mean
    int nok = 0;
    int nbad = 0;

    // Do Burlisch-Stoer method
    cout << "Calculating solution..." << endl;

    for (int i = 1; i < nPoints; i++) {
        double &x0 = X[i - 1];
        double x1 = x0 + h;
        X[i] = x1;
        NR::odeint(y, x0, x1, tol, h, hmin, nok, nbad, myDerivative,
                    NR::bsstep);
        mylib::writePoint(x1, y[0], outFile);
    }

    cout << "Complete." << endl;

    return 0;
}
