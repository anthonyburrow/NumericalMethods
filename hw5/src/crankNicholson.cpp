#include <iostream>
#include <cblas.h>

using namespace std;

namespace myLib {

    void setupCN(double *A, double *B, double *b, const double &r,
                 const double &NL, const double &NR, const int &nPoints) {
        const double diagA = 2 * (1 + r);
        const double diagB = 2 * (1 - r);
        const double bStart = 2 * r * NL;
        const double bEnd = 2 * r * NR;

        int diag;
        for (int i = 0; i < nPoints; i++) {
            diag = i * (nPoints + 1);
            A[diag] = diagA;
            B[diag] = diagB;

            if (i != 0) {
                A[diag - 1] = -r;
                B[diag - 1] = r;
            }

            if (i != nPoints - 1) {
                A[diag + 1] = -r;
                B[diag + 1] = r;
            }
        }

        b[0] = bStart;
        b[nPoints - 1] = bStart;
    }

    void iterCN(double *n, double *A, double *B, double *b,
                const int &nPoints) {
        // Copy b to c, so b is not overwritten
        double *c = new double[nPoints];
        for (int i = 0; i < nPoints; i++) { c[i] = b[i]; }

        cout << c[0] << " " << b[0] << endl;

        // This does c <- AB + c (I think)
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    nPoints, 1, nPoints,
                    1.0, A, nPoints, B, nPoints,
                    1.0, c, nPoints);

        cout << c[0] << " " << b[0] << endl;

        delete[] c;
    }

}