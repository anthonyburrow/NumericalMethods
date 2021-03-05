#pragma once

#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> leapfrogIter(const vector<double> &X0, const double &dt,
                                function<double (double)> acceleration);
}