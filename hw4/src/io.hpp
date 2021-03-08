#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "nr.h"

using namespace std;

namespace mylib {
    struct eulerParams {
        double x0;
        double v0;
        double m;
        int nPoints;
        double tol;
        double hMinRatio;
    };

    eulerParams readParams(const string &filename);

    void writePoint(const vector<double> &X, ofstream &file);

    void writePoint(const double &x, const Vec_IO_DP &y,
                    const double &E, ofstream &file);
}
