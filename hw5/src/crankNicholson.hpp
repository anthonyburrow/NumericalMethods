#pragma once

namespace myLib {

    void setupCN(double *A, double *B, double *b, const double &r,
                 const double &NL, const double &NR, const int &n);

    void iterCN(double *n, double *A, double *B, double *b,
                const int &nPoints);

}