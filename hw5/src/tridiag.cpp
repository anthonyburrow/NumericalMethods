
namespace myLib {

    void solveTridiag(double *x, const double *supA, const double *diagA,
                      const double *subA, const double *y, const int &nPoints) {
        // Solves Ax = y with A tridiagonal
        double *tmpDiagA = new double[nPoints];
        for (int i = 0; i < nPoints; i++) { tmpDiagA[i] = diagA[i]; }

        double *tmpY = new double[nPoints];
        for (int i = 0; i < nPoints; i++) { tmpY[i] = y[i]; }

        double t;
        for (int i = 1; i < nPoints; i++) {
            t = supA[i] / tmpDiagA[i - 1];
            tmpDiagA[i] = tmpDiagA[i] - subA[i - 1] * t;
            tmpY[i] = tmpY[i] - tmpY[i - 1] * t;
        }

        x[nPoints - 1] = tmpY[nPoints - 1] / tmpDiagA[nPoints - 1];

        for (int i = nPoints - 2; i > -1; i--) {
            x[i] = (tmpY[i] - subA[i] * x[i + 1]) / tmpDiagA[i];
        }

        delete[] tmpDiagA;
        delete[] tmpY;
    }

}