#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace myLib {

    struct params {
        double D;
        double dt;
        double dx;
        double xmin;
        double xmax;
        double NL;
        double NR;
        double tmax;
    };

    params readParams(const std::string &filename);

    void writePoint(const std::vector<double> &n, std::ofstream &file);

}
