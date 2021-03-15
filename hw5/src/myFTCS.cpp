#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "io.hpp"
#include "ftcs.hpp"

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
    string outFilename = "./output/ftcs.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Boundary conditions
    vector<double> n(nBounds);
    n[0] = NL;
    n[nBounds - 1] = NR;

    double x = xmin + dx;
    for (int i = 1; i < nBounds - 1; i++) {
        n[i] = myInitConfig(x);
        x += dx;
    }

    myLib::writePoint(n, outFile);

    // Calculate solution
    double t = dt;
    while (t < tmax) {
        myLib::iterFTCS(n, r);

        myLib::writePoint(n, outFile);
        t += dt;
    }

    return 0;
}
