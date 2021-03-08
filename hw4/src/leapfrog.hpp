#pragma once

#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> leapfrogIter(vector<double> &X,
                                const vector<double> &X0,
                                const double &dt,
                                function<double (double)> acceleration,
                                function<double (double, double)> kinetic,
                                const double &mass);
}