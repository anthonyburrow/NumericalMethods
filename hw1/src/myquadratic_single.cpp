#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <limits>
#include <cmath>
#include <stdlib.h>

struct quad_params {
    double a;
    double b;
    double c;
};

struct quad_solution {
    double x1;
    double x2;
};

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

quad_solution solve_standard(const double &c1, const double &c2) {
    quad_solution x;
    const double sqrt_discrim = sqrt_discriminant(c1, c2);

    x.x1 = -(sqrt_discrim + c1);
    x.x2 = sqrt_discrim - c1;

    return x;
}

quad_solution solve_accurate(const double &c1, const double &c2) {
    quad_solution x;
    const double sqrt_discrim = sqrt_discriminant(c1, c2);

    x.x1 = -c1 - std::copysign(sqrt_discrim, c1);
    x.x2 = c2 / x.x1;

    return x;
}

quad_solution solve_quadratic(quad_params &params, const bool accurate = 1) {
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

    if (accurate) { return solve_accurate(c1, c2); }
    else { return solve_standard(c1, c2); }
}

quad_params read_params(const std::string &filename) {
    std::cout << "Reading from parameter file: " << filename << std::endl;

    std::ifstream param_file(filename);
    std::string line;
    quad_params params;

    while (std::getline(param_file, line)) {
        if (line[0] == '#') { continue; }

        std::stringstream iss(line);
        double a, b, c;

        iss >> a >> b >> c;
        params = {a, b, c};
    }
    param_file.close();

    return params;
}

int main(int argc, char* argv[]) {
    const std::string filename = "./config/params";
    quad_params params = read_params(filename);

    // Get quadratic solutions
    quad_solution standard_x;
    quad_solution accurate_x;

    std::cout << "Attempting to solve equation " << params.a << "x^2 + "
              << params.b << "x + " << params.c << " = 0" << std::endl;

    try {
        standard_x = solve_quadratic(params, 0);
        accurate_x = solve_quadratic(params, 1);
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
