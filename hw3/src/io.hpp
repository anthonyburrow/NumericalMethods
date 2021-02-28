#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

namespace mylib {
    struct eulerParams {
        double x0;
        double h;
        int n_points;
    };

    eulerParams readParams(const string &filename);

    void writePoint(const vector<double> &X, ofstream &file);
}
