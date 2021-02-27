#pragma once

#include <string>
#include <vector>

using namespace std;

namespace mylib {
    struct eulerParams {
        double x0;
        double h;
        int n_points;
    };

    eulerParams read_params(const std::string &filename);
}
