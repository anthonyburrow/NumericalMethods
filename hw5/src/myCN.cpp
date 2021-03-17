#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "io.hpp"
#include "crankNicholson.hpp"

using namespace std;

extern "C" {
    #include <cblas.h>
    void cblas_dgemm(CBLAS_ORDER Order, CBLAS_TRANSPOSE TransA,
                     CBLAS_TRANSPOSE TransB, int M, int N, int K, double alpha,
                     const double *A, int lda, const double *B, int ldb,
                     double beta, double *C, int ldc);
}

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
    double *n = new double[nBounds * nBounds];

    double x = xmin;
    for (int i = 0; i < nBounds; i++) {
        n[i] = myInitConfig(x);
        x += dx;
    }

    // myLib::writePoint(n, outFile);

    // Calculate solution
    double *A = new double[nBounds * nBounds];
    double *B = new double[nBounds * nBounds];
    double *b = new double[nBounds];

    myLib::setupCN(A, B, b, r, NL, NR, nBounds);

    myLib::iterCN(n, A, B, b, nBounds);

    // double t = dt;
    // while (t < tmax) {
    //     myLib::iterCN(n, A, B, b, nBounds);

    //     myLib::writePoint(n, outFile);
    //     t += dt;
    // }

    delete[] n;
    delete[] A;
    delete[] B;
    delete[] b;

    return 0;
}
