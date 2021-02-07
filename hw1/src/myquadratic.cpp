#include <iostream>
#include <limits>

#include "quadratic.hpp"
#include "io.hpp"

int main(int argc, char* argv[]) {
    // fs::path exe_path = argv[0];
    // fs::path root_dir = exe_path.parent_path().parent_path();
    // std::cout << "root_dir: " << root_dir << std::endl;
    const std::string filename = "./config/params";
    mylib::quad_params params = mylib::read_params(filename);

    // Get quadratic solutions
    mylib::quad_solution standard_x;
    mylib::quad_solution accurate_x;

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
    std::cout.precision(n_digits);

    std::cout << "Standard calculation:" << std::endl;
    std::cout << standard_x.x1 << "  " << standard_x.x2 << std::endl;

    std::cout << "Accurate calculation:" << std::endl;
    std::cout << accurate_x.x1 << "  " << accurate_x.x2 << std::endl;

    return 0;
}
