#include <iostream>
#include <mkl.h>

#include "tridiag.hpp"

using namespace std;

namespace myLib {

    void setupCN(double *supA, double *diagA, double *subA, double *B,
                 double *b, const double &r, const double &NL,
                 const double &NR, const int &nPoints) {
        const double diagAval = 2 * (1 + r);
        const double diagB = 2 * (1 - r);
        const double bStart = 2 * r * NL;   // questionable
        const double bEnd = 2 * r * NR;   // questionable

        int diag;
        for (int i = 0; i < nPoints; i++) {
            diagA[i] = diagAval;

            diag = i * (nPoints + 1);
            B[diag] = diagB;

            if (i != 0) {
                B[diag - 1] = r;
            }

            if (i != nPoints - 1) {
                subA[i] = -r;
                supA[i] = -r;

                B[diag + 1] = r;
            }
        }

        b[0] = bStart;
        b[nPoints - 1] = bStart;

    }

    void iterCN(double *n, const double *supA, const double *diagA,
                const double *subA, const double *B, const double *b,
                const int &nPoints) {
        // Copy b to tmp, so b is not overwritten
        double *tmp = new double[nPoints];
        for (int i = 0; i < nPoints; i++) { tmp[i] = b[i]; }

        // This does tmp <- Bn + tmp (I think)
        cblas_dgemv(CblasRowMajor, CblasNoTrans,
                    nPoints, nPoints,
                    1.0, B, nPoints, n, 1,
                    1.0, tmp, 1);

        // Solve An = tmp for n with A being tridiagonal
        myLib::solveTridiag(n, supA, diagA, subA, tmp, nPoints);

        delete[] tmp;
    }

}