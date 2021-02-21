#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace mylib {

    vector<double> read_params(const std::string &filename) {
        std::cout << "Reading from parameter file: " << filename << std::endl;

        std::ifstream param_file(filename);
        std::string line;
        vector<double> params(2);

        while (std::getline(param_file, line)) {
            if (line[0] == '#') { continue; }

            std::stringstream iss(line);
            double a, b;

            iss >> a >> b;
            params[0] = a;
            params[1] = b;
        }
        param_file.close();

        return params;
    }

}