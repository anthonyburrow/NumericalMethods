#pragma once

#include <vector>

using namespace std;

namespace myHydro {

    void initR(vector<double> &R, const double &initRMax);

    void initU(vector<double> &U);

    void initP(vector<double> &P);

    void initV(vector<double> &V);

    void initT(vector<double> &T);

}