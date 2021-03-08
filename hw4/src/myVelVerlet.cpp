#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <vector>

#include "io.hpp"
#include "velVerlet.hpp"

using namespace std;

double myForce(const double &x, const double &m) {
    return -m * x;
}

double myKinetic(const double &p, const double &m) {
    return 0.5 * p * p / m;
}

double myTime = 10 * M_PI;

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    mylib::eulerParams params = mylib::readParams(inFilename);
    const double &x0 = params.x0;
    const double &mass = params.m;
    const double p0 = params.v0 * mass;
    const int &nPoints = params.nPoints;

    const double dt = myTime / nPoints;

    cout << "Calculating solution..." << endl;

    // Setup output
    string outFilename = "./output/velverlet.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Set boundary conditions
    vector<double> X0(5);
    X0[0] = 0;
    X0[1] = x0;
    X0[2] = p0;
    X0[3] = myForce(x0, mass);
    X0[4] = myKinetic(p0, mass);

    mylib::writePoint(X0, outFile);

    vector<double> X(5);

    int count = 1;
    while (true) {
        X = mylib::velVerletIter(X0, dt, myForce, myKinetic, mass);

        mylib::writePoint(X, outFile);

        count++;
        if (count >= nPoints) { break; }

        X0 = X;
    }

    outFile.close();
    cout << "Complete." << endl;

    return 0;
}
