#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
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
    stringstream outFilename;
    outFilename << fixed << setprecision(3)
                << "./output/ftcs-r" << r << ".dat";
    string outFilenameStr = outFilename.str();
    cout << "Writing to " << outFilenameStr << endl;
    ofstream outFile(outFilenameStr);

    // Boundary conditions
    vector<double> n(nBounds);

    double x = xmin;
    for (int i = 0; i < nBounds; i++) {
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
