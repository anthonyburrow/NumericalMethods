#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "io.hpp"
#include "crankNicolson.hpp"

using namespace std;

double myInitConfig(double x) {
    // Configuration at t = 0
    return exp(-x * x);
}

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    myLib::params params = myLib::readParams(inFilename);
    const double &D = params.D;
    const double &dt = params.dt;
    const double &dx = params.dx;
    const double &xmin = params.xmin;
    const double &xmax = params.xmax;
    const double &NL = params.NL;
    const double &NR = params.NR;
    const double &tmax = params.tmax;

    const double r = D * dt / pow(dx, 2);
    const int nBounds = static_cast<int>((xmax - xmin) / dx) + 1;

    cout << "Using r = " << r << endl;

    cout << "Calculating solution..." << endl;
    
    // Setup output
    string outFilename = "./output/crankNicolson.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Boundary conditions
    double *n = new double[nBounds * nBounds];

    double x = xmin;
    for (int i = 0; i < nBounds; i++) {
        n[i] = myInitConfig(x);
        x += dx;
    }

    myLib::writePoint(n, nBounds, outFile);

    // Calculate solution
    double *supA = new double[nBounds - 1];
    double *diagA = new double[nBounds];
    double *subA = new double[nBounds - 1];
    double *B = new double[nBounds * nBounds];
    double *b = new double[nBounds];

    myLib::setupCN(supA, diagA, subA, B, b, r, NL, NR, nBounds);

    double t = dt;
    while (t < tmax) {
        myLib::iterCN(n, supA, diagA, subA, B, b, nBounds);

        myLib::writePoint(n, nBounds, outFile);
        t += dt;
    }

    delete[] n;
    delete[] supA;
    delete[] diagA;
    delete[] subA;
    delete[] B;
    delete[] b;

    return 0;
}
