#include <cmath>
#include <limits>
#include <stdexcept>

#include "quadratic.hpp"

namespace {
    double sqrt_discriminant(const double &c1, const double &c2) {
        const double discrim = std::pow(c1, 2) - c2;

        // Throw exception if discriminant is negative (complex solution)
        if (discrim < 0) {
            const std::string msg =
                "Error: Imaginary value(s) encountered in solution.";
            throw std::runtime_error(msg);
        }

        const double sqrt_discrim = std::sqrt(discrim);

        return sqrt_discrim;
    }

    mylib::quad_solution solve_standard(const double &c1, const double &c2) {
        mylib::quad_solution x;
        const double sqrt_discrim = sqrt_discriminant(c1, c2);

        x.x1 = -(sqrt_discrim + c1);
        x.x2 = sqrt_discrim - c1;

        return x;
    }

    mylib::quad_solution solve_accurate(const double &c1, const double &c2) {
        mylib::quad_solution x;
        const double sqrt_discrim = sqrt_discriminant(c1, c2);

        x.x1 = -c1 - std::copysign(sqrt_discrim, c1);
        x.x2 = c2 / x.x1;

        return x;
    }
}

namespace mylib {

    quad_solution solve_quadratic(mylib::quad_params &params, const bool accurate = 1) {
        const double &a = params.a;
        const double &b = params.b;
        const double &c = params.c;

        // Check if `a` is (machine) 0
        const double eps = std::numeric_limits<double>::epsilon();

        if (std::abs(a) < eps) {
            if (std::abs(b) < eps & std::abs(c) < eps) {
                const std::string msg =
                    "Error: All parameters are zero. Either all params "
                    "are nonzero, or the config/param file is not found. "
                    "Try running the executable from the root directory.";
                throw std::runtime_error(msg);
            }

            const std::string msg =
                "Error: Attempting to solve quadratic equation "
                "with no second-degree term.";
            throw std::runtime_error(msg);
        }

        // Format as x**2 + 2* c1 * x + c2
        const double c1 = 0.5 * b / a;
        const double c2 = c / a;

        // Return either the standard solution or
        // accurate (no subtraction) solution
        if (accurate) { return solve_accurate(c1, c2); }
        else { return solve_standard(c1, c2); }
    }

}
