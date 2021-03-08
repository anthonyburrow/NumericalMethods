#pragma once

#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> velVerletIter(const vector<double> &X0, const double &dt,
                                 function<double (double, double)> force,
                                 function<double (double, double)> kinetic,
                                 const double &mass);
}