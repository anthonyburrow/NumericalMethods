#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>

#include "io.hpp"
#include "leapfrog.hpp"

using namespace std;

double myAcceleration(const double &x) {
    return -x;
}

double myKinetic(const double &v, const double &m) {
    return 0.5 * m * v * v;
}

double myTime = 10 * M_PI;

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    mylib::eulerParams params = mylib::readParams(inFilename);
    const double &x0 = params.x0;
    const double &v0 = params.v0;
    const double &mass = params.m;
    const int &nPoints = params.nPoints;

    const double dt = myTime / nPoints;

    cout << "Calculating solution..." << endl;

    // Setup output
    string outFilename = "./output/leapfrog.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);
    outFile << "time\tposition\tvelocity\tkinetic" << endl;

    // Set boundary conditions
    vector<double> X0(5);
    X0[0] = 0;
    X0[1] = x0;
    X0[2] = v0;
    X0[3] = myAcceleration(x0);
    X0[4] = myKinetic(v0, mass);

    mylib::writePoint(X0, outFile);

    vector<double> X(5);

    int count = 1;
    while (true) {
        X = mylib::leapfrogIter(X, X0, dt, myAcceleration, myKinetic, mass);

        mylib::writePoint(X, outFile);

        count++;
        if (count >= nPoints) { break; }

        // This assigns values of X to those of X0
        // (so it isn't a reference)
        X0 = X;
    }

    outFile.close();
    cout << "Complete." << endl;

    return 0;
}
