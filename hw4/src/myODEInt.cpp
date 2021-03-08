#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "io.hpp"

using namespace std;

void myDerivative(const DP t, Vec_I_DP &X, Vec_O_DP &derX) {
    derX[0] = X[1];
    derX[1] = -X[0];
    return;
}

// Want to get the solution for 5 cycles (10pi)
double myTime = 10 * M_PI;

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
    const double &v0 = params.v0;
    const int &nPoints = params.nPoints;
    const double &tol = params.tol;
    const double &hmin = params.hMinRatio;

    const double dt = myTime / nPoints;

    // Start with 10% of the interval size
    const double h = 0.1 * dt;

    cout << "Calculating solution..." << endl;

    // Setup output
    string outFilename = "./output/odeint.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Setup boundary condition
    Vec_IO_DP X(2);
    X[0] = x0;
    X[1] = v0;

    double t0 = 0;

    mylib::writePoint(t0, X, outFile);

    // I believe these are set to be 0 in the code anyways so I don't
    // know what these are even for or what they mean
    int nok = 0;
    int nbad = 0;

    // Do Burlisch-Stoer method
    for (int i = 1; i < nPoints; i++) {
        double t1 = t0 + dt;
        NR::odeint(X, t0, t1, tol, h, hmin, nok, nbad, myDerivative,
                    NR::bsstep);
        mylib::writePoint(t1, X, outFile);
        
        t0 = t1;
    }

    cout << "Complete." << endl;

    return 0;
}
