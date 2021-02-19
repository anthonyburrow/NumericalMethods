#pragma once

#include <vector>
#include <functional>

using namespace std;

namespace mylib {
    vector<double> findRoot(function<vector<double> (vector<double>)> func,
                            function<vector<vector<double>> (vector<double>)> invJacobian,
                            const vector<double> &X0);
}