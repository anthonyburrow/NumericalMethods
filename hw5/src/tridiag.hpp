#pragma once

namespace myLib {

    void solveTridiag(double *x, const double *supA, const double *diagA,
                      const double *subA, const double *y, const int &nPoints);

}