#pragma once

#include "quadratic.hpp"

namespace mylib {

    struct quad_params {
        double a;
        double b;
        double c;
    };

    struct quad_solution {
        double x1;
        double x2;
    };

    quad_solution solve_quadratic(mylib::quad_params &params, const bool accurate);

}
