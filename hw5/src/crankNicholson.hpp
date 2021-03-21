#pragma once

namespace myLib {

    void setupCN(double *supA, double *diagA, double *subA, double *B,
                 double *b, const double &r, const double &NL,
                 const double &NR, const int &nPoints);

    void iterCN(double *n, const double *supA, const double *diagA,
                const double *subA, const double *B, const double *b,
                const int &nPoints);

}