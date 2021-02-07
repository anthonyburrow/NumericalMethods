#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "quadratic.hpp"

namespace mylib {

    mylib::quad_params read_params(const std::string &filename) {
        std::cout << "Reading from parameter file: " << filename << std::endl;

        std::ifstream param_file(filename);
        std::string line;
        mylib::quad_params params;

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

}