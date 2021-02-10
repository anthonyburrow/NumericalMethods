#include <iostream>
#include <limits>
// #include <cmath>
#include <stdlib.h>

#include "quadratic.hpp"
#include "io.hpp"

int main(int argc, char* argv[]) {
    const std::string filename = "./config/params";
    mylib::quad_params params = mylib::read_params(filename);

    // Get quadratic solutions
    mylib::quad_solution standard_x;
    mylib::quad_solution accurate_x;

    std::cout << "Attempting to solve equation " << params.a << "x^2 + "
              << params.b << "x + " << params.c << " = 0" << std::endl;

    try {
        standard_x = mylib::solve_quadratic(params, 0);
        accurate_x = mylib::solve_quadratic(params, 1);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Output answer to console
    const int n_digits = std::numeric_limits<double>::max_digits10;
    // const int n_digits = std::ceil(std::numeric_limits<double>::digits * std::log10(2) + 1);
    std::cout.precision(n_digits);

    std::cout << "Standard calculation:" << std::endl;
    std::cout << standard_x.x1 << "  " << standard_x.x2 << std::endl;

    std::cout << "Accurate calculation:" << std::endl;
    std::cout << accurate_x.x1 << "  " << accurate_x.x2 << std::endl;

    return 0;
}
