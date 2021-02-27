#pragma once

#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> eulerIter(const vector<double> &X0,
                             const double &h,
                             function<double (vector<double>)> deriv);

    vector<double> eulerPCIter(const vector<double> &X0,
                               const double &h,
                               function<double (vector<double>)> deriv);
}