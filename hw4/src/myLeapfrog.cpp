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

double myTime = 10 * M_PI;

int main(int argc, char* argv[]) {
    // Read in parameters
    string inFilename = "./config/params";
    mylib::eulerParams params = mylib::readParams(inFilename);
    const double &x0 = params.x0;
    const double &v0 = params.v0;
    const int &nPoints = params.nPoints;

    const double dt = myTime / nPoints;

    cout << "Calculating solution..." << endl;

    // Setup output
    string outFilename = "./output/leapfrog.dat";
    cout << "Writing to " << outFilename << endl;
    ofstream outFile(outFilename);

    // Set boundary conditions
    vector<double> X0(4);
    X0[0] = 0;
    X0[1] = x0;
    X0[2] = v0;
    X0[3] = myAcceleration(x0);

    mylib::writePoint(X0, outFile);

    vector<double> X(4);

    int count = 1;
    while (true) {
        X = mylib::leapfrogIter(X0, dt, myAcceleration);

        mylib::writePoint(X, outFile);

        count++;
        if (count >= nPoints) { break; }

        X0 = X;
    }

    outFile.close();
    cout << "Complete." << endl;

    return 0;
}
